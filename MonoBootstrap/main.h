#pragma once

// Included header files

#include <string>
#include <stdlib.h>
#include <dlfcn.h>
#include <mach/error.h>
#include <mach_override.h>
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>
#include <mach/mach_init.h>
#include <pthread.h>
#include <mach/mach.h>
#include <mach/thread_act.h>
#include <mach/mach_init.h>
#include "config.h"

// Preprocessor macro to convert string preprocessor definitions into C strings

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

// External symbols
extern "C" void EntryPoint(const std::string mono_assembly_path);// __attribute__((visibility("default")));
