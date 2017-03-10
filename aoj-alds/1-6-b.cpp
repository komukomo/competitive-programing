#include <algorithm>
#include <iostream>
using namespace std;
static const int MAX = 100000;

struct Card {
  char suit;
  int value;
  bool operator<=(const Card &right) const { return value <= right.value; }
};

Card sentinel = Card{1, 1000000000};

int merge(Card A[], int left, int mid, int right) {
  int n1 = mid - left;
  int n2 = right - mid;
  Card L[n1 + 1], R[n2 + 1];
  for (int i = 0; i < n1; i++)
    L[i] = A[left + i];
  for (int i = 0; i < n2; i++)
    R[i] = A[mid + i];
  L[n1] = sentinel;
  R[n2] = sentinel;

  int i = 0, j = 0;
  for (int k = left; k < right; k++) {
    if (L[i] <= R[j]) {
      A[k] = L[i];
      i++;
    } else {
      A[k] = R[j];
      j++;
    }
  }
}

int mergeSort(Card A[], int left, int right) {
  if (left + 1 < right) {
    int mid = (left + right) / 2;
    mergeSort(A, left, mid);
    mergeSort(A, mid, right);
    merge(A, left, mid, right);
  }
}

int partition(Card A[], int p, int r) {
  // A[p ... q-1] [q] [q+1 ... r]
  Card x = A[r];
  int i = p - 1;
  for (int j = p; j < r; j++) {
    if (A[j] <= x) {
      i++;
      swap(A[i], A[j]);
    }
  }
  swap(A[i + 1], A[r]);
  return i + 1;
}

int quicksort(Card A[], int p, int r) {
  if (p < r) {
    int q = partition(A, p, r);
    quicksort(A, p, q - 1);
    quicksort(A, q + 1, r);
  }
}

int main() {
  Card data[MAX];
  Card data2[MAX];
  int n;
  char suit;
  int value;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> suit >> value;
    data[i].suit = data2[i].suit = suit;
    data[i].value = data2[i].value = value;
  }
  quicksort(data, 0, n - 1);
  mergeSort(data2, 0, n);

  bool isStable = true;
  for (int i = 0; i < n; i++) {
    if (data[i].suit != data2[i].suit) {
      isStable = false;
      break;
    }
  }
  cout << (isStable ? "Stable" : "Not stable") << endl;

  for (int i = 0; i < n; i++) {
    cout << data[i].suit << " " << data[i].value << endl;
  }
}
