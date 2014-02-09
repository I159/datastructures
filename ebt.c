struct node {
  int data;
  struct node* left;
  struct node* right;
}

static int lookup(struct node* node, int value) {
  if (node == NULL) {
    return false;
  }
  else {
    if (value == node->data) return true;
    else {
      if (value < node->data) return lookup(node->left, value);
      else return lookup(node->right, value);
    }
  }
}

struct node* NewNode(int data) {
  struct node* node = new(struct node);
  node->data = data;
  node->left = NULL;
  node->right = NULL;

  return node;
}

struct node* insert(struct node* node, int data) {
  if (node == NULL) return NewNode(data);
  else {
    if (data <= node->data) node->left = insert(node->left, data);
    else node->right = insert(node->right. data);

    return node;
  }
}
