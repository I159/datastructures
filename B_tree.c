#include <stdlib.h>
#define T_FUCTOR 3

struct key {
  int* data;
  struct node* left;
  struct node* right;
};

struct key* entry[(T_FUCTOR * 2)-1];

struct key *NewNode(int* value) {
  struct key** new_node;
  struct key* new_key;

  new_node = (struct key*)malloc(sizeof(new_key));
  new_key  = malloc(sizeof(new_key));

  new_key->data = value;
  new_key->left = NULL;
  new_key->right = NULL;

  new_node[0] = new_key;

  return new_node[0];
}

struct node *insert(struct node* entry, int* value) {
}

struct node *lookup(struct node* entry, int* value) {
}

int delete(struct node* entry, int* value) {
}

main() {
}
