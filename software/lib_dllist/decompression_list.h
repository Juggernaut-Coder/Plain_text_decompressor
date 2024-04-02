#ifndef DECOMPRESSION_LIST_H
#define DECOMPRESSION_LIST_H

#include "circular_doubly_linked_list.h"
#include "runtime_assert.h"

typedef struct __decomp_list{
    list_head list;
    char *word; 
}decomp_list;

/* Only required functions of the list for decompression are implemented using circular doubly linked linked macro inspired from linux kernel */
/* Function prototypes */
extern void add_entry(char *word);
extern char * read_and_move_entry_to_top(size_t idx);
extern void print_list(void);
extern void list_destroy(void);
extern void delete_entry(decomp_list *cursor);
#endif