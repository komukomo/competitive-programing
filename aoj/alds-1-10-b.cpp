#include <algorithm>
#include <iostream>
using namespace std;
static const int MAX = 100;
#define INF (1 << 30);

int store[MAX][MAX] = {{}};

struct matrix {
  int row;
  int col;
};

int nMul(matrix x, matrix y) { return x.row * x.col * y.col; }

matrix mult(matrix x, matrix y) {
  matrix mat;
  mat.row = x.row;
  mat.col = y.col;
  return mat;
}

int main() {
  matrix mat[MAX];
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> mat[i].row;
    cin >> mat[i].col;
  }

  int mcm[MAX][MAX] = {0};

  // mcm[i][j] is the minimum cost between mat[i] and mat[j]
  // m_0, m_1, m_2, m_3, m_4, m_5, ... m_n-1
  //       i         k         j
  for (int j = 1; j < n; j++) {
    for (int i = j-1; i >= 0; i--) {
      int minimum = INF;
      for (int k = i; k < j; k++) {
        int joint = nMul(mult(mat[i], mat[k]), mult(mat[k+1], mat[j]));
        int tmp = mcm[i][k] + mcm[k+1][j] + joint;
        minimum = min(minimum, tmp);
      }
      mcm[i][j] = minimum;
    }
  }

  cout << mcm[0][n-1] << endl;
}
