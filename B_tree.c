#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define T 3
#define T_FACTOR (T*2)-1

typedef struct key {
  int *data;
  struct node *left;
  struct node *right;
  struct node *container;
} key;

typedef struct node {
  int *length;
  key *gt_backref;
  key *ls_backref;
  key *keys;
} node;

node *entry = NULL;

key NewKey(int *value) {
  // New key production function.
}

node NewNode(int value) {
  node *new_node = malloc(sizeof(new_node));
  new_node->length = malloc(sizeof(int));
  *(new_node->length) = 1;
  new_node->gt_backref = NULL;
  new_node->ls_backref = NULL;
  new_node->keys = malloc(sizeof(new_node->keys));
  *(new_node->keys) = NewKey(value);
  return new_node;
}

node *insert_into(node *entry_point, int *value){
  int i = (entry_point != NULL) ? *(entry_point->length) : 0;
  if (entry_point == NULL) {
    entry_point = NewNode(value);
  }
  else
  {
    entry_point->keys = realloc(
        entry_point->keys,
        (*(entry_point->length)+1)*sizeof(entry_point->keys[0]));
    for (i; i--;) {
      entry_point->keys[i+1] = entry_point->keys[i];
      if ((value < entry_point->keys[i].data) || (entry_point->length == 0) )
        break;
    }
    entry_point->keys[i].data = value;
    entry_point->length++;
  }
  return entry_point;
}

int within(struct node *node, int *value) {
  if ((value <= node->keys[*(node->length)-1].data)
          && (value >= node->keys[0].data))
    return 0;
  else if (value > node->keys[*(node->length)-1].data)
    return 1;
  else if (value < node->keys[0].data)
    return -1;
}

key *lookup(struct node *node, int *value) {
  if (node == NULL)
    exit(0);
  else {
    key *found = NULL;
    if (within(node, value) == 0) {
      int i;
      for (i; i < *(node->length); i++) {
        if (node->keys[i].data == value)
          return &(node->keys[i]);
        else if (value > node->keys[i].data) {
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

key *__get_edge(key *keys, bool first) {
  int i;
  while (&(keys[i]) != NULL) {
    if (first) i--;
    else i++;
  }
  return &(keys[i]);
}

node *break_node(node *node) {
  if (*(node->length) == T_FACTOR) {
    int i;
    // TODO: implement node type here and below.
    struct node *insert_node;
    key *insert_key;

    if (node->ls_backref != NULL)
      insert_node = break_node(insert_into(node->node_backref, node->keys[2].data));
    else {
      entry = malloc(sizeof(entry));
      entry->keys[0].data = node->keys[2].data;
      insert_node = entry;
    }
    for (i=0; insert_node->keys[i].data != node->keys[2].data; i++);
    insert_key = &(insert_node->keys[i]);
    insert_key->left = malloc(sizeof(node[0]));
    insert_key->right = malloc(sizeof(node[0]));
    for (i=0; i < 2; i++) {
      insert_key->left->keys = realloc(insert_key->left, sizeof(node[0]) * (i+1));
      insert_key->left->keys[i] = node->keys[i];
    }
    i++;
    for (i; i <= 5; i++) {
      insert_key->right->keys = realloc(insert_key->right, sizeof(node[0]) * (i-2));
      insert_key->right->keys[i-3] = node->keys[i];
    }

    insert_key->right->gt_backref = insert_key;
    insert_key->left->ls_backref = insert_key;

    free(node);
    return insert_node;
  }
  return node;
}

node *insert(struct node *node, int *value) {
  if (node == NULL) {
      return insert_into(node, value);
  }
  else if (*(node->length) < T_FACTOR) {
    int i;
    for (i = 0; i < *(node->length); i++) {
      if (value > node->keys[i].data) {
        if (&(node[i+1]) != NULL)
          continue;
        else if (node->keys[i].right != NULL)
          return insert(node->keys[i].right, value);
        else
          return break_node(insert_into(node, value));
      }
      else {
        if (node->keys[i].left != NULL)
          return insert(node->keys[i].left, value);
        else
          return break_node(insert_into(node, value));
      }
    }
  }
}

typedef struct {
  bool right;
} directions;

#define delete(node, value, ...) kw_delete(node, value, (directions){__VA_ARGS__});

int delete_base(struct node *entry_point, int *value, bool right) {
  key *found_key = lookup(entry_point, value);
  struct node *found_node;
  found_node = found_key->container;
  key *last_key;
  int i;

  if (found_key != NULL) {
    if ((found_key->right != NULL) && (found_key->left != NULL)) {
      if (*(found_key->left->length) > T-1) {
        last_key = __get_edge(found_key->left->keys, false);
        found_key->data = last_key->data;
        return delete(found_key->left, last_key->data);
      }
      else {
        found_key->data = found_key->right->keys[0].data;
        return delete(found_key->right, found_key->right->keys[0].data);
      }
    }
    else if ((found_node->gt_backref != NULL) || (found_node->ls_backref != NULL)){
      if (*(found_node->length) > T-1)
        free(found_key);
      else if (right == true) {
        if (found_node->gt_backref != NULL) {
          insert_into(found_node, found_node->gt_backref->data);
          free(found_key);
          found_node->gt_backref->data = found_node->gt_backref->right->keys[0].data;
          return delete(found_node->gt_backref->right, found_node->gt_backref->right->keys[0].data);
        }
        else {
          return delete(found_node, value, right=false);
        }
      }
      else {
        if (found_node->ls_backref != NULL) {
          insert_into(found_node, found_node->ls_backref->data);
          free(found_key);
          found_node->ls_backref->data = found_node->ls_backref->left->keys->data;
          return delete(found_node->ls_backref->left, found_node->ls_backref->left->keys->data);
        }
        else {
          // Level up...
          found_key->data = found_node->gt_backref->data;
          return delete(found_node->gt_backref, found_node->gt_backref->data);
        }
      }
    }
    else {
      // Drop root and squash nodes.
      found_key->left = realloc(
        found_key->left,
        *(found_key->right->length) * sizeof(found_key->left[0]));

      for (i = *(found_key->left->length); i < *(found_key->left->length) + *(found_key->right->length); i++)
        found_key->left->keys[i] = found_key->right->keys[i-*(found_key->right->length)];
      entry = break_node(found_key->left);
      free(found_key);
    }
  }
}

int kw_delete(struct node *node, int *value, directions direction) {
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
