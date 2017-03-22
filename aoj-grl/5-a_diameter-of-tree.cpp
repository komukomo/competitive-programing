#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
static const int NMAX = 100000;
static const int WMAX = 1000;
int N;

struct Edge {
  int target, weight;
};

vector<Edge> G[NMAX];

bool visited[NMAX];
int weights[NMAX];

void clear() {
  for (int i = 0; i < N; i++) {
    visited[i] = false;
    weights[i] = 0;
  }
}

void visit(int n, int w) {
  visited[n] = true;
  weights[n] = w;
}

int bfs(int n, int *maxn_store) {
  clear();
  queue<int> q;
  q.push(n);
  visit(n, 0);
  int maxw = 0;
  int max_node = 0;

  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto v : G[u]) {
      if (!visited[v.target]) {
        int w = weights[u] + v.weight;
        if (w > maxw) {
          maxw = w;
          max_node = v.target;
        }
        visit(v.target, w);
        q.push(v.target);
      }
    }
  }
  if (maxn_store)
    *maxn_store = max_node;
  return maxw;
}

int main() {
  cin >> N;
  for (int i = 0; i < N - 1; i++) {
    int s, t, w;
    cin >> s >> t >> w;
    G[s].push_back(Edge{t, w});
    G[t].push_back(Edge{s, w});
  }
  int maxn;
  bfs(0, &maxn);
  cout << bfs(maxn, 0) << endl;
}
