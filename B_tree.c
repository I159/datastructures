#include <stdlib.h>
#define T_FUCTOR 3

struct key {
  int* data;
  struct node* left;
  struct node* right;
};

struct key* entry = NULL;

struct key *NewNode(int* value) {
  struct key* new_key;
  struct key* new_node = malloc(sizeof *new_key);

  new_key->data = value;
  new_key->left = NULL;
  new_key->right = NULL;

  new_node[0] = *new_key;

  return new_node;
}

struct node *insert(struct key* entry, int* value) {
  if (entry == NULL)
    entry = NewNode(value);
  else {
    // Add new key to the tree through the entry point.
  }
}

struct node *lookup(struct node* entry, int* value) {
}

int delete(struct node* entry, int* value) {
}

main() {
}
