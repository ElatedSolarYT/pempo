#pragma once

// Included header files

#include <string>
#include <regex>
#include <string>
#include <vector>
#include <stdlib.h>
#include <dlfcn.h>
#include <mach/error.h>
#include <mach/mach_init.h>
#include <pthread.h>
#include <mach/mach.h>
#include <mach/thread_act.h>
#include <mach/mach_init.h>

// External symbols
extern "C" void __pthread_set_self(void *);