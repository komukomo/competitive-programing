#include <algorithm>
#include <iostream>
using namespace std;
static const int MAX = 200000;


struct node {
  node *right,
  node *left,
  node *parent,
  int key,
}

void trace(int data[], int n) {
  cout << data[0];
  for (int i = 1; i < n; i++) {
    cout << " " << data[i];
  }
  cout << endl;
}

int main() {
  int data[MAX + 1];
  int n;
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> data[i];

  trace(data, n);
}

