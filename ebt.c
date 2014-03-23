#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define BUF_SIZE 1024
char buffer[BUF_SIZE];
char *command;
int *idata;
int dvalue;
int *found;

struct node {
  int data;
  struct node* left;
  struct node* right;
};

static struct node* entry;
const char *delimeter = " ";

static int lookup(struct node* node, int value) { /*static was here*/
  if (node == NULL){
    return false;
  }
  else {
    printf("node == NULL: %d", node == NULL);
    if (value == node->data)
      return node->data;
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
      if (entry && (*found = lookup(entry, *idata)))
        printf("Found: %d\n", *found);
      else if (!entry)
        printf("The tree is empty\n");
      else if (!found)
        printf("%d not in the tree.", *idata);
    }
    else {
        printf("Invalid command: %s\n", command);
    }
  }
}
