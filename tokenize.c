#include "tokenize.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *parsed;
char **tokens;
const char *delimeter = " ";
char *tok;
int i;

char **tokenize(char *tok_buffer) {
  parsed = malloc(sizeof(BUFSIZ));
  tokens = (char**)malloc(sizeof(BUFSIZ));
  if (tok_buffer[0] == '\n'){
    printf("What do you expect? Enter sumething!\n");
    exit(0);
  }
  strcpy(parsed, tok_buffer);
  for (i=0; i < 2; i++){
    if (!(((tok = strsep(&parsed, delimeter)) != NULL) && (tokens[i] = tok)))
      exit(0);
  }
  return tokens;
}
