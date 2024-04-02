#ifndef CONTAINER_OF
#define CONTAINER_OF

#include <assert.h>
#include <stddef.h>
#include "same_type.h"

#define container_of(ptr, type, member) ({                              \
        void * __member_ptr = (void *)(ptr);                            \
        static_assert(__same_type(*(ptr), ((type *)0)->member) ||	\
		      __same_type(*(ptr), void),                        \
                      "pointer type mismatch in container_of()");	\
        (type *)( __member_ptr - offsetof(type, member));               \
})

#endif
