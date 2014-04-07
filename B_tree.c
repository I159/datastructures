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

struct key *insert(struct key *entry, int *value) {
  length = sizeof(entry)/sizeof(entry[0]);

  // TODO: understand when flat insert is possible.
  if (entry == NULL)
    entry = NewNode(value);
  else if (length < MAX_DEGREE){
    /*
     *   Case #1: If value greater than the key->data.
     *     case #1.1: If next key exists and the value lesser than the next key.
     *       Then recursive call of the insert function with new entry as entry[i]->right
     *     case #1.2: If next key exists and the value greater than the next key.
     *       Then continue.
     *     case #1.3: If next key does not exist.
     *       Then create new node as entry[i]->right.
     *   Case #2: If value lesser than the key->data.
     *     case #2.1: If previous key exists and the value greater than the previous key->data.
     *       Then recursive call of the insert function with new entry as entry[i]->left
     *     case #2.2: If previous key exists and the value lesser than the previous key->data.
     *       Then continue.
     *     case #2.3: If previous key does not exist.
     *       Then create new node as entry[i]->left.
     *     */
  }
  else {
    // Break into two nodes
  }
}

struct node *lookup(struct node* entry, int* value) {
}

int delete(struct node* entry, int* value) {
}

main() {
}


    /*
     * The process of the flat insertion
     *
    entry = realloc(entry, (length + 1) * sizeof(entry[0]));
    for (length; (entry[length].data > value) || (length >= 0); length--)
      entry[length + 1] = entry[length];
    entry[length] = *NewKey(value);
    */
