#include "main.h"

void EntryPoint(const char *mono_assembly_path)
{
	MonoDomain *mono_domain = mono_jit_init("");

	MonoAssembly *mono_assembly = mono_domain_assembly_open(mono_domain, mono_assembly_path);
	printf("Mono assembly '%s': %p\n", mono_assembly_path, mono_assembly);

	if (mono_assembly == nullptr)
	{
		fprintf(stderr, "Error: Could not open Mono assembly '%s'\n", mono_assembly_path);
		exit(EXIT_FAILURE);
	}

	MonoImage *mono_image = mono_assembly_get_image(mono_assembly);
	if (mono_image == nullptr)
	{
		fprintf(stderr, "Error: Could not get Mono image for Mono assembly '%s'\n", mono_assembly_path);
		exit(EXIT_FAILURE);
	}

	MonoClass *entry_point_attribute_class = mono_class_from_name(mono_image, "Pempo", "AssemblyEntryPointAttribute");
	MonoCustomAttrInfo *assembly_attributes = mono_custom_attrs_from_assembly(mono_assembly);

	if (assembly_attributes == nullptr)
	{
		fprintf(stderr, "Error: Could not get Mono custom attributes for Mono assembly '%s'\n", mono_assembly_path);
		exit(EXIT_FAILURE);
	}

	MonoArray *assembly_attribute_objects = mono_custom_attrs_construct(assembly_attributes);
	MonoMethodDesc *entry_point_method_desc = nullptr;
	char *entry_point_method_desc_string;

	for (int i = 0; i < assembly_attributes->num_attrs; ++i)
	{
		MonoCustomAttrEntry attribute_entry = assembly_attributes->attrs[i];

		if (mono_method_get_class(attribute_entry.ctor) == entry_point_attribute_class)
		{
			MonoObject *object = mono_array_get(assembly_attribute_objects, MonoObject *, i);
			MonoProperty *property = mono_class_get_property_from_name(entry_point_attribute_class, "EntryPointMethod");
			MonoString *string = (MonoString *) mono_property_get_value(property, object, nullptr, nullptr);
			entry_point_method_desc_string = mono_string_to_utf8(string);
			entry_point_method_desc = mono_method_desc_new(entry_point_method_desc_string, true);
		}
	}

	mono_custom_attrs_free(assembly_attributes);

	if (entry_point_method_desc == nullptr)
	{
		fprintf(stderr, "Error: Could not find 'Pempo.AssemblyEntryPointAttribute' on the Mono assembly '%s'\n",
		        mono_assembly_path);
		exit(EXIT_FAILURE);
	}

	MonoMethod *entry_point_method = mono_method_desc_search_in_image(entry_point_method_desc, mono_image);

	printf("Mono entry point method '%s': %p\n", entry_point_method_desc_string, entry_point_method);

	if (entry_point_method == nullptr)
	{
		fprintf(stderr, "Error: Could not find Mono method '%s' in Mono assembly '%s'.\n",
		        entry_point_method_desc_string,
		        mono_assembly_path);
		exit(EXIT_FAILURE);
	}

	mono_runtime_invoke(entry_point_method, nullptr, nullptr, nullptr);
}
