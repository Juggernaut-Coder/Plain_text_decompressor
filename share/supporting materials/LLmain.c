/*
 - Mainline for linked list example
 - Read a file of words, create LL for each word
 - Search LL for word
 - ECED 3401
 - 14 Oct 22 - Added call to remove_from_list()
 -  4 Oct 21
*/
#include "LinkedList.h"

ENTRY* start;

FILE *infile;
char word[MAX_WORD_SZ];

main(int argc, char *argv[])
{
/* Check number of arguments */
ENTRY *removed;

if (argc == 1)
{
	printf("Missing file name\n");
	getchar();
    return -1;
}
else /* argc >= 1, attempt to open file (0 = opened) */
if (fopen_s(&infile, argv[1], "r") != 0)
{
	printf("Error opening file >%s< - possibly missing\n", argv[1]);
	getchar();
	return -1;
}

/* 
 - Pass address of start so that start can be updated 
 - This means the function is accepting the address of a pointer
   rather than the contents (i.e., its value)
 - This is call-by-reference, allowing the function to change the 
   value of start
*/
initialize_list(&start);

/* 
 - Read records and call add_to_list() until EOF 
 - Pass address of start for updating
*/
while (fgets(word, MAX_WORD_SZ, infile) > 0)
	add_to_list(&start, word);

/* Display list */
display_list(start);


printf("\nEnter word to find and remove ('#' to stop):\n");
scanf("%s", &word);

while (word[0] != '#')
{
	/*
	 - Search for word and remove it if found
	- Call-by-reference to allow start to be updated
	*/
	if ((removed = remove_from_list(&start, word)) != NULL)
	{
		printf(">%s< exists and is removed\n", word);
		free(removed);
	}
	else
		printf(">%s< does not exist\n", word);
	
	printf("\nEnter word to find and remove ('#' to stop):\n");
	scanf("%s", &word);
}

display_list(start);
getchar();

/* Wrap up */
free_mem(&start);
fclose(infile);
getchar();
return 0;
}
