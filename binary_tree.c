#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define BUF_SIZE 1024
char buffer[BUF_SIZE];
char *command;
int *idata;
int dvalue;
char **tokens;
char *tok;

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
    /* Tokenization. TODO: separate into the helper. */
    char *parsed = malloc(sizeof(buffer));
    tokens = (char**)malloc(sizeof(buffer));
    if (buffer[0] == '\n'){
      printf("What do you expect? Enter sumething!");
      exit(0);
    }
    strcpy(parsed, buffer);
    if ((tok = strsep(&parsed, delimeter)) != NULL)
      tokens[0] = tok;
    else
      exit(0);
    if ((tok = strsep(&parsed, delimeter)) != NULL)
      tokens[1] = tok;
    else
      exit(0);

    //free(parsed);
    //free(tok);
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    command = tokens[0];
    dvalue = atoi(tokens[1]);
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
