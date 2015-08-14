#pragma once

// Included header files

#include <string>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syslimits.h>
#include <sys/proc_info.h>
#include <mach/error.h>
#include <libproc.h>
#include "mach_inject.h"

// Included functions

pid_t GetProcessByName(const char * name);
bool string_has_suffix(const std::string &str, const std::string &suffix);