#ifndef RT_ASSERT_H
#define RT_ASSERT_H

#include <stdlib.h>
#include <stdio.h>

#define rt_assert(expr, err_str)							                              \
  ((void) sizeof ((expr) ? 1 : 0), __extension__ ({			                    \
    if (!expr) {  								                                          \
		printf("In file %s:%d, Error: %s\n",__FILE__, __LINE__ , err_str);      \
    getchar();                                                              \
		exit(EXIT_FAILURE);                                                     \
  	}                                                                       \
    }))                                                                     \

#endif /* RT_ASSERT_H */