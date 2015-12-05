#pragma once

#include <stdlib.h>
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/reflection.h>

extern "C" void EntryPoint(const char *mono_assembly_path);