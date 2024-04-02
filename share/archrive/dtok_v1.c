char * dtok_r (const char *delim, char **save_ptr, char **dlmfnt, char *dlmbck) {

  *dlmfnt = NULL;
  *dlmbck = '\0';
  
  char *end;
  char *s = *save_ptr;
  
  if (*s == '\0') 
    { *save_ptr = s; return NULL; }
    
  /* Scan the length of leading delimiter str  */
  size_t dlmfnt_len = strspn (s, delim);

  if(dlmfnt_len > 0) {
    /* strndup strings should be freed */
    *dlmfnt = strndup(s, dlmfnt_len);
    assert(*dlmfnt != NULL && "NOT ENOUGH MEMORY FOR dlmfnt!!!");
  } 

  s +=dlmfnt_len;
  if (*s == '\0') 
    { *save_ptr = s; return NULL; }
  
  /* Find the end of the token.  */
  end = s + strcspn (s, delim);
  if (*end == '\0') 
    { *save_ptr = end; return s; }
    
  /* Terminate the token and make *SAVE_PTR point past it and assign dlmbck */
  if(*end !='\n') *dlmbck = *end;
  *end = '\0';
  *save_ptr = end + 1;
  return s;

} 
