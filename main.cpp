#include <CoreFoundation/CoreFoundation.h>
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>

__attribute__((constructor))
void EntryPoint()
{
    printf("Injected!\n");
    MonoDomain * domain = mono_jit_init_version("pempo", "v4.0.30319");
    mono_set_dirs("/opt/mono/lib", "/opt/mono/etc");
    MonoAssembly * assembly;

    char const * const file_name = "pempo.txt";
    FILE * file = fopen(file_name, "r");
    if (file == nullptr)
    {
        printf("Could not open 'pempo.txt'.\n");
        exit(EXIT_FAILURE);
    }

    char assembly_file[256], entry_point_method_desc[256], entry_point_class_name[256],
            entry_point_class_method_name[256];

    fgets(assembly_file, sizeof(assembly_file), file);
    assembly_file[strcspn(assembly_file, "\n")] = 0;

    fgets(entry_point_method_desc, sizeof(entry_point_method_desc), file);
    entry_point_method_desc[strcspn(entry_point_method_desc, "\n")] = 0;

//    fgets(entry_point_class_name, sizeof(entry_point_class_name), file);
//    entry_point_class_name[strcspn(entry_point_class_name, "\n")] = 0;
//
//    fgets(entry_point_class_method_name, sizeof(entry_point_class_method_name), file);
//    entry_point_class_method_name[strcspn(entry_point_class_method_name, "\n")] = 0;

    fclose(file);

    MonoAssembly * mono_assembly = mono_domain_assembly_open(domain, assembly_file);
    if (mono_assembly == nullptr)
    {
        printf("Could not open mono assembly '%s'.\n", assembly_file);
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Loaded mono assembly '%s'.\n", assembly_file);
    }

    MonoImage * mono_image = mono_assembly_get_image(mono_assembly);
    if (mono_image == nullptr)
    {
        printf("Could not get mono image of mono assembly '%s'.\n", assembly_file);
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Got mono image of mono assembly '%s'.\n", assembly_file);
    }

    MonoMethodDesc * mono_method_desc = mono_method_desc_new(entry_point_method_desc, true);
    if (mono_method_desc == nullptr)
    {
        printf("Could not get mono method description of '%s'.\n", entry_point_method_desc);
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Got mono method description of '%s'.\n", entry_point_method_desc);
    }

    MonoMethod * mono_method = mono_method_desc_search_in_image(mono_method_desc, mono_image);
    if (mono_method == nullptr)
    {
        printf("Could not find mono method '%s'.\n", entry_point_method_desc);
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Found mono method '%s'.\n", entry_point_method_desc);
    }

    mono_runtime_invoke(mono_method, nullptr, nullptr, nullptr);
}