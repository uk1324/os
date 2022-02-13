#pragma once

#include <Kernel/kstdio.h>

#ifdef KERNEL_DEBUG
    
#define ASSERT(condition, message) \
    do \
    { \
        if ((condition) == false) \
        { \
            kprintf("%s:%d: %s: Assertion '" #condition "' failed.\n", __FILE__, __LINE__, __PRETTY_FUNCTION__); \
        } \
        while (true) \
            ; \
    } while (false)
#else

#define ASSERT(condition);

#endif

#define ASSERT_NOT_REACHED() ASSERT(false)