#include <iostream>
using namespace std;
static const int MAX = 1000000;

void trace(int data[], int n) {
  cout << data[0];
  for (int i = 1; i < n; i++) {
    cout << " " << data[i];
  }
  cout << endl;
}

int insertionSort(int A[], int n, int g) {
  int cnt = 0;
  for (int i = g; i < n; i++) {
    int v = A[i];
    int j = i - g;
    while (j >= 0 && A[j] > v) {
      A[j + g] = A[j];
      j = j - g;
      cnt++;
    }
    A[j + g] = v;
  }
  return cnt;
}

int shellSort(int A[], int n) {
  cnt = 0;
  m = 0;
  cout << m << endl;
  int G[m] = {1, 2, 3};
  trace(G, m);
  for (int i = 0; i < m; i++) {
    cnt += insertionSort(A, n, G[i]);
  }
  return cnt;
}

int main() {
  int data[MAX + 1];
  int n;
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> data[i];

  int cnt = shellSort(data, n);
  trace(data, n);
}
