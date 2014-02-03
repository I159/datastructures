/* Binary tree */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct node {
  int key_value;
  struct node *left;
  struct node *right;
};

struct node *root = 0;
struct node *child;

int tmp_right;

void destroy_tree(struct node *leaf) {
  if (leaf != 0) {
    destroy_tree(leaf->left);
    destroy_tree(leaf->right);
    free(leaf);
  }
}

insert(int key, struct node **leaf) {
  if (*leaf == 0) {
    *leaf = (struct node*) malloc(sizeof(struct node));
    (*leaf)->key_value = key;
    (*leaf)->left = 0;
    (*leaf)->right = 0;
  }
  else if (key < (*leaf)->key_value) {
    insert(key, &(*leaf)->left);
  }
  else if (key > (*leaf)->key_value) {
    insert(key, &(*leaf)->right);
  }
}

delete(int key, struct node *leaf) {
  if (leaf != 0){
    if (*leaf == key) {
      if (*leaf->right != 0) {

        *child = leaf->right;
        while (child->left != 0)
          *child = *leaf->left;
        *leaf->key_value = *child->key_value;
        if (*child->right) {
          insert(*child->right, *leaf->right);
        }

      }
    }
    else if (key < *leaf) {
      return delete(key, *leaf->left);
    }
    else if (key > *leaf) {
      return delete(key, *leaf->right);
    }
  }
  return 0;
}

struct node *search(int key, struct node *leaf) {
  if (leaf != 0) {
    if(key == leaf->key_value) {
      return leaf;
    }
    else if (key < leaf->key_value) {
      return search(key, leaf->left);
    }
    else {
      return search(key, leaf->right);
    }
  }
  return 0;
}

main() {
  char action, line[1024], *e;
  int value;

  while ((action = getchar()) && fgets(line, sizeof(line), stdin)) {
    switch (action) {
      case 'i':
        printf("i %lu\n", strtol(line, &e, 10));
        break;
      case 'd':
        printf("d %lu\n", strtol(line, &e, 10));
        break;
      case 'l':
        printf("l %lu\n", strtol(line, &e, 10));
        break;
      case 'a':
        printf("d %lu\n", strtol(line, &e, 10));
        break;
      default:
        exit(0);
    }
  }
}
