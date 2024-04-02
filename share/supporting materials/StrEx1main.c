/*
 - Some basics of string manipulation in C
	* C supports arrays.
	* An array is a block of contiguous memory of a specific type
	* Each entry or "element" in the array has a type and a value
	* A string in C is an array of 8-bit characters
	* In C, a character is defined as a "char"
	  char alpha;   	// alpha is a variable of type alpha

	* A character is a byte and has 256 possible values (0x00 to 0xFF)
	* Each character occupies one byte and is associated with a unique address
	* Internally, the name of the array is the first address in the array and is
	  referred to as the base address of the array
	  char data[10];	// data is a character array consisting of 10 characters

	* The address of the first character is the same as the base address
	* The address of each character increases by 1 for each subsequent character 
 - We can access an aarray using subscripts or pointers:
	* A subscript is an integer value (0, 1, 2, ...) which refers to a character in
	  the array
	* A subscript is written as "arrayname[index]"
	* Internally, the machine determines the address of the character by adding the
	  arrayname to the index
	  data[2] = 'A';	// 'A' is stored in the third location of array data[]
	  alpha = data[4];	// alpha is assigned the value of the fifth location of data[]

	* A pointer contains the address of a memory location
	  char *cptr;	// cptr is a pointer referring to the address of a char

	* All memory locations have an address
	* A character pointer "points to" a memory location 
	* We must assign an address of a character to a pointer before it is used:
	  cptr = data;	// cptr is assigned the base address of the array data[]
	
	* We can write-to or read-from an element in an array by "dereferencing" the
	  pointer:
	  *cptr = 'A'		// The location referred to by cptr is assigned 'A'
	  alpha = *cptr;	// Alpha is assigned the value referred to by cptr

	* We can "move through" an array by changing the value of a subscript or
	  pointer:
	  data[i] = alpha;
	  i++;	// Move to next character

	  alpha = *cptr;
	  cptr++;	// Move pointer to next character

	* Finally, all strings must be terminated with a NUL character
	* A NUL character has a zero value and is written '\0'
	* If we build a string, we must assign the NUL character to the last location
	* Most string functions such as fgets() concatenate a NUL after the last
	  character in the string 
  
 - ECED 3401
 - 11 Sep 22
*/
#include <stdio.h>	/* Generic I/O */
#include <string.h>	/* C string library containing string functions */
#include <ctype.h>	/* Basic C operations */

#define MAX_STR_LEN	256		/* Maximum string length */
#define NUL	'\0'			/* ASCII NUL, equivalent to 0x00 */

char instr[MAX_STR_LEN];

void func1(char strpar[])
{
/*
 - Func1() accepts the address of a string in strpar[]
 - Since strpar[] is declared as an array, we can access the contents of the
   string as an array of characters
 - In this case, each blank character is turned into '#'
*/
int i;
i = 0;
while (strpar[i] != NUL)
{
	if(strpar[i] == ' ')
		strpar[i] = '#';
	i++;
}
}

void func2(char* strpar)
{
/*
 - Func2() accept the address of a string as a character pointer, *strpar
 - We can access the character pointed to by the pointer by dereferencing it (*ptr)
 - We can move through the string by changing the value of the pointer (e.g., ptr++)
*/
while (*strpar != NUL)
{
	if (*strpar >= 'A' && *strpar <= 'Z')
		*strpar = tolower(*strpar);
	else
	if (*strpar >= 'a' && * strpar <= 'z')
		*strpar = toupper(*strpar);
	/* Else, do nothing with the character */
	/* Move to next character in the string */
	strpar++;
}
}

void func3(char *srcstr, char *dststr)
{
/* 
 - Func3() copies the source string into the destination string, reversing 
   the characters.
 - This is an unsafe function in that we do not know the length of dststr and
   could overwrite memory.
*/
int srclen;
srclen = strlen(srcstr) - 1;

do
{
	/* We are using srcstr as an array */
	*dststr++ = srcstr[srclen];
	srclen -= 1;
}
while (srclen >= 0);

*dststr = NUL;	/* dststr must be terminated with a NUL */

}

main()
{
/*
 - Program's mainline
 - Entry point to the program
*/
char temp_str[MAX_STR_LEN];	/* Temporary string */
int len;	/* Length of a string */

/* 1. Ask user for a string */
printf("Enter a string\n");
fgets(instr, MAX_STR_LEN, stdin);

/* 2. Determine string length with string library function strlen() */
len = strlen(instr);

/* 3. Print string with "%s" and its length 
 - The string appears over two lines because of the new line in the string
 - The new line character is the last character in the string before the NUL
*/
printf("instr: >>%s<< len: %d\n", instr, len);

/* 4. To remove the new line, we need to insert a NUL in place of the new line 
 - The string now has two NULs, the second, following the first, stops the 
   processing of the string
*/
instr[len - 1] = NUL;
printf("instr: >>%s<< len: %d\n", instr, len);

/* 5. The C library function strcpy() copies a sources string to a destination string 
 - The microsoft secure version is strcpy_s(), copies up to a specified number of bytes
   or the NUL
*/
strcpy_s(temp_str, MAX_STR_LEN, instr);

/* 6. Arrays are passed by reference 
 - Arrays are contiguous (one byte follows another)
 - The name of the array refers to the first byte in the string and the starting
   address of the string
 - Calling func1() supplies the address of temp_str to func1()
 - With the address, the function can change the contents of the string. Why?
*/
func1(temp_str);
printf("After func1() - temp_str: >>%s<<\n", temp_str);

func2(instr);
printf("After func2() - instr: >>%s<<\n", instr);

func3(instr, temp_str);
printf("After func3() - instr: >>%s<< temp_str: >>%s<<\n", instr, temp_str);

getchar();

}