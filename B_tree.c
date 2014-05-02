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

int len(struct key *node) {
  return sizeof(node)/sizeof(node[0]);
}

struct key *insert_into(struct key *node, int *value){
  int length = len(node);

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
  int length = len(node);
  if ((value <= node[length-1].data) && (value >= node[0].data))
    return 0;
  else if (value > node[length-1].data)
    return 1;
  else if (value < node[0].data)
    return -1;
}

struct key *lookup(struct key *node, int *value) {
  if (node == NULL)
    exit(0);
  else {
    struct key *found = NULL;
    if (within(node, value) == 0) {
      int length = len(node);
      int i;
      for (i; i < length; i++) {
        if (node[i].data == value)
          return &(node[i]);
        else if (value > node[i].data) {
          if (node[i].right != NULL) {
            if ((within(node[i].right, value) == 1) && (&(node[i+1]) != NULL))
              continue;
            else if (within(node[i].right, value) == 0)
              return lookup(node[i].right, value);
            else
              return NULL;
          }
          else {
            if (&(node[i+1]) != NULL)
              continue;
          }
        }
        else {
          if (node[i].left != NULL)
            return lookup(node[i].left, value);
          else
            return NULL;
        }
      }
    }
  }
}

struct key *insert(struct key *node, int *value) {
  /* Result function decorator. Check (Norris) of node length and break it if
   * length greater then T-factor. */

  struct key *break_node(struct key *node) {
    int length = len(node);
    if (length == T_FACTOR) {
      struct key *insert_node = NULL;

      if (node[0].backref != NULL)
      // TODO: make it decorator
          insert_node = insert(node[0].backref, node[2].data);
      else {
          entry = NewKey(node[2].data);
          insert_node = entry;
      }
      insert_node->left = malloc(sizeof(node[0]));
      insert_node->right = malloc(sizeof(node[0]));
      int i;
      for (i; i < 2; i++) {
          insert_node->left = realloc(insert_node->right, sizeof(node[0]) * (i+1));
          insert_node->left[i] = node[i];
      }
      i++;
      for (i; i <= 5; i++) {
          insert_node->right = realloc(insert_node->right, sizeof(node[0]) * (i-2));
          insert_node->right[i-3] = node[i];
      }
      free(node);
      return insert_node;
    }
    return node;
  }

  int length = len(node);

  if (node == NULL) {
      entry = insert_into(node, value);
      return entry;
  }
  else if (length < T_FACTOR) {
    int i;
    for (i; i < length; i++) {
      if (value > node[i].data) {
        if (&(node[i+1]) != NULL)
          continue;
        else if (node[i].right != NULL)
          return insert(node[i].right, value);
        else
          return break_node(insert_into(node, value));
      }
      else {
        if (node[i].left != NULL)
          return insert(node[i].left, value);
        else
          return break_node(insert_into(node, value));
      }
    }
  }
}

void delete(struct key *node, int value) {
  // TODO: get the deletion algorythm.
  struct key *found_key = lookup(node, value);
  struct key *found_node;
  if (found_key != NULL) {
    if ((found_key.right == NULL) && (found_key.left == NULL)) {
      int i;
      for (i; found_key[i]; i--);
      found_node = found_key[i];
      if (len(found_node) > T -1)
        free(found_key);
      else {
        // NOTE: backref must be greater than the last node key data.
        found_key.data = found_key.backref[0].data;
        found_key.backref[0].data = found_key.backref[0].right[0].data;
        delete(found_key.backref[0].right[0]);
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
