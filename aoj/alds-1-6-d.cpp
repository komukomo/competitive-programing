#include <algorithm>
#include <iostream>
using namespace std;
static const int MAX = 200000;

void trace(int data[], int n) {
  cout << data[0];
  for (int i = 1; i < n; i++) {
    // cout << " " << data[i];
    printf("%2d ", data[i]);
  }
  cout << endl;
}

int bsearch(int data[], int target, int left, int right) {
  // target in [left, ... ,right]
  int mid;
  while (left <= right) {
    mid = (left + right) / 2;
    if (data[mid] == target) {
      return mid;
    } else if (data[mid] < target) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return -1;
}

int main() {
  int n;
  int data[MAX];
  int sorted[MAX];
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> data[i];
    sorted[i] = data[i];
  }
  sort(sorted, sorted + n);
  int allmin = sorted[0];
  int total = 0;
  for (int i = 0; i < n; i++) {
    int ans = sorted[i];
    int x = data[i];
    if (ans == x)
      continue;

    int count = 0;
    int cyclemin = x;
    int sum = x;
    while (ans != x) {
      int j = bsearch(sorted, x, 0, n - 1);
      swap(x, data[j]);
      sum += x;
      cyclemin = min(x, cyclemin);
      count++;
    }
    data[i] = x;
    int cost1 = sum + (count - 1) * cyclemin;
    int cost2 = cost1 + 2 * (cyclemin + allmin) - count * (cyclemin - allmin);
    total += min(cost1, cost2);
  }

  cout << total << endl;
}
