#include "main.h"

void *EntryPoint(void *param_block)
{
	char *param = (char *) param_block;

	char dynamic_library_path[PATH_MAX];
	char mono_library_path[PATH_MAX];

	char *delimiter = strchr(param, ':');
	if (delimiter != nullptr)
	{
		strncpy(mono_library_path, delimiter + 1, strlen(delimiter + 1));
		strncpy(dynamic_library_path, param, delimiter - param);
	}
	else
	{
		strncpy(dynamic_library_path, param, strlen(param));
	}

	void *module = dlopen(dynamic_library_path, RTLD_NOW);

	printf("Dynamic library '%s': %p\n", dynamic_library_path, module);

	if (module == nullptr)
	{
		fprintf(stderr, "Error: %s\n", dlerror());
		exit(EXIT_FAILURE);
	}

	if (mono_library_path != nullptr)
	{
		void *mono_bootstrap_module_entry_point = dlsym(module, "EntryPoint");

		printf("Dynamic library '%s': Function '%s': %p\n", dynamic_library_path, "EntryPoint",
		       mono_bootstrap_module_entry_point);

		if (mono_bootstrap_module_entry_point == nullptr)
		{
			fprintf(stderr, "Error: %s\n", dlerror());
			exit(EXIT_FAILURE);
		}

		((void (*)(const char *)) mono_bootstrap_module_entry_point)(mono_library_path);
	}

	return 0;
}

void Bootstrap(ptrdiff_t code_offset, void *param_block, size_t param_size, void *dummy_pthread_data)
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
	pthread_create(&thread, &thread_attributes, (void *(*)(void *)) ((long) EntryPoint), param_block);
	pthread_attr_destroy(&thread_attributes);

	thread_suspend(mach_thread_self());
}

void UserNotificationDisplayNotice(const char *header, const char *message, CFOptionFlags flags)
{
	CFStringRef header_cfstringref = CFStringCreateWithCString(NULL, header, (CFStringEncoding) strlen(header));
	CFStringRef message_cfstringref = CFStringCreateWithCString(NULL, message, (CFStringEncoding) strlen(message));

	CFUserNotificationDisplayNotice(0, flags, nullptr, nullptr, nullptr, header_cfstringref,
	                                message_cfstringref, NULL);

	CFRelease(header_cfstringref);
	CFRelease(message_cfstringref);
}