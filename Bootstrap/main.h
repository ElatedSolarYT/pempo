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
#include <CoreFoundation/CoreFoundation.h>
#include <iostream>

// External symbols
extern "C" void __pthread_set_self(void *);
extern "C" void Bootstrap(ptrdiff_t code_offset, void * param_block, size_t param_size, void * dummy_pthread_data);
extern "C" void UserNotificationDisplayNotice(const char * header, const char * message, int type);