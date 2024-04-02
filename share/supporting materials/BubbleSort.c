/*
 - Sorting example
 - ECED 3401
 - 20 Sep 22
*/
#include <stdlib.h>
#include <stdio.h>

#define NUM_STUDS	5
#define TRUE 1
#define FALSE 0

/* Structure holding the total courses taken (count) and student number (id) */
struct course_count
{
int count;
int id;
};

typedef struct course_count CC;

/* Create an arrau of student counts and ids */
CC students[NUM_STUDS] = { {3, 1000}, {5, 1001}, {7, 1002}, {1, 1004}, {3, 1005} };	/* Random */
// CC students[NUM_STUDS] = { {7, 1000}, {6, 1001}, {5, 1002}, {4, 1004}, {3, 1005} };	/* Sorted */
// CC students[NUM_STUDS] = { {1, 1000}, {2, 1001}, {2, 1002}, {4, 1004}, {5, 1005} };	/* Sorted */
// CC students[NUM_STUDS] = { {1, 1000}, {1, 1001}, {1, 1002}, {1, 1004}, {1, 1005} };	/* Same */


void bubble_sort(CC data[], int size)
{
/*
 - Implementation of a very simple sort routine
 - data[] - array to sort
 - size - number of entries in list
 - Compare and swap if [n] > [n+1]
 - Move largest to end of list
 - Largest value of list should be in last location
 - List gets "shorter" as the largest value is stored at the end
*/
int chksub;	/* Subscript of value to check */
CC tcc;		/* Temporary count and id */
int last;	/* Last sorted entry */
int sorted;	/* T|F - is the list sorted? */

sorted = FALSE; 	/* To get into loop */
last = size - 1;	/* Last data[] to inspect */

while (!sorted)
{
	chksub = 0;
	sorted = TRUE;  /* Assume in order */
	while (chksub < last)
	{
		/* Compare count [n] and [n+1] */
		if (data[chksub].count > data[chksub + 1].count)
		{
			/* Exchange [n] and [n+1] */
			tcc = data[chksub + 1];
			data[chksub + 1] = data[chksub];
			data[chksub] = tcc;
			sorted = FALSE;	/* List might be unsorted */
		}
		chksub++;	/* Next entry in list to check */
	}
	last--;	/* Last entry sorted, reduce length */
}
}

void print_list(CC *data, unsigned size)
{
/*
 - Print contents of data
 - Uses a pointer to the structure
*/

while (size)
{
	printf("%d:  %d\n", data -> id, data -> count);
	data++; /* Next entry */
	size--;
}
putc('\n', stdout);
}

main()
{
/*
 - Sort example
 - Call with list and print
*/

/* Call sort */
bubble_sort(students, NUM_STUDS);

/* Print */
print_list(students, NUM_STUDS);

getchar();
}
