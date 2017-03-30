#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
static const int MAX = 100000;
#define ROOT 0

vector<int> G[MAX];
bool visited[MAX];
int prenum[MAX];
int lowest[MAX];
int parents[MAX];
bool is_artpoint[MAX];
int NCHILD_ROOT = 0;

void visit(int n, int parent) {
  static int v = 0;
  visited[n] = true;
  prenum[n] = v++;
  parents[n] = parent;
}

void judge_parent(int n) {
  if (n != ROOT && parents[n] == ROOT)
    NCHILD_ROOT++;

  if (prenum[parents[n]] <= lowest[n])
    is_artpoint[parents[n]] = true;
}

int calc_lowest(int n, int childmin) {
  int l = min(childmin, prenum[n]);
  for (auto i : G[n]) {
    if (i != parents[n])
      l = min(l, prenum[i]);
  }
  return l;
}

int dfs(int n, int parent) {
  int childmin = MAX;
  visit(n, parent);
  for (auto i : G[n]) {
    if (!visited[i])
      childmin = min(childmin, dfs(i, n));
  }
  lowest[n] = calc_lowest(n, childmin);
  judge_parent(n);
  return lowest[n];
}

int main() {
  int nv, ne;
  cin >> nv >> ne;
  for (int i = 0; i < ne; i++) {
    int s, t;
    cin >> s >> t;
    G[s].push_back(t);
    G[t].push_back(s);
  }
  for (int i = 0; i < nv; i++) {
    visited[i] = false;
    is_artpoint[i] = false;
  }

  dfs(ROOT, ROOT);

  is_artpoint[ROOT] = NCHILD_ROOT >= 2;

  for (int i = 0; i < nv; i++) {
    if (is_artpoint[i])
      cout << i << endl;
  }
}
