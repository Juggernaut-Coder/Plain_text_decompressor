#ifndef SAME_TYPE
#define SAME_TYPE

#define __same_type(a, b) __builtin_types_compatible_p(typeof(a), typeof(b))

#endif