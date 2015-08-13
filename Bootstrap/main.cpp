#include "main.h"

// The entry point for the library when successfully injected into target process
// The attribute is for osxinj to find our function
__attribute__((constructor))
void EntryPoint()
{
    //TODO: Check if a Mono domain already exists in injected process.

    // Initialize Mono and create a Mono domain
    MonoDomain * domain = mono_jit_init_version("pempo", "v4.0.30319");
    // Set Mono directories from CMake configuration
    mono_set_dirs(TOSTRING(MONO_LIB_DIRECTORY), TOSTRING(MONO_ETC_DIRECTORY));

    // Hard code the Mono assembly file to load
    const char * assembly_file = "pempo.dll";

    // Open Mono assembly
    MonoAssembly * mono_assembly = mono_domain_assembly_open(domain, assembly_file);
    if (mono_assembly == nullptr)
    {
        printf("Could not open mono assembly '%s'.\n", assembly_file);
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Opened mono assembly '%s'.\n", assembly_file);
    }

    // Get the Mono image (the actual Mono code) for the Mono assembly
    MonoImage * mono_image = mono_assembly_get_image(mono_assembly);
    if (mono_image == nullptr)
    {
        printf("Could not get Mono image of Mono assembly '%s'.\n", assembly_file);
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Got Mono image of Mono assembly '%s'.\n", assembly_file);
    }

    // Hard code name of the static method to invoke
    const char * entry_point_method_desc = "Pempo.Program:EntryPoint()";

    // Get a Mono method description of name (just a data structure that parses the namespace and method name)
    MonoMethodDesc * pempo_entry_point_method_desc = mono_method_desc_new(entry_point_method_desc, true);

    // Search for the Mono method in the Mono image
    MonoMethod * mono_entry_point_method = mono_method_desc_search_in_image(pempo_entry_point_method_desc, mono_image);
    if (mono_entry_point_method == nullptr)
    {
        printf("Could not find Mono method '%s' in Mono assembly '%s'.\n", entry_point_method_desc, assembly_file);
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Found Mono method '%s' in Mono assembly '%s'.\n", entry_point_method_desc, assembly_file);
    }

    // Invoke Mono method
    mono_runtime_invoke(mono_entry_point_method, nullptr, nullptr, nullptr);
}