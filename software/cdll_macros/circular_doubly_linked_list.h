#ifndef CIRCULAR_DOUBLY_LINKED_LIST
#define CIRCULAR_DOUBLY_LINKED_LIST
/* Inspired from linux kernel */
/* See linux GPL license if any conflict  */

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <stdlib.h>

#include "container_of.h"
#include "rwonce.h"

typedef struct _list_head {
	struct _list_head* next;
	struct _list_head* prev;
}list_head;

#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) \
	list_head name = LIST_HEAD_INIT(name)

static inline void INIT_LIST_HEAD(list_head *list)
{
	WRITE_ONCE(list->next, list);
	WRITE_ONCE(list->prev, list);
}

/* Local function to insert a new entry between two known consecutive entries. 
 * the prev/next entries are already known and passed as parameters along with new.
 * --------  --------  --------
 * - prev -  - new  -  - next -
 * --------  --------  --------
 */
static inline void __list_add(list_head *new, list_head *prev, list_head *next) {
	next->prev = new;
	new->next = next;
	new->prev = prev;
	WRITE_ONCE(prev->next, new);
}

/**
 * list_add - add a new entry
 * @new: new entry to be added
 * @head: list head to add it after
 *
 * Insert a new entry after the specified head.
 * This is good for implementing stacks.
 */
static inline void list_add(list_head *new, list_head *head)
{
	__list_add(new, head, head->next);
}

/**
 * list_add_tail - add a new entry
 * @new: new entry to be added
 * @head: list head to add it before
 *
 * Insert a new entry before the specified head.
 * This is useful for implementing queues.
 */
static inline void list_add_tail(list_head *new, list_head *head)
{
	__list_add(new, head->prev, head);
}

/*
 * Delete a list entry by making the prev/next entries
 * point to each other.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static inline void __list_del(list_head * prev, list_head * next)
{
	next->prev = prev;
	WRITE_ONCE(prev->next, next);
}

static inline void __list_del_entry(list_head *entry)
{
	__list_del(entry->prev, entry->next);
}

/**
 * list_del - deletes entry from list.
 * @entry: the element to delete from the list.
 * Note: list_empty on entry does not return true after this, the entry is in an undefined state.
 */
static inline void list_del(list_head *entry)
{
	__list_del_entry(entry);
	entry->next = (void *) 0;
	entry->prev = (void *) 0;
}

/**
 * list_replace - replace old entry by new one
 * @old : the element to be replaced
 * @new : the new element to insert
 *
 * If @old was empty, it will be overwritten.
 */
static inline void list_replace(list_head *old,
				list_head *new)
{
	new->next = old->next;
	new->next->prev = new;
	new->prev = old->prev;
	new->prev->next = new;
}

/**
 * list_replace_init - replace old entry by new one and initialize the old one
 * @old : the element to be replaced
 * @new : the new element to insert
 *
 * If @old was empty, it will be overwritten.
 */
static inline void list_replace_init(list_head *old,
				    list_head *new)
{
	list_replace(old, new);
	INIT_LIST_HEAD(old);
}

/**
 * list_swap - replace entry1 with entry2 and re-add entry1 at entry2's position
 * @entry1: the location to place entry2
 * @entry2: the location to place entry1
 */
static inline void list_swap(list_head *entry1,
			    list_head *entry2)
{
	list_head *pos = entry2->prev;

	list_del(entry2);
	list_replace(entry1, entry2);
	if (pos == entry1)
		pos = entry2;
	list_add(entry1, pos);
}

/**
 * list_del_init - deletes entry from list and reinitialize it.
 * @entry: the element to delete from the list.
 */
static inline void list_del_init(list_head *entry)
{
	__list_del_entry(entry);
	INIT_LIST_HEAD(entry);
}

/**
 * list_move - delete from one list and add as another's head
 * @list: the entry to move
 * @head: the head that will precede our entry
 */
static inline void list_move(list_head *list, list_head *head)
{
	__list_del_entry(list);
	list_add(list, head);
}

/**
 * list_move_tail - delete from one list and add as another's tail
 * @list: the entry to move
 * @head: the head that will follow our entry
 */
static inline void list_move_tail(list_head *list,
				list_head *head)
{
	__list_del_entry(list);
	list_add_tail(list, head);
}

/**
 * list_is_first -- tests whether @list is the first entry in list @head
 * @list: the entry to test
 * @head: the head of the list
 */
static inline int list_is_first(const list_head *list, const list_head *head)
{
	return list->prev == head;
}

/**
 * list_is_last - tests whether @list is the last entry in list @head
 * @list: the entry to test
 * @head: the head of the list
 */
static inline int list_is_last(const list_head *list, const list_head *head)
{
	return list->next == head;
}

/**
 * list_is_head - tests whether @list is the list @head
 * @list: the entry to test
 * @head: the head of the list
 */
static inline int list_is_head(const list_head *list, const list_head *head)
{
	return list == head;
}

/**
 * list_empty - tests whether a list is empty
 * @head: the list to test.
 */
static inline int list_empty(const list_head *head)
{
	return (READ_ONCE(head->next) == head);
}

/**
 * list_entry - get the struct for this entry
 * @ptr:	the &struct list_head pointer.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_head within the struct.
 */
#define list_entry(ptr, type, member) \
	container_of(ptr, type, member)

/**
 * list_first_entry - get the first element from a list
 * @ptr:	the list head to take the element from.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_head within the struct.
 *
 * Note, that list is expected to be not empty.
 */
#define list_first_entry(ptr, type, member) \
	list_entry((ptr)->next, type, member)

/**
 * list_last_entry - get the last element from a list
 * @ptr:	the list head to take the element from.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_head within the struct.
 *
 * Note, that list is expected to be not empty.
 */
#define list_last_entry(ptr, type, member) \
	list_entry((ptr)->prev, type, member)

/**
 * list_next_entry - get the next element in list
 * @pos:	the type * to cursor
 * @member:	the name of the list_head within the struct.
 */
#define list_next_entry(pos, member) \
	list_entry((pos)->member.next, typeof(*(pos)), member)

/**
 * list_prev_entry - get the prev element in list
 * @pos:	the type * to cursor
 * @member:	the name of the list_head within the struct.
 */
#define list_prev_entry(pos, member) \
	list_entry((pos)->member.prev, typeof(*(pos)), member)

/**
 * list_for_each	-	iterate over a list
 * @pos:	the &struct list_head to use as a loop cursor.
 * @head:	the head for your list.
 */
#define list_for_each(pos, head) \
	for (pos = (head)->next; !list_is_head(pos, (head)); pos = pos->next)


/**
 * list_for_each_continue - continue iteration over a list
 * @pos:	the &struct list_head to use as a loop cursor.
 * @head:	the head for your list.
 *
 * Continue to iterate over a list, continuing after the current position.
 */
#define list_for_each_continue(pos, head) \
	for (pos = pos->next; !list_is_head(pos, (head)); pos = pos->next)


/**
 * list_for_each_prev	-	iterate over a list backwards
 * @pos:	the &struct list_head to use as a loop cursor.
 * @head:	the head for your list.
 */
#define list_for_each_prev(pos, head) \
	for (pos = (head)->prev; !list_is_head(pos, (head)); pos = pos->prev)


/**
 * list_for_each_safe - iterate over a list safe against removal of list entry
 * @pos:	the &struct list_head to use as a loop cursor.
 * @n:		another &struct list_head to use as temporary storage
 * @head:	the head for your list.
 */
#define list_for_each_safe(pos, n, head) \
	for (pos = (head)->next, n = pos->next; \
	    !list_is_head(pos, (head)); \
	    pos = n, n = pos->next)


/**
 * list_for_each_prev_safe - iterate over a list backwards safe against removal of list entry
 * @pos:	the &struct list_head to use as a loop cursor.
 * @n:		another &struct list_head to use as temporary storage
 * @head:	the head for your list.
 */
#define list_for_each_prev_safe(pos, n, head) \
	for (pos = (head)->prev, n = pos->prev; \
	    !list_is_head(pos, (head)); \
	    pos = n, n = pos->prev)

/**
 * list_entry_is_head - test if the entry points to the head of the list
 * @pos:	the type * to cursor
 * @head:	the head for your list.
 * @member:	the name of the list_head within the struct.
 */
#define list_entry_is_head(pos, head, member)				\
	(&pos->member == (head))


/**
 * list_for_each_entry	-	iterate over list of given type
 * @pos:	the type * to use as a loop cursor.
 * @head:	the head for your list.
 * @member:	the name of the list_head within the struct.
 */
#define list_for_each_entry(pos, head, member)				\
	for (pos = list_first_entry(head, typeof(*pos), member);	\
	     !list_entry_is_head(pos, head, member);			\
	     pos = list_next_entry(pos, member))


/**
 * list_for_each_entry_reverse - iterate backwards over list of given type.
 * @pos:	the type * to use as a loop cursor.
 * @head:	the head for your list.
 * @member:	the name of the list_head within the struct.
 */
#define list_for_each_entry_reverse(pos, head, member)			\
	for (pos = list_last_entry(head, typeof(*pos), member);		\
	     !list_entry_is_head(pos, head, member); 			\
	     pos = list_prev_entry(pos, member))


/**
 * list_for_each_entry_safe - iterate over list of given type safe against removal of list entry
 * @pos:	the type * to use as a loop cursor.
 * @n:		another type * to use as temporary storage
 * @head:	the head for your list.
 * @member:	the name of the list_head within the struct.
 */
#define list_for_each_entry_safe(pos, n, head, member)			\
	for (pos = list_first_entry(head, typeof(*pos), member),	\
		n = list_next_entry(pos, member);		             	\
	    !list_entry_is_head(pos, head, member); 			    \
	    pos = n, n = list_next_entry(n, member))          


/**
 * list_for_each_entry_safe - iterate over list of given type safe against removal of list entry
 * @pos:	the type * to use as a loop cursor.
 * @n:		another type * to use as temporary storage
 * @head:	the head for your list.
 * @member:	the name of the list_head within the struct.
 * @counter: counts number of iterations.
 * @idx: the index of a member in the list
 */

#define list_get_entry_at_idx_safe(pos, n, head, member, counter, idx)			\
	for (pos = list_first_entry(head, typeof(*pos), member),				    \
		n = list_next_entry(pos, member), counter = 1;		                 	\
	    !list_entry_is_head(pos, head, member) && counter < idx; 		        \
	    pos = n, n = list_next_entry(n, member),counter++)          



#endif

