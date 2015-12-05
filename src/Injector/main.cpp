#include <mach/mach_error.h>
#include "main.h"

pid_t GetProcessByName(const char *process_name)
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

		char current_process_path[PROC_PIDPATHINFO_MAXSIZE];
		char current_process_name[PROC_PIDPATHINFO_MAXSIZE];

		memset(current_process_path, 0, sizeof current_process_path);
		proc_pidpath(process_ids[i], current_process_path, sizeof current_process_path);

		size_t process_path_length = strlen(current_process_path);
		if (process_path_length > 0)
		{
			size_t index = process_path_length;
			while (index && current_process_path[index] != '/')
			{
				--index;
			}

			strcpy(current_process_name, current_process_path + index + 1);
			if (!strcmp(current_process_name, process_name))
			{
				return process_ids[i];
			}
		}
	}

	return 0;
}

int main(int argc, char *argv[])
{
	if (argc < 3 || getuid() > 0)
	{
		fprintf(stderr, "Usage: sudo ./inj process_name library_name\n");
		exit(EXIT_FAILURE);
	}

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

	char *bootstrap_library_path = (char *) "libbootstrap.dylib";
	void *module = dlopen(bootstrap_library_path, RTLD_NOW | RTLD_LOCAL);

	printf("Dynamic library '%s': %p\n", bootstrap_library_path, module);

	if (module == nullptr)
	{
		const char *error = dlerror();
		if (error != nullptr)
		{
			fprintf(stderr, "Error: %s\n", error);
		}
		exit(EXIT_FAILURE);
	}

	char *entry_point_function_name = (char *) "Bootstrap";
	void *module_entry_point = dlsym(module, entry_point_function_name);

	printf("Dynamic library '%s': Function '%s': %p\n", bootstrap_library_path, entry_point_function_name,
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

	char library_path[PATH_MAX];
	realpath(argv[2], library_path);

	char mach_inject_parameter[PATH_MAX];
	strncpy(mach_inject_parameter, library_path, strlen(library_path));

	char *token = strtok(library_path, ".");
	char *last_token = nullptr;
	while (token != NULL)
	{
		last_token = token;
		token = strtok(NULL, " ,.-");
	}

	if (!strcmp(last_token, "dll"))
	{
		char *mono_bootstrap_library_path = (char *) "libmonobootstrap.dylib";
		char dynamic_library_path[PATH_MAX];
		realpath(mono_bootstrap_library_path, dynamic_library_path);
		strncpy(mach_inject_parameter, dynamic_library_path, strlen(dynamic_library_path));
		strcat(mach_inject_parameter, ":");
		strcat(mach_inject_parameter, library_path);
	}
	else
	{
		strncpy(mach_inject_parameter, library_path, strlen(library_path));
	}

	mach_error_t error = mach_inject((mach_inject_entry) module_entry_point, mach_inject_parameter,
	                                 strlen(mach_inject_parameter) + 1, pid, 0);

	if (error != ERR_SUCCESS)
	{
		fprintf(stderr, "Error: %s\n", mach_error_string(error));
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}