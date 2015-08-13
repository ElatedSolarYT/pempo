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
#include "cmake_vars_generated.h"

// Preprocessor macro to convert string preprocessor definitions into C strings

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define AT __FILE__ ":" TOSTRING(__LINE__)