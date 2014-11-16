#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define T 3
#define T_FACTOR (T*2)-1

typedef struct key {
  int *data;
  struct Node *left;
  struct Node *right;
} Key;

typedef struct node {
  int *length;
  Key *gt_backref;
  Key *ls_backref;
  Key *keys;
} Node;

Node *entry;

Key *NewKey(int *value){
  Key *key = malloc(sizeof(Key));
  key->data = value;
  key->left = NULL;
  key->right = NULL;
  return key;
}

Node *NewNode(int *value){
  Node *node = malloc(sizeof(Node));
  *node->length = 1;
  node->keys = NewKey(value);
  node->gt_backref = NULL;
  node->ls_backref = NULL;
}

int *lookup(Node *node, int *value){}

int *insert(Node *node, int *value){
}

int *delete(Node *node, int *value){
}

/******************************** Utils ************************************/

char buffer[BUFSIZ];
char *command;
int *idata;
int dvalue;
char **tokens;

main() {
  while (fgets(buffer, BUFSIZ, stdin)) {
    **tokens = tokenize(buffer);

    command = tokens[0];
    dvalue = atoi(tokens[1]);
    idata = &dvalue;

    if (strcmp(command, "insert") == 0) {
      insert(entry, idata);
    }
    else if (strcmp(command, "delete") == 0) {
      delete(entry, idata);
    }
    else if (strcmp(command, "lookup") == 0) {
      printf("%d", *(lookup(entry, idata)));
    }
    else {
      exit(0);
    }
  }
}
