#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;

#define N 4
#define NPANEL (N * N)
#define EMPTY 0

int manhattan_sum(short panels[]) {
  int result = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      int v = panels[i * N + j] - 1;
      if (v == EMPTY - 1)
        continue;
      int tmp = abs(i - v / N) + abs(j - v % N);
      result += tmp;
    }
  }
  return result;
}

class State {
public:
  short panels[NPANEL];
  short empty;
  int estimate;
  State(short p[]) {
    for (int i = 0; i < NPANEL; i++) {
      panels[i] = p[i];
      if (p[i] == EMPTY)
        empty = i;
    }
    estimate = manhattan_sum(panels);
  }
  void print() {
    for (int i = 0; i < NPANEL; i++) {
      if (i != 0 && i % N == 0)
        printf("\n");
      printf("%d ", panels[i]);
    }
    printf("\n");
  }
  bool is_completed() {
    for (int i = 0; i < NPANEL-1; i++)
      if (panels[i] != i+1)
        return false;
    return true;
  }
  State left() { return slide(empty, empty - 1); }
  State above() { return slide(empty, empty - N); }
  State right() { return slide(empty, empty + 1); }
  State bottom() { return slide(empty, empty + N); }
  State slide(int x, int y) {
    auto s = State(panels);
    swap(s.panels[x], s.panels[y]);
    s.empty = y;
    s.estimate = manhattan_sum(s.panels);
    return s;
  }

  vector<State> nexts() {
    vector<State> v;
    if (empty % N != 0)
      v.push_back(left());
    if (empty >= N)
      v.push_back(above());
    if (empty % N != N - 1)
      v.push_back(right());
    if (empty <= NPANEL - N - 1)
      v.push_back(bottom());
    return v;
  }
};

bool is_cached(State st) {
  static set<long long> cache;
  long long hash = 0;
  long long n = 1;
  for (int i = 0; i < NPANEL-1; i++) {
    hash += st.panels[i] * n;
    n *= (NPANEL-1);
  }
  bool exists = cache.find(hash) != cache.end();
  if (!exists) {
    cache.insert(hash);
  }
  return exists;
}

struct Node {
  State state;
  int depth;
  bool operator<(const Node &n) const {
    return state.estimate + depth > n.state.estimate + n.depth;
  }
};

short solve(State init) {
  priority_queue<Node> que;
  que.push(Node{init, 0});
  is_cached(init);

  while (!que.empty()) {
    Node node = que.top();
    que.pop();
    if (node.state.is_completed())
      return node.depth;
    for (auto s : node.state.nexts()) {
      if (!is_cached(s)) {
        que.push(Node{s, node.depth + 1});
      }
    }
  }
  return -1; // unsolved
}

int main() {
  short data[NPANEL];
  for (int i = 0; i < NPANEL; i++)
    cin >> data[i];

  auto s = State(data);

  cout << solve(s) << endl;
}
