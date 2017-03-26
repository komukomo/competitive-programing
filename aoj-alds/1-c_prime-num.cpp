#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
static const int MAX = 10000;

bool is_prime(int n) {
  if (n == 1 || (n != 2 && n % 2 == 0))
    return false;
  for (int i = 3; i <= sqrt(n); i += 2) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}

int main() {
  int data[MAX];
  int n;
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> data[i];

  int count = 0;
  for (int i = 0; i < n; i++)
    if (is_prime(data[i]))
      count++;
  cout << count << endl;
}
