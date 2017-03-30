#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
static const int MAX = 500000;

class Node {
public:
  int location;
  int right, left;
  Node() {}
};

struct Range {
  int sx, tx, sy, ty;
};

class Point {
public:
  int id, x, y;
  Point() {}
  Point(int id, int x, int y) : id(id), x(x), y(y) {}
  void print() { printf("id:%d (%d, %d)\n", id, x, y); }
  bool inRange(Range r) {
    return r.sx <= x && x <= r.tx && r.sy <= y && y <= r.ty;
  }
};

bool compX(const Point &p1, const Point &p2) { return p1.x < p2.x; }
bool compY(const Point &p1, const Point &p2) { return p1.y < p2.y; }

Point P[MAX];
Node T[MAX];

int IDX = 0;
int makeTree(int l, int r, int depth) {
  if (!(l < r))
    return -1;
  int n = IDX;
  IDX++;
  int m = (l + r) / 2;

  if (depth % 2 == 0) {
    sort(P + l, P + r, compX);
  } else {
    sort(P + l, P + r, compY);
  }
  T[n].location = m;
  T[n].left = makeTree(l, m, depth + 1);
  T[n].right = makeTree(m + 1, r, depth + 1);
  return n;
}

vector<int> answer;

int find(int idx, Range range, int depth) {
  Point p = P[T[idx].location];
  if (p.inRange(range))
    answer.push_back(p.id);

  if (depth % 2 == 0) {
    if (T[idx].left != -1 && range.sx <= p.x)
      find(T[idx].left, range, depth + 1);
    if (T[idx].right != -1 && range.tx >= p.x)
      find(T[idx].right, range, depth + 1);
  } else {
    if (T[idx].left != -1 && range.sy <= p.y)
      find(T[idx].left, range, depth + 1);
    if (T[idx].right != -1 && range.ty >= p.y)
      find(T[idx].right, range, depth + 1);
  }
}

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int x, y;
    scanf("%d %d", &x, &y);
    P[i] = Point(i, x, y);
    T[i].right = T[i].left = -1;
  }
  makeTree(0, n, 0);

  int q;
  cin >> q;
  for (int i = 0; i < q; i++) {
    int sx, tx, sy, ty;
    scanf("%d %d %d %d", &sx, &tx, &sy, &ty);
    Range r = {sx, tx, sy, ty};
    find(0, r, 0);
    sort(answer.begin(), answer.end());
    for (int j = 0; j < answer.size(); j++)
      printf("%d\n", answer[j]);
    printf("\n");
    answer.clear();
  }
}
