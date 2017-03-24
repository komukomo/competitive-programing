#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;

enum Eptype {
  BOTTOM = 0,
  LEFT = 1,
  TOP = 2,
};

class EndPoint {
public:
  int x, y;
  Eptype t;
  int rightx; // empty if not LEFT
  EndPoint() {}
  EndPoint(int x, int y, Eptype t) : x(x), y(y), t(t) {}
  EndPoint(int x, int y, Eptype t, int rightx) : x(x), y(y), t(t),rightx(rightx) {}
  bool operator<(const EndPoint ep) { // for sort
    if (y == ep.y)
      return t < ep.t;
    return y < ep.y;
  }
};

int manhattan_scan(vector<EndPoint> &epts) {
  sort(epts.begin(), epts.end());
  set<int> xs;
  int count = 0;

  for (int i = 0; i < epts.size(); i++) {
    EndPoint ept = epts[i];
    if (ept.t == BOTTOM) {
      xs.insert(ept.x);
    } else if (ept.t == TOP) {
      xs.erase(ept.x);
    } else if (ept.t == LEFT) {
      auto lb = lower_bound(xs.begin(), xs.end(), ept.x);
      auto ub = upper_bound(xs.begin(), xs.end(), ept.rightx);
      count += distance(lb, ub);
    }
  }
  return count;
}

int main() {
  int n;
  cin >> n;
  vector<EndPoint> epts;
  for (int i = 0; i < n; i++) {
    Eptype t1, t2;
    int x1, y1, x2, y2;
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    if (x1 == x2) {
      t1 = BOTTOM;
      t2 = TOP;
      if (y1 > y2) {
        t1 = TOP;
        t2 = BOTTOM;
      }
      epts.push_back(EndPoint(x1, y1, t1));
      epts.push_back(EndPoint(x2, y2, t2));
    } else {
      // push only leftside with right-x
      if (x1 < x2) {
        epts.push_back(EndPoint(x1, y1, LEFT, x2));
      } else {
        epts.push_back(EndPoint(x2, y2, LEFT, x1));
      }
    }
  }
  cout << manhattan_scan(epts) << endl;
}
