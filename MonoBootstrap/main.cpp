#include "main.h"

// The entry point for Mono bootstrap
void EntryPoint(const std::string mono_assembly_path)
{
    //TODO: Check if a Mono domain already exists in injected process.

    // Initialize Mono and create a Mono domain
    MonoDomain * mono_domain = mono_jit_init_version("", "v4.0.30319");

    // Set Mono directories from CMake configuration
    mono_set_dirs(TOSTRING(MONOBOOTSTRAP_LIB_DIRECTORY), TOSTRING(MONOBOOTSTRAP_ETC_DIRECTORY));

    // Open Mono assembly
    MonoAssembly * mono_assembly = mono_domain_assembly_open(mono_domain, mono_assembly_path.c_str());
    printf("Mono assembly '%s': %p\n", mono_assembly_path.c_str(), mono_assembly);

    if (mono_assembly == nullptr)
    {
        fprintf(stderr, "Error: Could not open Mono assembly '%s'\n", mono_assembly_path.c_str());
        exit(EXIT_FAILURE);
    }

    // Get the Mono image (the actual Mono code) for the Mono assembly
    MonoImage * mono_image = mono_assembly_get_image(mono_assembly);
    if (mono_image == nullptr)
    {
        fprintf(stderr, "Error: Could not get Mono image for Mono assembly '%s'\n", mono_assembly_path.c_str());
        exit(EXIT_FAILURE);
    }

    // Get the Mono class for EntryPointAttribute from the Mono assembly
    MonoClass * entry_point_attribute_class = mono_class_from_name(mono_image, "Pempo", "AssemblyEntryPointAttribute");

    // Get (alloc) all attributes for the Mono assembly
    MonoCustomAttrInfo * assembly_attributes = mono_custom_attrs_from_assembly(mono_assembly);

    if (assembly_attributes == nullptr)
    {
        fprintf(stderr, "Error: Could not get Mono custom attributes for Mono assembly '%s'\n", mono_assembly_path.c_str());
        exit(EXIT_FAILURE);
    }

    MonoArray * assembly_attribute_objects = mono_custom_attrs_construct(assembly_attributes);
    MonoMethodDesc * entry_point_method_desc = nullptr;
    std::string entry_point_method_desc_string = "";

    // Loop through all the attributes for the Mono assembly
    for (int i = 0; i < assembly_attributes->num_attrs; ++i)
    {
        MonoCustomAttrEntry attribute_entry = assembly_attributes->attrs[i];

        // Check if the attribute is of type EntryPointAttribute
        if (mono_method_get_class(attribute_entry.ctor) == entry_point_attribute_class)
        {
            // Get the Mono method description of the entry point
            MonoObject * object = mono_array_get(assembly_attribute_objects, MonoObject *, i);
            MonoProperty * property = mono_class_get_property_from_name(entry_point_attribute_class, "EntryPointMethod");
            MonoString * string = (MonoString *)mono_property_get_value(property, object, nullptr, nullptr);
            entry_point_method_desc_string = mono_string_to_utf8(string);
            entry_point_method_desc = mono_method_desc_new(entry_point_method_desc_string.c_str(), true);
        }
    }

    // Free the attributes for the Mono assembly
    mono_custom_attrs_free(assembly_attributes);

    if (entry_point_method_desc == nullptr)
    {
        fprintf(stderr, "Error: Could not find 'Pempo.AssemblyEntryPointAttribute' on the Mono assembly '%s'\n",
                mono_assembly_path.c_str());
        exit(EXIT_FAILURE);
    }

    // Search for the Mono method in the Mono image
    MonoMethod * entry_point_method = mono_method_desc_search_in_image(entry_point_method_desc, mono_image);

    printf("Mono entry point method '%s': %p\n", entry_point_method_desc_string.c_str(), entry_point_method);

    if (entry_point_method == nullptr)
    {
        fprintf(stderr, "Error: Could not find Mono method '%s' in Mono assembly '%s'.\n", entry_point_method_desc_string.c_str(),
                mono_assembly_path.c_str());
        exit(EXIT_FAILURE);
    }

    // Invoke Mono method
    mono_runtime_invoke(entry_point_method, nullptr, nullptr, nullptr);
}
