#include <algorithm>
#include <iostream>
using namespace std;
static const int MAX = 100;

void trace(int data[], int n) {
  cout << data[0];
  for (int i = 1; i < n; i++) {
    cout << " " << data[i];
  }
  cout << endl;
}

int selectionSort(int A[], int len) {
  int count = 0;
  for (int i = 0; i < len; i++) {
    int mini = i;
    for (int j = i; j < len; j++) {
      if (A[j] < A[mini]) {
        mini = j;
      }
    }
    if (i != mini) {
      swap(A[i], A[mini]);
      count++;
    }
  }
  return count;
}

int main() {
  int data[MAX + 1];
  int n;
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> data[i];

  int count = selectionSort(data, n);
  trace(data, n);
  cout << count << endl;
}
