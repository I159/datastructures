#include <stdlib.h>
#define T_FUCTOR 3
#define MAX_DEGREE (T_FUCTOR * 2)

struct key {
  int* data;
  struct node* left;
  struct node* right;
};

struct key* entry = NULL;
struct key* current = NULL;
int length;
int *tmp;

struct key *NewKey(int *value) {
  struct key *new_key = malloc(sizeof *new_key);

  new_key->data = value;
  new_key->left = NULL;
  new_key->right = NULL;

  return new_key;
}

struct key *NewNode(int *value) {
  struct key *new_node = malloc(sizeof *new_node);
  new_node[0] = NewKey(value);
  return new_node;
}

struct node *insert(struct key* entry, int* value) {
  if (entry == NULL)
    entry = NewNode(value);
  else if ((length = sizeof(entry)/sizeof(entry[0])) < MAX_DEGREE){
    entry = realloc(entry, (length + 1) * sizeof(entry[0]));
    for (length; (entry[length].data > value) || (length >= 0); length--)
      entry[length + 1] = entry[length];
    entry[length] = NewKey(*value);
  }
  else {
    //The game is started!!! Make the tree higher.
  }
}

struct node *lookup(struct node* entry, int* value) {
}

int delete(struct node* entry, int* value) {
}

main() {
}
