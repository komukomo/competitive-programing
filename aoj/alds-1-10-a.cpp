#include <algorithm>
#include <iostream>
using namespace std;
static const int MAX = 200000;

void trace(int data[], int n) {
  cout << data[0];
  for (int i = 1; i < n; i++) {
    cout << " " << data[i];
  }
  cout << endl;
}

int main() {
  int data[MAX + 1];
  data[0] = 1;
  data[1] = 1;
  int n;
  cin >> n;
  for (int i = 2; i < n; i++) {
    data[i] = data[i-1] + data[i-2];
    cout << " " << data[i] << endl;
  }

  //trace(data, n);
}

