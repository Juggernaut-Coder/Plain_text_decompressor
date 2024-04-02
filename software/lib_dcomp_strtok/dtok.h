#ifndef DTOK_H
#define DTOK_H
#include <string.h>
#include <stdlib.h>

#include "runtime_assert.h"

/**
 * dtok_r sends back the delimiter char before and after a word.
 * @s: the string to returned
 * @delim: the delimiter string
 * @save_ptr: The remaining string
 * @dlmfnt: the delimeter string at the front
 * @dlmbck: the delimeter char at the back
 */
extern char * dtok_r (const char *restrict delim, char **restrict save_ptr, char **restrict dlmfnt, char *restrict dlmbck); 

#ifdef __MINGW32__
static inline char * strndup (const char *restrict s, size_t n)
{
    size_t l = strnlen (s, n);
    char *ret = (char *) malloc ((l+1)*sizeof(char));
    if(!ret) return NULL;
    memcpy(ret,s,l);
    ret[l] = 0;
    return ret;
}
#endif



#endif 