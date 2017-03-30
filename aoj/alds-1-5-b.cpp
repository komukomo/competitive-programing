#include <algorithm>
#include <iostream>
using namespace std;
static const int NDATA = 500000;
static const int SENTINEL = 1000000000;

int ncomparison = 0;

void trace(int data[], int n) {
  cout << data[0];
  for (int i = 1; i < n; i++) {
    cout << " " << data[i];
  }
  cout << endl;
}

int merge(int A[], int left, int mid, int right) {
  int n1 = mid - left;  // [0, 4, 9]  n1:5
  int n2 = right - mid; // n2: 4
  int L[n1+1], R[n2+1];
  for (int i = 0; i < n1; i++)
    L[i] = A[left + i];
  for (int i = 0; i < n2; i++)
    R[i] = A[mid + i];
  L[n1] = SENTINEL;
  R[n2] = SENTINEL;

  int i = 0, j = 0;
  for (int k = left; k < right; k++) {
      ncomparison++;
    if (L[i] <= R[j]) {
      A[k] = L[i];
      i++;
    } else {
      A[k] = R[j];
      j++;
    }
  }
}

int mergeSort(int A[], int left, int right) {
  if (left + 1 < right) {
    int mid = (left + right) / 2;
    mergeSort(A, left, mid);
    mergeSort(A, mid, right);
    merge(A, left, mid, right);
  }
}

int main() {
  int data[NDATA];
  int n;
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> data[i];

  mergeSort(data, 0, n);

  trace(data, n);
  cout << ncomparison << endl;
}
