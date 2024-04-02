#include "dtok.h"
/* strtok that returns delimiters */
char * dtok_r (const char *restrict delim, char **restrict save_ptr, char **restrict dlmfnt, char *restrict dlmbck) {

  *dlmfnt = NULL;
  *dlmbck = '\0';

  if (!*save_ptr) return NULL;
  char *s = *save_ptr;

  /* Scan the length of leading delimiter str  */
  size_t dlmfnt_len = strspn (s, delim);

  if(dlmfnt_len > 0) {
    /* strndup strings should be freed */
    *dlmfnt = strndup(s, dlmfnt_len); /* Assign dlmfnt */
    rt_assert((*dlmfnt != NULL), "Failed to allocate mermory for -->dlmfnt<--");
  }
  /* Start the token */
  s +=dlmfnt_len;
  if(!*s) return *save_ptr = 0;
  /* Find the end of the token.  */
  *save_ptr = s + strcspn (s, delim);
  /* Terminate the token and make *SAVE_PTR point past end of token and assign dlmbck */
  if(**save_ptr !='\n') *dlmbck = **save_ptr;
  if (**save_ptr) *(*save_ptr)++ = 0;
	else *save_ptr = 0;
  return s;
}