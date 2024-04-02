#ifndef READ_WRITE_ONCE_H
#define READ_WRITE_ONCE_H

#include "memory_barrier.h"

#define READ_ONCE(x)	(*(const volatile typeof(x) *)&(x))

#define WRITE_ONCE(x, val) do {          \
    barrier();                           \
    *(volatile typeof(x) *)&(x) = (val); \
    barrier();                           \
} while (0)


#endif