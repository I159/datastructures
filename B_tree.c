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
int *length;
int *tmp;

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
  else if ((length = sizeof(entry)/sizeof(entry[0])) < *MAX_DEGREE){
    // Add new key to the tree through the entry point.
    entry = realloc(entry, *(length + 1) * sizeof(entry[0]));
    for (length; (*entry[length] > value) || (*length >= 0); length--)
      entry[length + 1] = entry[length];
    entry[length] = value;
  }
}

struct node *lookup(struct node* entry, int* value) {
}

int delete(struct node* entry, int* value) {
}

main() {
}
