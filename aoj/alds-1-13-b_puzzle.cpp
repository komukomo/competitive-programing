#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <vector>
#include <map>
using namespace std;

#define N 3
#define NPANEL (N * N)

class State {
public:
  int panels[NPANEL];
  int empty;
  State(int p[]) {
    for (int i = 0; i < NPANEL; i++) {
      panels[i] = p[i];
      if (p[i] == 0)
        empty = i;
    }
  }
  void print() {
    for (int i = 0; i < NPANEL; i++) {
      if (i != 0 && i % N == 0)
        printf("\n");
      printf("%d ", panels[i]);
    }
  }
  bool is_completed() {
    for (int i = 1; i < NPANEL; i++)
      if (panels[i - 1] != i)
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

bool store(State st) {
  static set<int> pool;
  int hash = 0;
  for (int i = 0; i < NPANEL; i++) {
    hash *= 10;
    hash += st.panels[i];
  }
  bool exists = (pool.find(hash) != pool.end());
  if (!exists)
    pool.insert(hash);
  return !exists;
}

struct Node {
  State state;
  int depth;
};

int solve(State init) {
  if (init.is_completed())
    return 0;
  queue<Node> que;
  que.push(Node{init, 0});

  while (!que.empty()) {
    Node node = que.front();
    for (auto s : node.state.nexts()) {
      if (s.is_completed()) {
        return node.depth + 1;
      }
      if (store(s)) {
        que.push(Node{s, node.depth + 1});
      }
    }
    que.pop();
  }
}

int main() {
  int data[NPANEL];
  for (int i = 0; i < NPANEL; i++)
    cin >> data[i];

  auto s = State(data);
  cout << solve(s) << endl;
}
