#pragma once

#include <iostream>
#include <stdlib.h>
#include <dlfcn.h>
#include <mach/mach.h>
#include <CoreFoundation/CoreFoundation.h>
#include "mach_override.h"

extern "C" void __pthread_set_self(void *);
extern "C" void Bootstrap(ptrdiff_t code_offset, void *param_block, size_t param_size, void *dummy_pthread_data);
extern "C" void UserNotificationDisplayNotice(const char *header, const char *message, CFOptionFlags type);
extern "C" mach_error_t mach_override_ptr(void *originalFunctionAddress, const void *overrideFunctionAddress, void **originalFunctionReentryIsland);