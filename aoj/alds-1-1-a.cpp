#include <iostream>
using namespace std;
static const int MAX = 1000;

void trace(int data[], int n) {
  cout << data[0];
  for (int i = 1; i < n; i++) {
    cout << " " << data[i];
  }
  cout << endl;
}

void insertionSort(int A[], int N) {
  for (int i = 1; i < N; i++) {
    int v = A[i];
    int j = i - 1;
    while (j >= 0 && A[j] > v) {
      A[j + 1] = A[j];
      j--;
    }
    A[j + 1] = v;
    trace(A, N);
  }
}

int main() {
  int data[MAX + 1];
  int n;
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> data[i];

  trace(data, n);
  insertionSort(data, n);
}
