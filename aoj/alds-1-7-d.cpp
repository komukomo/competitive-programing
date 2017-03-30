#include <algorithm>
#include <iostream>
using namespace std;
static const int MAX = 41;
int measure[MAX];
struct node {
  node *left;
  node *right;
  int key;
};

node *root = NULL;

void insert(int key) {
  node *nd = (node *)malloc(sizeof(node));
  nd->key = key;
  nd->left = NULL;
  nd->right = NULL;

  if (root == NULL) {
    root = nd;
    return;
  }

  node *x = root;
  while (1) {
    if (measure[x->key] < measure[nd->key]) {
      if (x->right == NULL) {
        x->right = nd;
        break;
      } else {
        x = x->right;
      }
    } else {
      if (x->left == NULL) {
        x->left = nd;
        break;
      } else {
        x = x->left;
      }
    }
  }
}

int buf[MAX];
int bufp =0;
void walk(node *n) {
  if (!n)
    return;
  walk(n->left);
  walk(n->right);
  buf[bufp++] = n->key;
}

int main() {
  int keys[MAX];
  int n, idx;
  cin >> n;

  for (int i = 0; i < n; i++) {
    cin >> keys[i];
  }
  for (int i = 0; i < n; i++) {
    cin >> idx;
    measure[idx] = i;
  }

  for (int i = 0; i < n; i++) {
    insert(keys[i]);
  }

  walk(root);
  cout << buf[0];
  for (int i=1; i<n; i++) {
    cout << " " << buf[i];
  }
  cout << endl;
}
