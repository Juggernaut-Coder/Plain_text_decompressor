/*
 - Creating a dynamic array (n x m) at runtime
 - Multi-dimensional arrays are row major, meaning the memory is
	organized (ordered) by row
 - For example, in an array 3 rows by 5 columns (C: [3][5]), the
	first five consecutive memory locations are the columns of row 0, 
	the next five are the columns of row 1, and the last five are the 
	columns of row 2.
 - To access an element in an array, the location (its memory address)
	is the array's base address + row number x number of columns + the
	column number.
 - This overcomes the problems of allocating arrays of a size known at
	run time as opposed to compile time.
 - ECED 3401
 - 27 Sep 2022 - Comments to explain subscripting
 - 20 Sep 2022
*/
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

/*
 - Macro to map a 2D subscript into a 1D subscript (offset)
 - Requires know value for ylim (number of columns)
 - Either: global or pass as parameter, name must be "ylim"
 - This does not refer to the element size (int in this example), since
	all references to the base address refer to an int (e.g., int a[] or
	int *a)
*/
#define XY(r, c)	(((r) * ylim + (c)))

void* create_array(int xsize, int ysize, int elementsize)
{
/*
 - Create an array of x rows and y columns
 - Each element in the array is specifed in the element size
 - Returns an address
*/
void *newarray;
printf("Create array: %d\n", xsize * ysize * elementsize);

newarray = malloc(xsize * ysize * elementsize);
printf("Base address: %p\n", newarray);

return newarray;
}

/*
 - a[3][5] - if declared as [3][5]
 - a[][1] - sets up access to a[][] with ysize of 1, but subscripting is wrong
 - a[][5] - works because row multiplier is correct
 - *a - pointer to a single-dimension array, equvalent to a[]
 - if multi-dimensional, the second (and greater) dimension must be specified
*/
void init_array(int xlim, int ylim, int a[])
{
/*
 - Initialize a 1D array as a 2D array
 - Array size is array[xlim][ylim]
 - Fill array with known 32-bit pattern
*/
int x, y;
int i;

printf("Init array\n");
i=0xffffeeee;
for (x = 0; x < xlim; x++)
	for (y = 0; y < ylim; y++)
		a[XY(x, y)] = i++;
}

void print_memory(int xlim, int ylim, int *a)
{
/*
 - Print each element of the array and its address
 - 'a' contains the address of an int (i.e., it is a pointer
	to an int)
 - When 'a' is dereferenced, it refers to an int
 - 'a' can be used as the base address of an array
*/
int x1, y1;

printf("Print memory\n");

for (x1 = 0; x1 < xlim; x1++)
	for (y1 = 0; y1 < ylim; y1++)
	{
		/* Print subscripts and offset */
		printf("%d %d -> %d %zd\t", x1, y1, XY(x1, y1), XY(x1, y1) * sizeof(int));
		/* Print actual address */
		printf("%llx\t", ((unsigned long long) a) + XY(x1, y1) * sizeof(int));
		/* Print address using subscript and contents of element */
		printf("%p %0x\n", &a[XY(x1, y1)], a[XY(x1, y1)]);
	}
}

void print_array(int xlim, int ylim, int a[])
{
/*
 - Print each element of the array by row
 - a[] refers to an int which is to be accessed as an array
*/
int x1, y1;

printf("Print array\n");

for (x1 = 0; x1 < xlim; x1++)
{
	for (y1 = 0; y1 < ylim; y1++)
		printf("%x ", a[XY(x1, y1)]);
	putc('\n', stdout);
}
}

main()
{
/*
 - Create a 3x5 array of ints
 - Access a 1D array
 - Normal declaration: int array[3][5];
 - In this case, we want an array with a variable row and col size
*/
int *array;	/* Base address of array */
int xsz, ysz;

/* These could be read from a file or stdin */
xsz = 3;
ysz = 5;

array = (int *) create_array(xsz, ysz, sizeof(int));

init_array(xsz, ysz, array);

print_array(xsz, ysz, array);

print_memory(xsz, ysz, array);

/* Allocated memory should be freed once finished with */
free(array);

getchar();

}