/*
 - Sort example using quicksort
 - For a brief description of quicksort see:
	https://www.tutorialspoint.com/data_structures_algorithms/quick_sort_algorithm.htm
 - For a more detailed description of quicksort, see:
	https://en.wikipedia.org/wiki/Quicksort
 - In this example we are to sort elements in an array of structures
 - Each element consists of a count of the number of courses a student had taken
	and the student's id
 - Quicksort uses a user-supplied comparison function that is to return an indication
	whether the first element is greater than the second (+1), equal (0), or less than (-1)
 - In this example, we are comparing the course counts, which are integer values.
 - ECED 3401
 - 14 Sep 2022
*/

#include <stdlib.h>
#include <stdio.h>
#include <search.h>

#define NUM_STUDS	5

/* Structure holding the total courses taken (count) and student number (id) */
struct course_count
{
int count;
int id;
};

typedef struct course_count CC;

/* Create an arrau of student counts and ids */
CC students[NUM_STUDS] = {{3, 1000}, {5, 1001}, {7, 1002}, {1, 1004}, {3, 1005}};

int compare(CC* p1, CC* p2)
{
/* 
 - Compare student counts 
 - p1 points to first element
 - p2 points to second element
 - return:
	+1 if p1 count > p2 count
	 0 if p1 count = p2 count
	-1 if p1 count < p2 count
*/
return p1->count > p2->count ? 1 : p1->count == p2->count ? 0 : -1;
}

void print_CC()
{
/* Print the counts and ids of each student */
int i;
i = 0;
while (i < NUM_STUDS)
{
	printf("%d:  %d\n", students[i].id, students[i].count);
	i++;
}
putc('\n', stdout);
}

main()
{
/* 
 - Show how we can use qsort() 
 - Print unsorted array
 - Sort on course count
 - Print sorted array
*/
print_CC();
/*
 - Specify:
	- the array (students)
	- the number of elements in the array (NUM_STUDS)
	- the size of the structure CC
	- the function to be called for the comparison
*/
qsort((void *)&students, NUM_STUDS, sizeof(CC), compare);
print_CC();
getchar();

}