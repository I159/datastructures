#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 1024
char buffer[BUF_SIZE];

struct key {
  int *data;
  struct key *left;
  struct key *right;
  struct key *backerf;
};

struct key *entry = NULL;

struct key *NewKey(int *value) {
  struct key *new_key = malloc(sizeof(new_key));
  new_key->data = value;
  new_key->right = NULL;
  new_key->left = NULL;
}

struct key *insert_into(struct key *node, int *value){
  int length = sizeof(node)/sizeof(node[0]);

  node = realloc(node, (length+1)*sizeof(node[0]));
  if (length > 0) {
    for (length; length--;) {
      node[length+1] = node[length]; // TODO: implement refs regroup
      if ( (value < node[length].data) || (length == 0) )
        break;
    }
  }
  node[length] = *NewKey(value);
  return node;
}

int within(struct key *node, int *value) {
  int length = sizeof(node)/sizeof(node[0]);
  if ((value <= node[length-1].data) && (value >= node[0].data))
    return 0;
  else if (value > node[length-1].data)
    return 1;
  else if (value < node[0].data)
    return -1;
}

struct key *insert(struct key *node, int *value) {
  if (node == NULL)
    entry = insert_into(node, value);
  else {
    int length = sizeof(node)/sizeof(node[0]);
    int i;
    for (i; i < length; i++) {
      if (value > node[i].data) {
        if (&(entry[i+1]) == NULL){
          if ((entry[i].right != NULL) && (within(entry[i].right, value) == 0)) // Squash conditions
            insert_into(entry[i].right, value);
          else
            insert_into(entry, value);
        }
        else if (&(entry[i+1]) != NULL) {
          if (value > entry[i+1].data)
            continue;
          else if ((entry[i].right != NULL) && (within(entry[i].right, value) == 0))
            insert_into(entry[i].right, value);
          else
            insert_into(entry, value);
        }
      }
      else {
        if (&(entry[i-1]) == NULL) {
        }
      }
    }
  }
}

/******************************** Utils ************************************
 * Must be moved to a header. */
char *command;
int *idata;
int dvalue;
char **tokens;
char *tok;
const char *delimeter = " ";

char **tokenize(char buffer[BUF_SIZE]) {
  char *parsed = malloc(sizeof(buffer));
  tokens = (char**)malloc(sizeof(buffer));
  if (buffer[0] == '\n'){
    printf("What do you expect? Enter sumething!\n");
    exit(0);
  }
  strcpy(parsed, buffer);
  if (!(((tok = strsep(&parsed, delimeter)) != NULL) && (tokens[0] = tok)))
    exit(0);
  if (!(((tok = strsep(&parsed, delimeter)) != NULL) && (tokens[1] = tok)))
    exit(0);
  return tokens;
}

main() {
  while (fgets(buffer, BUF_SIZE, stdin)) {
    tokens = tokenize(buffer);

    command = tokens[0];
    dvalue = atoi(tokens[1]);
    idata = &dvalue;

    insert(entry, idata);
  }
}
