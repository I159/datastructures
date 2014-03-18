#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define BUF_SIZE 1024
char buffer[BUF_SIZE];
char *command;
char *idata;

struct node {
  int data;
  struct node* left;
  struct node* right;
};

struct node* entry;
const char delimeter[1] = " ";

static int lookup(struct node* node, int value) {
  if (node == NULL)
    return false;
  else {
    if (value == node->data)
      return true;
    else {
      if (value < node->data)
        return lookup(node->left, value);
      else
        return lookup(node->right, value);
    }
  }
}

struct node* NewNode(int data) {
  /*hm... allocated memory? http://www.codingunit.com/c-tutorial-the-functions-malloc-and-fre*/
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

void main(){

  while (fgets(buffer, BUF_SIZE, stdin)) {
    command = strtok(buffer, delimeter);
    idata = strtok(NULL, delimeter);
    if (command == "insert") {
      if (entry != NULL)
        insert(entry, *idata);
      else
        entry = NewNode(*idata);
    }
    else if (command == "lookup") {
      if (entry)
        printf("Found: %d", lookup(entry, *idata));
    }
    else {
        printf("Invalid command\n");
    }
  }
}
