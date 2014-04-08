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
  new_key->left = NULL; // node[i-1]->right
  new_key->right = NULL; // node[i+1]->left

  return new_key;
}

struct key *NewNode(int *value) {
  struct key *new_node = malloc(sizeof *new_node);
  new_node[0] = *NewKey(value);
  return new_node;
}

struct key *lookup(struct key *entry, int *value) {
  int length = sizeof(entry)/sizeof(entry[0]);
  for (int i = 0; i < length; i++) {
  }
}

struct key *insert_into(struct key *entry, int *value, int i) {
  entry = realloc(entry, (length + 1) * sizeof(entry[0]));
  for (length; (entry[length].data > value) || (length >= 0); length--)
    entry[length + 1] = entry[length];
  entry[length] = *NewKey(value);
}

struct key *insert(struct key *entry, int *value) {
  length = sizeof(entry)/sizeof(entry[0]);

  // The tree is empty
  if (entry == NULL)
    entry = NewNode(value);
  // Current node is not filled, insertion in the current node is possible
  else if (length < MAX_DEGREE) {
    for (int i; i < length; i++) {
      if (value > entry[i]) {
        if ((entry[i+1] != NULL) && (value > entry[i+1]->data))
          continue;
        else if (entry[i+1] == NULL) {
          entry = realloc(entry, length + 1);
          entry[length+1] = NewKey(value);
          return entry;
        }
        else if ((value < entry[i+1]) && (entry->right != NULL))
          insert(entry->right, value);
        else if (value < entry[i+1] && (entry->right == NULL))
          return insert_into(entry, value, i);
      }
      else {
      }
    }
  }
  // Break into two nodes
  else {
  }
}

struct node *lookup(struct node* entry, int* value) {
}

int delete(struct node* entry, int* value) {
}

main() {
}
