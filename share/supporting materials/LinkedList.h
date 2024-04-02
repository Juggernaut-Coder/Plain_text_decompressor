/*
 - Header file for sorted linked list example
 - Define SORTED to build sorted list
 - ECED 3401
 - 14 Oct 22 - Added remove_from_list()
 -  9 Oct 21 - Modified to hold entry structure
 -  4 Oct 21
*/
#pragma once

#include <stdio.h>
#include <string.h>
#include <malloc.h>

//#define SORTED

#define MAX_WORD_SZ 32
#define TRUE	1
#define FALSE	0
#define NUL		'\0'

struct entry
{
char data[MAX_WORD_SZ];
struct entry* next;
};

typedef struct entry ENTRY;

extern void initialize_list(ENTRY**);
extern int add_to_list(ENTRY**, char *);
extern void display_list(ENTRY*);
extern int search_word(ENTRY*, char *);
extern void free_mem(ENTRY**);
extern ENTRY* remove_from_list(ENTRY**, char*);
