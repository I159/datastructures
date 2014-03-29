#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define BUF_SIZE 1024
char buffer[BUF_SIZE];
char *parsed;
char *command;
int *idata;
int dvalue;

struct node {
  int data;
  struct node* left;
  struct node* right;
};

static struct node* entry;
struct node* found;
struct node* leftest;
const char *delimeter = " ";

struct node* lookup(struct node* node, int value) {
  if (node == NULL)
    return false;
  else {
    if (value == node->data)
      return node;
    else if (value < node->data)
      return lookup(node->left, value);
    return lookup(node->right, value);
  }
}

struct node* NewNode(int data) {
  struct node* node = malloc(sizeof(*node));
  node->data = data;
  node->left = NULL;
  node->right = NULL;

  return node;
}

struct node* insert(struct node* node, int data) {
  if (node == NULL)
    return NewNode(data);
  else {
    if (data <= node->data)
      node->left = insert(node->left, data);
    else
      node->right = insert(node->right, data);
    return node;
  }
}

int delete(struct node* node, int value) {
  found = lookup(node, value);
  if (found->right != NULL){
    leftest = found->right;
    while (leftest)
      leftest = leftest->left;

    found->data = leftest->data;
    if (leftest->right)
      insert(found, leftest->right->data);
    free(leftest);
  }
  return 0;
}

void main(){

  while (fgets(buffer, BUF_SIZE, stdin)) {
    /* Segfault if no buffer*/
    parsed = strdup(buffer);
    command = strtok(parsed, delimeter);
    dvalue = atoi(strtok(NULL, delimeter));
    idata = &dvalue;

    if (strcmp(command, "insert") == 0) {
      if (entry != NULL)
        insert(entry, *idata);
      else
        printf("Inserting %d\n", *idata);
        entry = NewNode(*idata);
    }
    else if (strcmp(command, "lookup") == 0) {
      if (entry && (found = lookup(entry, *idata)))
        printf("Found: %d\n", found->data);
      else if (!entry)
        printf("The tree is empty\n");
      else if (!found)
        printf("%d not in the tree\n", *idata);
    }
    else if ((strcmp(command, "delete") == 0) && entry)
      delete(entry, *idata);
    else {
      printf("Invalid command: %s\n", command);
      exit(0);
    }
  }
}
