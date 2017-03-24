#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
#define EPS 1e-10
#define equals(a, b) (fabs(a - b) < EPS)

class Vector {
public:
  double x, y;
  Vector() {}
  Vector(double x, double y) : x(x), y(y) {}

  Vector operator+(Vector v) { return Vector(x + v.x, y + v.y); }
  Vector operator-(Vector v) { return Vector(x - v.x, y - v.y); }
  Vector operator*(double s) { return Vector(s * x, s * y); }
  Vector operator/(double s) { return Vector(s / x, s / y); }
  bool operator==(Vector v) { return equals(x - v.x, 0) && equals(y - v.y, 0); }
  double norm() { return x * x + y * y; }
  double abs() { return sqrt(norm()); }
  Vector rescale(double s) { return Vector(x, y) * (s / abs()); }
};

// inner product
double dot(Vector v1, Vector v2) { return v1.x * v2.x + v1.y * v2.y; }

// cross product
double cross(Vector v1, Vector v2) { return v1.x * v2.y - v1.y * v2.x; }

class Line {
public:
  Vector v1, v2;
  Line() {}
  Line(Vector v1, Vector v2) : v1(v1), v2(v2) {}
  // Vector unit() { return (v2 - v1) / (v2 - v1).abs(); }
};
class Segment {
public:
  Vector v1, v2;
  Segment() {}
  Segment(Vector v1, Vector v2) : v1(v1), v2(v2) {}
  operator Line() const { return Line(v1, v2); }
};

class Circle {
public:
  Vector v;
  double r;
  Circle() {}
  Circle(Vector v, double r) : v(v), r(r) {}
  Circle(double cx, double cy, double cr) {
    v = Vector(cx, cy);
    r = cr;
  }
};

class Polygon {
public:
  vector<Vector> v;
  Polygon() {}
  void push(Vector w) { v.push_back(w); }
};

bool is_parrallel(Vector a, Vector b) { return equals(cross(a, b), 0); }
bool is_parrallel(Line a, Line b) {
  return is_parrallel(a.v1 - a.v2, b.v1 - b.v2);
}
bool is_parrallel(Segment a, Segment b) {
  return is_parrallel((Line)a, (Line)b);
}

bool is_orthogonal(Vector a, Vector b) { return equals(dot(a, b), 0); }
bool is_orthogonal(Line a, Line b) {
  return is_orthogonal(a.v1 - a.v2, b.v1 - b.v2);
}

Vector project(Line l, Vector v) {
  Vector a = v - l.v1;
  Vector b = l.v2 - l.v1;
  return l.v1 + b * (dot(a, b) / b.norm());
}

Vector reflect(Line l, Vector v) { return v + (project(l, v) - v) * 2.0; }

double distance(Line l, Vector v) { return (v - project(l, v)).abs(); }
double distance(Vector v1, Vector v2) { return (v1 - v2).abs(); }
bool in_segment(Segment s, Vector v) {
  return dot(s.v2 - s.v1, v - s.v1) > 0 && dot(s.v1 - s.v2, v - s.v2) > 0;
}
double distance(Segment s, Vector v) {
  auto m = project((Line)s, v);
  if (in_segment(s, m)) {
    return distance(m, v);
  } else
    return min(distance(s.v1, v), distance(s.v2, v));
}
bool opposite(Line l, Vector v1, Vector v2) {
  auto a = l.v2 - l.v1;
  auto b = v1 - l.v1;
  auto c = v2 - l.v1;
  return cross(a, b) * cross(a, c) < 0;
}
enum Direction {
  ONLINE_FRONT = -2,
  CLOCKWISE = -1,
  ON_SEGMENT = 0,
  COUNTER_CLOCKWISE = 1,
  ONLINE_BACK = 2,
};
Direction ccw(Vector v0, Vector v1, Vector v2) {
  auto a = v1 - v0;
  auto b = v2 - v0;
  if (cross(a, b) > 0)
    return COUNTER_CLOCKWISE;
  if (cross(a, b) < 0)
    return CLOCKWISE;
  if (dot(a, b) < 0)
    return ONLINE_BACK;
  if (a.norm() < b.norm())
    return ONLINE_FRONT;
  return ON_SEGMENT;
}
void printd(Direction d) {
  switch (d) {
  case COUNTER_CLOCKWISE:
    printf("COUNTER_CLOCKWISE\n");
    break;
  case CLOCKWISE:
    printf("CLOCKWISE\n");
    break;
  case ONLINE_BACK:
    printf("ONLINE_BACK\n");
    break;
  case ONLINE_FRONT:
    printf("ONLINE_FRONT\n");
    break;
  case ON_SEGMENT:
    printf("ON_SEGMENT\n");
    break;
  }
}

bool intersect(Segment s1, Segment s2) {
  return ccw(s1.v1, s1.v2, s2.v1) * ccw(s1.v1, s1.v2, s2.v2) <= 0 &&
         ccw(s2.v1, s2.v2, s1.v1) * ccw(s2.v1, s2.v2, s1.v2) <= 0;
}

double distance(Segment s1, Segment s2) {
  if (intersect(s1, s2)) {
    return 0;
  }
  return min({distance(s1, s2.v1), distance(s1, s2.v2), distance(s2, s1.v1),
              distance(s2, s1.v2)});
}
Vector cross_point(Segment s1, Segment s2) {
  auto a = s1.v2 - s1.v1;
  auto d1 = abs(cross(a, s2.v1 - s1.v1));
  auto d2 = abs(cross(a, s2.v2 - s1.v1));
  auto r = d1 / (d1 + d2);
  return s2.v1 + (s2.v2 - s2.v1) * r;
}

pair<Vector, Vector> cross_circle_line(Circle c, Line l) {
  auto h = project(l, c.v);
  auto a = (h == c.v) ? c.r : sqrt(c.r * c.r - (h - c.v).norm());
  auto lv = l.v2 - l.v1;
  auto b = lv * (a / lv.abs());
  return make_pair(h + b, h - b);
}

// TODO: generalize
Vector rotate90(Vector v) { return Vector(-v.y, v.x); }

double calc_cos(double a, double b, double c) {
  return (b * b + c * c - a * a) / (2.0 * b * c);
}

pair<Vector, Vector> cross_circles(Circle c1, Circle c2) {
  double dist = distance(c1.v, c2.v);
  double arg_cos = calc_cos(c2.r, c1.r, dist);
  double arg_sin = sqrt((1.0 + arg_cos) * (1.0 - arg_cos));
  Vector cv = (c2.v - c1.v);
  Vector mv = c1.v + cv.rescale(c1.r * arg_cos);
  Vector hv = rotate90(cv).rescale(c1.r * arg_sin);
  return make_pair(mv - hv, mv + hv);
}

void sort_ans(Vector &a, Vector &b) {
  if (equals(a.x - b.x, 0)) {
    if (b.y < a.y)
      swap(a, b);
  } else {
    if (b.x < a.x)
      swap(a, b);
  }
}

int contains(Polygon pol, Vector v) {
  // in:2, on:1, otherwise:0
  const int in = 2;
  const int on = 1;
  const int otherwise = 0;
  int count = 0;
  for (int i = 0; i < pol.v.size(); i++) {
    auto v1 = pol.v[i] - v;
    auto v2 = pol.v[(i + 1) % pol.v.size()] - v;
    if (v1.y > v2.y)
      swap(v1, v2);
    if (equals(cross(v1, v2), 0) && dot(v1, v2) < EPS)
      return on;
    if (cross(v1, v2) > EPS && (v1.y * v2.y < 0 || equals(v1.y, 0)))
      count++;
  }
  return (count % 2 == 0) ? otherwise : in;
}

bool compare_vector(Vector a, Vector b) {
  return equals(a.y, b.y) ? a.x < b.x : a.y < b.y;
}

vector<Vector> convex_hull(vector<Vector> &vs) {
  sort(vs.begin(), vs.end(), compare_vector);

  // [1,2,3,4,5] -> [1,2.3,4,5,4,3,2,1]
  vector<Vector> vs_copy = vs;
  reverse(vs_copy.begin(), vs_copy.end());
  vs.insert(vs.end(), vs_copy.begin() + 1, vs_copy.end());

  vector<Vector> cv;
  cv.push_back(vs[0]);
  cv.push_back(vs[1]);
  for (int i = 2; i < vs.size(); i++) {
    for (int j = i; j > 1; j--) {
      auto base = cv[cv.size() - 2];
      if (cross(cv.back() - base, vs[i] - base) >= 0) // counter-clockwise
        break;
      else
        cv.pop_back();
    }
    cv.push_back(vs[i]);
  }
  cv.pop_back();
  return cv;
}

int main() {
  int n;
  cin >> n;
  vector<Vector> vs;
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    vs.push_back(Vector(x, y));
  }
  auto cv = convex_hull(vs);
  cout << cv.size() << endl;
  for (auto v : cv) {
    printf("%.0f %.0f\n", v.x, v.y);
  }
}
