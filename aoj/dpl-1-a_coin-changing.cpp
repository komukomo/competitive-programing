#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define T_NMAX 50000
#define NCOIN_MAX 20
int solve_coin_changing(vector<int> coins, int target) {
  sort(coins.begin(), coins.end());
  int need_ncoin[T_NMAX + 1];

  for (int j = 0; j <= target; j++) {
    need_ncoin[j] = j;
  }
  for (int i = 1; i < coins.size(); i++) {
    for (int j = 1; j <= target; j++) {
      int not_use_i = need_ncoin[j];
      int use_i = (j-coins[i] >= 0) ? need_ncoin[j - coins[i]] + 1 : T_NMAX;
      need_ncoin[j] = min(use_i, not_use_i);
    }
  }
  return need_ncoin[target];
}

int main() {
  int ncoin, target;
  cin >> target >> ncoin;
  vector<int> coins;
  for (int i = 0; i < ncoin; i++) {
    int val;
    cin >> val;
    coins.push_back(val);
  }
  cout << solve_coin_changing(coins, target) << endl;
}
