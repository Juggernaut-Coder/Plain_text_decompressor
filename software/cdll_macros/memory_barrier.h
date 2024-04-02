#ifndef MEMORY_BARRIER_H
#define MEMORY_BARRIER_H

/* Optimization barrier */
# define barrier() __asm__ __volatile__("": : :"memory") /* The "volatile" is due to gcc bugs */

#endif