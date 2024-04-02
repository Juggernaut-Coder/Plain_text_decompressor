#include "decompression_list.h"

static LIST_HEAD(HEAD);
static size_t LIST_COUNT = 0;

/* This function adds a new entry to the top of the list */
void add_entry(char *word) {
    decomp_list *temp_node = (decomp_list*)malloc(sizeof(decomp_list));
    temp_node->word = strdup(word);
    INIT_LIST_HEAD(&temp_node->list);
    list_add(&temp_node->list, &HEAD);
    LIST_COUNT++;
}

/* Print the list */
void print_list(void) {
    decomp_list *temp_node;
    int item_idx = 1;
    list_for_each_entry(temp_node,&HEAD,list) {
        printf("List_Item_%d: %s\n", item_idx, temp_node->word);
        item_idx++;
    }
}

/* Finds entry at index x. Reads the word, replaces entry with head entry */
char * read_and_move_entry_to_top(size_t idx) {
    decomp_list *temp_node, *cursor;
    size_t counter;
    rt_assert((idx > 0 && idx <= LIST_COUNT),"-->Invalid index<-- index larger than list count");
    
    list_get_entry_at_idx_safe(cursor, temp_node, &HEAD, list, counter, idx);
    
    list_del_init(&cursor->list);
    list_add(&cursor->list, &HEAD);
    return cursor->word;
}

/* Delete a entry from the list */
void delete_entry(decomp_list *cursor) {
    list_del(&cursor->list);
    free(cursor->word);
    free(cursor);
}

/* Deletes all entries from the list */
void list_destroy(void) {
    decomp_list *temp_node, *cursor;
    list_for_each_entry_safe(cursor, temp_node, &HEAD, list) {
        delete_entry(cursor);    
    }
    LIST_COUNT = 0;
}






