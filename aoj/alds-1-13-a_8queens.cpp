#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;
#define N 8

struct Pos {
  int x, y;
};

class Queens {
private:
  vector<Pos> st;
  vector<int> index;
  bool row[N] = {};
  bool col[N] = {};
  bool slantr[2 * N - 1] = {};
  bool slantl[2 * N - 1] = {};

  void set_val(int x, int y, bool val) {
    row[x] = val;
    col[y] = val;
    slantr[x + y] = val;
    slantl[x - y + N - 1] = val;
  }
  bool solve_main(int idx) {
    int x = index[idx];
    if (st.size() == N)
      return true;
    for (int y = 0; y < N; y++) {
      if (check(x, y)) {
        set(x, y);
        if (solve_main(idx + 1))
          return true;
        pop();
      }
    }
    return false;
  }

public:
  Queens() {}
  void pop() {
    auto p = st.back();
    set_val(p.x, p.y, false);
    st.pop_back();
  }
  void set(int x, int y) {
    st.push_back(Pos{x, y});
    set_val(x, y, true);
  }
  bool check(int x, int y) {
    return !(row[x] || col[y] || slantr[x + y] || slantl[x - y + N - 1]);
  }
  void print() {
    bool data[N][N] = {};
    for (auto q : st)
      data[q.x][q.y] = true;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++)
        cout << (data[i][j] ? "Q" : ".");
      printf("\n");
    }
  }
  bool solve() {
    bool tmp[N] = {};
    for (auto q : st)
      tmp[q.x] = true;
    for (int i = 0; i < N; i++)
      if (!tmp[i])
        index.push_back(i);
    return solve_main(0);
  }
};

int main() {
  int n;
  cin >> n;
  auto queens = Queens();
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    queens.set(x, y);
  }

  queens.solve();
  queens.print();
}
