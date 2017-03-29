#include <iostream>
#include <map>
#include <queue>
#include <vector>
using namespace std;
#define MAX 64

bool cell[MAX][MAX];
int VSIZE, HSIZE;
enum Direction {
  LEFT = -2,
  UP = -1,
  NO = 0,
  DOWN = 1,
  RIGHT = 2,
};

#define D_OFFSET 2
int dcols[] = {-1, 0, 0, 0, 1};
int drows[] = {0, -1, 0, 1, 0};

class State {
private:
  int next_cost(Direction to) { return to == d || d == NO ? cost : cost + 1; }
  bool can_go_to(Direction to) {
    int ncol = col + dcols[to + D_OFFSET];
    int nrow = row + drows[to + D_OFFSET];
    return 0 <= nrow && nrow < VSIZE && 0 <= ncol && ncol < HSIZE &&
           cell[nrow][ncol];
  }

public:
  int row, col, cost;
  Direction d;
  State(int row, int col, Direction d, int cost)
      : row(row), col(col), d(d), cost(cost) {}
  State go(Direction nextd) {
    int ncol = col + dcols[nextd + D_OFFSET];
    int nrow = row + drows[nextd + D_OFFSET];
    return State(nrow, ncol, nextd, next_cost(nextd));
  }
  Direction reverse(Direction x) { return (Direction)-x; }
  vector<State> nexts() {
    vector<State> st;
    for (auto dir: {UP, DOWN, RIGHT, LEFT}) {
      if (d != reverse(dir) && can_go_to(dir))
        st.push_back(go(dir));
    }
    return st;
  }
  void print() { printf("[%d, %d] cost:%d\n", row, col, cost); }
  bool is_goal() { return row == (VSIZE - 1) && col == (HSIZE - 1); }
  bool operator<(const State &st) const { return cost > st.cost; }
};

bool is_cached(State st) {
  static map<int, bool> cache = {};
  int hash = (MAX * st.row + st.col) * 10000 + st.d * 1000 + st.cost;
  bool exists = cache[hash];
  if (!exists) {
    cache[hash] = true;
  }
  return exists;
}

int bfs(State init) {
  priority_queue<State> qu;
  qu.push(init);

  while (!qu.empty()) {
    auto st = qu.top();
    qu.pop();
    if (st.is_goal()) {
      return st.cost;
    }
    for (auto s : st.nexts()) {
      if (!is_cached(s)) {
        qu.push(s);
      }
    }
  }
  return -1; // unsolved
}

int main() {
  cin >> VSIZE >> HSIZE;
  for (int i = 0; i < VSIZE; i++) {
    for (int j = 0; j < HSIZE; j++) {
      char tmp;
      cin >> tmp;
      cell[i][j] = (tmp == '.');
    }
  }

  auto init = State(0, 0, NO, 0);
  cout << bfs(init) << endl;
}
