#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define T 3
#define T_FACTOR (T*2)-1

typedef struct key {
  int *data;
  struct key *left;
  struct key *right;
  struct key *backref;
} key;

typedef struct node {
  *int length;
  *key gt_backref;
  *key ls_backref;
  *key keys;
} node;

node *entry = NULL;

node *insert_into(node *node, int *value){
  int i = node.length;
  node->keys = realloc(node, (length+1)*sizeof(node[0]));
  if (node.length > 0) {
    for (i; i--;) {
      node->keys[i+1] = node->keys[i];
      if ((value < node->keys[i].data) || (node.length == 0) )
        break;
    }
  }
  node->keys[length].data = value;
  node->length++;
  return node;
}

int within(struct key *node, int *value) {
  if ((value <= node->keys[node->length-1].data)
          && (value >= node->keys[0].data))
    return 0;
  else if (value > node->keys[node->length-1].data)
    return 1;
  else if (value < node.keys[0].data)
    return -1;
}

struct key *lookup(struct key *node, int *value) {
  if (node == NULL)
    exit(0);
  else {
    key *found = NULL;
    if (within(node, value) == 0) {
      int length = len(node);
      int i;
      for (i; i < node->length; i++) {
        if (node->keys[i].data == value)
          return &(node[i]);
        else if (value > node[i].data) {
          if (node->keys[i].right != NULL) {
            if ((within(node->keys[i].right, value) == 1) && (&(node->keys[i+1]) != NULL))
              continue;
            else if (within(node->keys[i].right, value) == 0)
              return lookup(node->keys[i].right, value);
            else
              return NULL;
          }
          else {
            if (&(node->keys[i+1]) != NULL)
              continue;
          }
        }
        else {
          if (node->keys[i].left != NULL)
            return lookup(node->keys[i].left, value);
          else
            return NULL;
        }
      }
    }
  }
}

key *first_of(node *node) {
  int i;
  for (i=0; &(node->keys[i]) != NULL; i--);
  return &(node->keys[i]);
}

key *last_of(node *node) {
  int i;
  for (i=0; &(node->keys[i]) != NULL; i++);
  return &(node->keys[i]);
}

node *break_node(node *node) {
  if (node->length == T_FACTOR) {
    int i;
    // TODO: implement node type here and below.
    struct key *insert_node = NULL;
    struct key *insert_key = NULL;

    if (node[0].backref != NULL)
      insert_node = break_node(insert_into(node[0].backref, node[2].data));
    else {
      entry = malloc(sizeof(entry));
      entry->data = node[2].data;
      insert_node = entry;
    }
    for (i=0; insert_node[i].data != node[2].data; i++);
    insert_key = &(insert_node[i]);
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
    if ((&(insert_key[1]) == NULL) && (insert_key[-1].backref != NULL)) {
      insert_key->backref = insert_key[-1].backref;
      insert_key[-1].backref = NULL;
    }
    else if ((&(insert_key[-1]) == NULL) && (insert_key[1].backref != NULL)) {
      insert_key->backref = insert_key[1].backref;
      insert_key[1].backref = NULL;
    }

    insert_key->right->backref = insert_key;
    last_of(insert_key->left)->backref = insert_key;
    last_of(insert_key->right)->backref = &(insert_key[1]);
    insert_key->left->backref = &(insert_key[-1]);

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
    for (i = 0; i < length; i++) {
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

void delegate_backref(struct key *found_key) {
  if (found_key->backref != NULL) {
    if (&(found_key[1]) != NULL)
      found_key[1].backref = found_key->backref;
    else
      found_key[-1].backref = found_key->backref;
  }
}

typedef struct Parents {
  struct key *greater;
  struct key *lesser;
} Parents;

Parents *get_parents (struct key *node) {
  Parents *parents;
  parents->lesser = first_of(node)->backref;
  parents->greater = last_of(node)->backref;
  return parents;
}

typedef struct {
  bool right;
} directions;

#define delete(node, value, ...) kw_delete(node, value, (directions){__VA_ARGS__});

int delete_base(struct key *node, int *value, bool right) {
  struct key *found_key = lookup(node, value);
  struct key *found_node = first_of(found_key);
  struct key *last_key;
  Parents *fn_parents = get_parents(found_node);
  int i;

  if (found_key != NULL) {
    if ((found_key->right != NULL) && (found_key->left != NULL)) {
      if (len(found_key->left) > T-1) {
        last_key = last_of(found_key->left);
        found_key->data = last_key->data;
        return delete(found_key->left, &(found_key->left[i].data));
      }
      else {
        found_key->data = found_key->right[0].data;
        return delete(found_key->right, found_key->right[0].data);
      }
    }
    else if ((fn_parents->greater != NULL) || (fn_parents->lesser != NULL)){
      if (len(found_node) > T-1)
        free(found_key);
      else if (right == true) {
        if (fn_parents->greater != NULL) {
          delegate_backref(found_key);
          insert_into(found_node, fn_parents->greater->data);
          free(found_key);
          fn_parents->greater->data = fn_parents->greater->right[0].data;
          return delete(fn_parents->greater->right, fn_parents->greater->right[0].data);
        }
        else {
          return delete(found_node, value, right=false);
        }
      }
      else {
        if (fn_parents->lesser != NULL) {
          delegate_backref(found_key);
          insert_into(found_node, fn_parents->lesser->data);
          free(found_key);
          fn_parents->lesser->data = fn_parents->lesser->left->data;
          return delete(fn_parents->lesser->left, fn_parents->lesser->left->data);
        }
        else {
          // Level up...
          found_key->data = fn_parents->greater->data;
          return delete(fn_parents->greater, fn_parents->greater->data);
        }
      }
    }
    else {
      // Drop root and squash nodes.
      found_key->left = realloc(
        found_key->left,
        len(found_key->right) * sizeof(found_key->left[0]));

      for (i = len(found_key->left); i < len(found_key->left) + len(found_key->right); i++)
        found_key->left[i] = found_key->right[i-len(found_key->right)];
      entry = break_node(found_key->left);
      free(found_key);
    }
  }
}

int kw_delete(struct key *node, int *value, directions direction) {
  bool right = direction.right ? direction.right : true;
  return delete_base(node, value, right);
}

/******************************** Utils ************************************
 * Must be moved to a header. */
char *command;
int *idata;
int dvalue;
char **tokens;
char *tok;
const char *delimeter = " ";
#define BUF_SIZE 1024
char buffer[BUFSIZ];
char *parsed;
int i;

char **tokenize(char *tok_buffer) {
  parsed = malloc(sizeof(buffer));
  tokens = (char**)malloc(sizeof(buffer));
  if (buffer[0] == '\n'){
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

main() {
  while (fgets(buffer, BUFSIZ, stdin)) {
    tokens = tokenize(buffer);

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
      printf("%d", *(lookup(entry, idata)->data));
    }
    else {
      exit(0);
    }
  }
}
