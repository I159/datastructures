#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 1024
#define T 3
#define T_FACTOR (T*2)-1

// TODO: Implement parents, greater backref and lesser backref.

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

struct key *break_node(struct key *node) {
  int length = len(node);
  if (length == T_FACTOR) {
    int i;
    struct key *insert_node = NULL;
    struct key *insert_key = NULL;

    if (node[0].backref != NULL)
        insert_node = break_node(insert_into(node[0].backref, node[2].data));
    else {
        entry = NewKey(node[2].data);
        insert_node = entry;
    }
    for (i=0; insert_node[i].data == node[2].data);
    insert_key = insert_node[i];
    insert_key->left = malloc(sizeof(node[0]));
    insert_key->right = malloc(sizeof(node[0]));
    for (i=0; i < 2; i++) {
        insert_key->left = realloc(insert_key->left, sizeof(node[0]) * (i+1));
        insert_key->left[i] = node[i];
    }
    i++;
    for (i; i <= 5; i++) {
        insert_key->right = realloc(insert_key->right, sizeof(node[0]) * (i-2));
        insert_key->right[i-3] = node[i];
    }
    free(node);
    return insert_node;
  }
  return node;
}

struct key *insert(struct key *node, int *value) {
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

void delegate_backref(struct *key found_key) {
  if (found_key.backref != NULL) {
    if (found_key[1] != 0)
      found_key[1].backref = found_key.backref;
    else
      found_key[-1].backref = found_key.backref;
  }
}

// TODO: Create macro for keyword arguments, use default directions, both as true
void delete(struct key *node, int *value) {
  struct key *found_key = lookup(node, value);
  struct key *found_node;
  int i;

  for (i=0; found_key[i]; i--);
  found_node = found_key[i];

  if (found_key != NULL) {
    if (found_key.right != NULL) && (found_key.left != NULL) {
      if (len(found_key.left) > t-1) {
        for (i=0; found_key.left[i], i++);
        found_key.data = found_key.left[i];
        return delete(found_key.left, found_key.left[i]);
      }
      else {
        found_key.data = found_key.right[0].data;
        return delete(found_key.right, found_key.right[0].data);
      }
    }
    else if ((found_node[0].gt_parent != NULL) || (found_node[0].lt_parent != NULL)){
      if (len(found_node) > t-1)
        free(found_key);
      else if (right == true) {
        if (gt_parent != NULL) {
          delegate_backref(found_key);
          insert_into(found_node, gt_parent.data);
          free(found_key);
          gt_parent.data = gt_parent.right[0].data;
          return delete(gt_parent.right, gt_parent.right[0].data);
        }
        else {
          return delete(found_node, value, .right=false);
        }
      }
      else {
        if (lt_parent != NULL) {
          delegate_backref(found_key);
          insert_into(found_node, lt_parent.data);
          free(found_key);
          lt_parent.data = lt_parent.left.data;
          return delete(lt_parent.left, lt_parent.left.data);
        }
        else {
          // Level up...
          found_key.data = gt_parent.data;
          return delete(gt_parent, gt_parent.data);
        }
      }
    }
    else {
      // Drop root and squash nodes.
      realloc(found_key.left, len(found_key.right)*found_key.left[0]);
      for (i = len(found_key.left); i < len(found_key.left) + len(found_key.right); i++)
        found_key.left[i] = found_key.right[i-len(found_key.right)];
      entry = break_nofe(found_key.left);
      free(found_key);
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
