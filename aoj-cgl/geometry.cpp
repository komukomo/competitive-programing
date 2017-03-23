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
  double norm() { return x * x + y * y; }
  double abs() { return sqrt(norm()); }
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
};
class Segment {
public:
  Vector v1, v2;
  Segment() {}
  Segment(Vector v1, Vector v2) : v1(v1), v2(v2) {}
  operator Line() const { return Line(v1, v2); }
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
  auto r = d1/(d1+d2);
  return s2.v1 + (s2.v2 - s2.v1) * r;
}

int main() {
  int nq;
  cin >> nq;
  for (int i = 0; i < nq; i++) {
    Segment seg[2];
    for (int j = 0; j < 2; j++) {
      int x0, y0, x1, y1;
      cin >> x0 >> y0 >> x1 >> y1;
      seg[j] = Segment(Vector(x0, y0), Vector(x1, y1));
    }
    auto v = cross_point(seg[0], seg[1]);
    printf("%.10f %.10f\n", v.x, v.y);
  }
}
