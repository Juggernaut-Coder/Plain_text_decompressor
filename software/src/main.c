#include "main.h"

int main(int argc, char **argv) {

    rt_assert((argc == 2), "Program only operates with -->one input file<--" );

    /* Open the file to decompress */
    FILE *dcomp_file = fopen(argv[1], "r");
    
    rt_assert((dcomp_file != NULL),"Failed to open the input file -->possibly missing<--");
    
    /* Line Buffer for fgets */
    char line_buff[MAX_LINE_SIZE];
    
    /* dtok_r variable inits */
    char *word_token, *save_ptr, *dlmfnt, dlmbck; 
    static const char *delim = " \n,.?!'\":;-"; /* Delimter string for dtok_r */
    
    /* list lookup variables */
    int lookup_index;


    /* Read line from file until end of file */
    while( ((fgets(line_buff, MAX_LINE_SIZE, dcomp_file) != NULL) && \
        (strcmp(line_buff, "0\n") != 0)) ) {
        
        save_ptr = line_buff;

        while( (strcmp(line_buff, "\n") != 0) && \
            (word_token = dtok_r(delim,&save_ptr,&dlmfnt,&dlmbck)) ) {
            /* If 1st character isdigit then it is a number
             * else it is a word. Therefore a word can have digits in it as long as it is not the 1st character of the word. */
            if(!isdigit(word_token[0])) add_entry( word_token );
            else {
                lookup_index = atoi(word_token);
                word_token = read_and_move_entry_to_top(lookup_index);
            }

            if(dlmfnt) { 
                printf("%s",dlmfnt); 
                free(dlmfnt); 
            } /* free string created by strndup */
            printf("%s", word_token);
            if(dlmbck) putchar(dlmbck);
        }
        putchar('\n');
    }
    
    list_destroy();
    int fclose_res = fclose(dcomp_file);

    rt_assert((fclose_res == 0), "Failed to close the -->input file<--");
    
    /* Stop screen from disappearing until any character is pressed */
    getchar();
    return EXIT_SUCCESS;
}