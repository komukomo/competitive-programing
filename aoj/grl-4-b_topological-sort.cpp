#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
static const int MAX = 10000;
vector<int> G[MAX];
int indegs[MAX];
bool visited[MAX];

void visit(int x) {
  cout << x << endl;
  visited[x] = true;
}

void bfs(int start) {
  queue<int> q;
  q.push(start);

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (auto t : G[u]) {
      indegs[t]--;
      if (indegs[t] == 0 && !visited[t])
        q.push(t);
    }
    visit(u);
  }
}

int main() {
  int nv, ne;
  cin >> nv >> ne;
  for (int i = 0; i < nv; i++) {
    indegs[i] = 0;
    visited[i] = false;
  }

  for (int i = 0; i < ne; i++) {
    int s, t;
    cin >> s >> t;
    G[s].push_back(t);
    indegs[t]++;
  }

  for (int i = 0; i < nv; i++) {
    if (indegs[i] == 0 && !visited[i])
      bfs(i);
  }
}
