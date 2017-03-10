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


void bubbleSort(int A[], int len) {
    int count = 0;
    for (int i=0; i<len; i++) {
        for (int j=len-1; j >= i+1; j--) {
            if (A[j] < A[j-1]) {
                swap(A[j], A[j-1]);
                count++;
            }
        }
    }
    trace(A, len);
    cout << count << endl;
}


int main() {
  int data[MAX + 1];
  int n;
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> data[i];

  bubbleSort(data, n);
}

