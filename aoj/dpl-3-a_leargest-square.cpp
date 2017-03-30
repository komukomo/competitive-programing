#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;
static const int HMAX = 1401;
static const int WMAX = 1401;

int tiles[HMAX][WMAX] = {0};

void print_tiles(int h, int w) {
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      cout << tiles[i][j] << " ";
    }
    cout << endl;
  }
}

// side-effects (to tiles)
int leargest_square(int height, int width, int ans_init) {
  int ans = ans_init;
  for (int i = 1; i < height; i++) {
    for (int j = 1; j < width; j++) {
      if (tiles[i][j] != 0) {
        tiles[i][j] =
            min({tiles[i - 1][j], tiles[i][j - 1], tiles[i - 1][j - 1]}) + 1;
        ans = max(ans, tiles[i][j]);
      }
    }
  }
  return ans * ans;
}

struct Rect {
  int height;
  int left;
};

// side-effects (to tiles)
int leargest_rectanble(int height, int width) {
  // mkae histgrams
  for (int i = 1; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (tiles[i][j] != 0) {
        tiles[i][j] = tiles[i - 1][j] + 1;
      }
    }
  }

  int maxsize = 0;
  stack<Rect> st;
  for (int i = 0; i < height; i++) {
    // calc the rectangle size of the i-th histgram
    tiles[i][width] = 0; // sentinel
    for (int j = 0; j < width + 1; j++) {
      auto rect = Rect{tiles[i][j], j};
      if (st.empty() || st.top().height < rect.height) {
        st.push(rect);
      } else if (st.top().height > rect.height) {
        Rect r;
        int left_store;
        while (!st.empty()) {
          r = st.top();
          if (r.height <= rect.height)
            break;
          int size = r.height * (rect.left - r.left);
          maxsize = max(size, maxsize);
          left_store = r.left;
          st.pop();
        }
        if (r.height < rect.height) {
          rect.left = left_store;
          st.push(rect);
        }
      }
    }
  }

  return maxsize;
}

#define BLOCK 1
int main() {
  int height, width;
  int ans_init = 0;
  cin >> height >> width;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      int tmp;
      cin >> tmp;
      tiles[i][j] = tmp == BLOCK ? 0 : 1;
      ans_init = max(ans_init, tiles[i][j]);
    }
  }
  cout << leargest_rectanble(height, width) << endl;
}
