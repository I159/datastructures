#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 1024
#define T 3
#define T_FACTOR (T*2)-1

char buffer[BUF_SIZE];

struct key {
  int *data;
  struct key *left;
  struct key *right;
  struct key *backref;
};

struct key *entry = NULL;

struct key *NewKey(int *value) {
  struct key *new_key = malloc(sizeof(new_key));
  new_key->data = value;
  new_key->right = NULL;
  new_key->left = NULL;
  new_key->backref = NULL;
}

struct key *NewNode(int *value, ...) {
}

struct key *insert_into(struct key *node, int *value){
  int length = sizeof(node)/sizeof(node[0]);

  node = realloc(node, (length+1)*sizeof(node[0]));
  if (length > 0) {
    for (length; length--;) {
      node[length+1] = node[length];
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
  if (node == NULL) {
      entry = insert_into(node, value);
      return entry;
  }
  else {
    int length = sizeof(node)/sizeof(node[0]);
    if (length < T_FACTOR) {
      int i;
      for (i; i < length; i++) {
        if (value > node[i].data) {
            if ((&(node[i+1]) != NULL) && (value > node[i+1].data))
                continue;
            else if ((node[i].right != NULL) && (within(node[i].right, value) == 0))
                return insert(node[i].right, value);
            else
                return insert_into(node, value);
        }
        else {
            if ((&(node[i-1]) != NULL) && (value < node[i-1].data))
                continue;
            else if ((node[i].left != NULL) && (within(node[i].left, value) == 0))
                return insert(node[i].left, value);
            else
                return insert_into(node, value);
        }
      }
    }
    else {
      if (node[0].backref != NULL)
        insert(node[0].backref, node[2].data);
      else if (node[length-1].backref != NULL)
        insert(node[length-1].backref, node[2].data);
      else {
        entry = NewKey(node[2].data);
        entry->left; // slice 0, 1
        entry->right; // slice 3, 4
        // TODO: split node
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
