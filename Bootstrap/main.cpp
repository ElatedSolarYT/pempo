#include "main.h"

void * EntryPoint(void * param_block)
{
    std::string param = (char *)param_block;

    std::string dynamic_library_path = "";
    std::string mono_library_path = "";

    size_t split_index = param.find(":");
    if (split_index != std::string::npos)
    {
        dynamic_library_path = param.substr(0, split_index);
        mono_library_path = param.substr(split_index + 1, param.size() - split_index);
    }
    else
    {
        dynamic_library_path = param;
    }

    void * module = dlopen(dynamic_library_path.c_str(), RTLD_NOW);

    printf("Dynamic library '%s': %p\n", dynamic_library_path.c_str(), module);

    if (module == nullptr)
    {
        fprintf(stderr, "Error: %s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    if (mono_library_path.size() > 0)
    {
        void * module_entry_point = dlsym(module, "EntryPoint");

        printf("Dynamic library '%s': Function '%s': %p\n", dynamic_library_path.c_str(), "EntryPoint", module_entry_point);

        if (module_entry_point == nullptr)
        {
            fprintf(stderr, "Error: %s\n", dlerror());
            exit(EXIT_FAILURE);
        }

        ((void(*)(const std::string)) module_entry_point)(mono_library_path);
    }

    return 0;
}

// The entry point for the library when successfully injected into target process
void Bootstrap(ptrdiff_t code_offset, void * param_block, size_t param_size, void * dummy_pthread_data)
{
    __pthread_set_self(dummy_pthread_data);

    pthread_attr_t thread_attributes;
    pthread_attr_init(&thread_attributes);

    int policy;
    pthread_attr_getschedpolicy(&thread_attributes, &policy);
    pthread_attr_setdetachstate(&thread_attributes, PTHREAD_CREATE_DETACHED);
    pthread_attr_setinheritsched(&thread_attributes, PTHREAD_EXPLICIT_SCHED);

    struct sched_param schedule;
    schedule.sched_priority = sched_get_priority_max(policy);
    pthread_attr_setschedparam(&thread_attributes, &schedule);

    pthread_t thread;
    pthread_create(&thread, &thread_attributes, (void * (*)(void *)) ((long)EntryPoint), param_block);
    pthread_attr_destroy(&thread_attributes);

    thread_suspend(mach_thread_self());
}

void UserNotificationDisplayNotice(const char * header, const char * message, int type)
{
    CFStringRef header_cfstringref = CFStringCreateWithCString(NULL, header, (CFStringEncoding)strlen(header));
    CFStringRef message_cfstringref = CFStringCreateWithCString(NULL, message, (CFStringEncoding)strlen(message));

    CFUserNotificationDisplayNotice(0, (CFOptionFlags)type, nullptr, nullptr, nullptr, header_cfstringref,
                                    message_cfstringref, NULL);

    CFRelease(header_cfstringref);
    CFRelease(message_cfstringref);
}