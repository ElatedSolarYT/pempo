#pragma once

#include <stdlib.h>
#include <dlfcn.h>
#include <mach/error.h>
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/reflection.h>
#include <mach/mach_init.h>
#include <pthread.h>
#include <mach/mach.h>
#include <mach/thread_act.h>
#include <mach/mach_init.h>

extern "C" void EntryPoint(const char* mono_assembly_path);