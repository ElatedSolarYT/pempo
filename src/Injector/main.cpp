#include <mach/mach_error.h>
#include "main.h"

pid_t GetProcessByName(std::string name)
{
    int process_count = proc_listpids(PROC_ALL_PIDS, 0, NULL, 0);
    pid_t process_ids[1024];
    memset(process_ids, 0, sizeof process_ids);
    proc_listpids(PROC_ALL_PIDS, 0, process_ids, sizeof(process_ids));

    for (int i = 0; i < process_count; i++)
    {
        if (!process_ids[i])
        {
            continue;
        }

        char process_path[PROC_PIDPATHINFO_MAXSIZE];
        char process_name[PROC_PIDPATHINFO_MAXSIZE];

        memset(process_path, 0, sizeof process_path);
        proc_pidpath(process_ids[i], process_path, sizeof process_path);

        int process_path_length = strlen(process_path);
        if (process_path_length > 0)
        {
            int position = process_path_length;
            while (position && process_path[position] != '/')
            {
                --position;
            }

            strcpy(process_name, process_path + position + 1);
            if (!strcmp(process_name, name.c_str()))
            {
                return process_ids[i];
            }
        }
    }

    return 0;
}

bool string_has_suffix(const std::string &str, const std::string &suffix)
{
    return str.size() >= suffix.size() &&
           str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

std::string execute_command(std::string command)
{
    FILE * pipe = popen(command.c_str(), "r");
    if (!pipe)
    {
        return "";
    }

    char buffer[128];
    std::string result = "";
    while(!feof(pipe))
    {
        if(fgets(buffer, 128, pipe) != NULL)
        {
            result += buffer;
        }
    }

    pclose(pipe);
    return result;
}

// Main injector program
int main(int argc, char * argv[])
{
    // Require the right amount of arguments and root
    if (argc < 3 || getuid() > 0)
    {
        fprintf(stderr, "Usage: sudo ./inj process_name library_name\n");
        exit(EXIT_FAILURE);
    }

    // Find the process ID by name
    pid_t pid = GetProcessByName(argv[1]);

    if (pid == 0)
    {
        fprintf(stderr, "Process '%s' not found\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Process ID: %u\n", pid);
    }

    // Find the bootstrap dynamic library
    std::string bootstrap_library_path = "libbootstrap.dylib";
    void * module = dlopen(bootstrap_library_path.c_str(), RTLD_NOW | RTLD_LOCAL);

    printf("Dynamic library '%s': %p\n", bootstrap_library_path.c_str(), module);

    if (module == nullptr)
    {
        const char *error = dlerror();
        if (error != nullptr)
        {
            fprintf(stderr, "Error: %s\n", error);
        }
        exit(EXIT_FAILURE);
    }

    // Find the entry point function of the dynamic library by name
    std::string entry_point_function_name = "Bootstrap";
    void * module_entry_point = dlsym(module, entry_point_function_name.c_str());

    printf("Dynamic library '%s': Function '%s': %p\n", bootstrap_library_path.c_str(), entry_point_function_name.c_str(),
           module_entry_point);

    if (module_entry_point == nullptr)
    {
        const char *error = dlerror();
        if (error != nullptr)
        {
            fprintf(stderr, "Error: %s\n", error);
        }
        exit(EXIT_FAILURE);
    }

    // Get absolute path for the dynamic library to inject
    char path[PATH_MAX];
    realpath(argv[2], path);

    std::string param = path;
    if (string_has_suffix(param, ".dll"))
    {
        size_t pointer_size = sizeof(int *);
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
        if (pointer_size == 4)
        {
            realpath("libmonobootstrap_i386.dylib", path);
        }
        else if (pointer_size == 8)
        {
            realpath("libmonobootstrap_x86_64.dylib", path);
        }
#pragma clang diagnostic pop

        param = std::string(path) + ":" + param;
    }

    // Create new thread and invoke dynamic library function in target process
    mach_error_t error = mach_inject((mach_inject_entry)module_entry_point, param.c_str(), param.length() + 1, pid, 0);

    if (error != ERR_SUCCESS)
    {
        fprintf(stderr, "Error: %s\n", mach_error_string(error));
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}