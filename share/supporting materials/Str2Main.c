/*
 - Character Counter
 - Counts spaces, periods, newlines, and total characters in a text file
 - ECED 3401
 - 13 Sep 2022
*/

#include "stdio.h"

#define SP	' '
#define NUL	'\0'
#define LF	'\n'

FILE* infile;

int main(int argc, char* argv[])
{
/*
 - Open file in argv[1], read each character in the file
 - Count number of space, periods, newlines, and total characters
 - At EOF (end-of-file), stop reading and close file
 - If only one argument (.exe name), stop executing
*/
int periodcount;
int lfcount;
int spcount;
int chcount;
/* unsigned */ char ch;

/* Check number of arguments */
if (argc == 1)
{
	printf("Missing file name\n");
	getchar();
	return -1;
}

/* argc >= 1, attempt to open file */
if (fopen_s(&infile, argv[1], "r") != 0)
{
	printf("Error opening file >%s< - possibly missing\n", argv[1]);
	getchar();
	return -1;
}

/* File exists and is open, now process */
spcount = 0;
chcount = 0;
periodcount = 0;
lfcount = 0;

while ((ch = fgetc(infile)) != EOF)
{
	/* Count number of spaces, newlines, and periods */
	if (ch == SP)
		spcount = spcount + 1;
	else
	if (ch == '.')
		periodcount = periodcount + 1;
	else
	if (ch == LF)
		lfcount = lfcount + 1;

	/* Count number of characters */
	chcount = chcount + 1;
	printf("%c", ch);
}

printf("\nTotal char: %d; spaces: %d; periods: %d; newlines: %d\n", 
	chcount, spcount, periodcount, lfcount);

/* Close file */
fclose(infile);

/* Delay screen from disappearing */
getchar();
return 0;

}

