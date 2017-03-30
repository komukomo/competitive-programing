#include <stdio.h>
#include <stdlib.h>

struct node {
  struct node *right;
  struct node *left;
  struct node *parent;
  int key;
};
typedef struct node *Node;
#define NIL NULL

Node root;

Node treeMinimum(Node x) {}

Node treeMaximum(Node x) {}

Node treeSearch(Node u, int k) {
  Node x = u;
  while (x != NIL) {
    if (x->key == k)
      return x;
    if (k < x->key) {
      x = x->left;
    } else {
      x = x->right;
    }
  }
  return NIL;
}

Node treeSuccessor(Node x) {}

int numChildren(Node x) {
  int n = 0;
  if (x->left != NIL)
    n++;
  if (x->right != NIL)
    n++;
  return n;
}

Node mostLeft(Node u) {
  Node x = u;
  while (x->left) {
    x = x->left;
  }
  return x;
}

bool isLeftChild(Node u) {
    return u->parent->left == u;
}


void treeDelete(Node z) {
  Node next;
  switch (numChildren(z)) {
  case 0:
    if (isLeftChild(z)) {
      z->parent->left = NIL;
    } else {
      z->parent->right = NIL;
    }
    free(z);
    break;
  case 1:
    next = z->left ? z->left : z->right;
    next->parent = z->parent;
    if (isLeftChild(z)) {
      z->parent->left = next;
    } else {
      z->parent->right = next;
    }
    free(z);
    break;
  case 2:
    next = mostLeft(z->right);
    z->key = next->key;
    treeDelete(next);
    break;
  }
}

void insert(int k) {
  Node y = NIL;
  Node x = root;
  Node z;

  z = (Node)malloc(sizeof(struct node));
  z->key = k;
  z->left = NIL;
  z->right = NIL;

  while (x != NIL) {
    y = x;
    if (z->key < x->key) {
      x = x->left;
    } else {
      x = x->right;
    }
  }
  z->parent = y;

  if (y == NIL) {
    root = z;
  } else if (z->key < y->key) {
    y->left = z;
  } else {
    y->right = z;
  }
}

void inorder(Node u) {
  if (u == NIL)
    return;
  inorder(u->left);
  printf(" %d", u->key);
  inorder(u->right);
}

void preorder(Node u) {
  if (u == NIL)
    return;
  printf(" %d", u->key);
  preorder(u->left);
  preorder(u->right);
}

int main() {
  int n, i, x;
  char com[20];
  scanf("%d", &n);

  for (i = 0; i < n; i++) {
    scanf("%s", com);
    if (com[0] == 'f') {
      scanf("%d", &x);
      Node t = treeSearch(root, x);
      if (t != NIL)
        printf("yes\n");
      else
        printf("no\n");
    } else if (com[0] == 'i') {
      scanf("%d", &x);
      insert(x);
    } else if (com[0] == 'p') {
      inorder(root);
      printf("\n");
      preorder(root);
      printf("\n");
    } else if (com[0] == 'd') {
      scanf("%d", &x);
      treeDelete(treeSearch(root, x));
    }
  }

  return 0;
}
