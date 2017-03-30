#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Dtree {
public:
  vector<int> parent;

  Dtree(int size) {
    parent.resize(size, 0);
    for (int i = 0; i < parent.size(); i++)
      parent[i] = i;
  }
  int unite(int x, int y) {
    int l = label(x);
    while (1) {
      int pre = parent[y];
      parent[y] = l;
      if (y == pre)
        break;
      y = pre;
    }
  }
  bool same(int x, int y) { return label(x) == label(y); }
  int label(int x) {
    while (x != parent[x]) {
      x = parent[x];
    }
    return x;
  }
};

int main() {
  int n, nquery;
  cin >> n;
  cin >> nquery;
  Dtree dt = Dtree(n);
  for (int i = 0; i < nquery; i++) {
    int x, y, command;
    cin >> command >> x >> y;
    if (command == 0) {
      dt.unite(x, y);
    } else if (command == 1) {
      cout << (dt.same(x, y) ? 1 : 0) << endl;
    }
  }
}
