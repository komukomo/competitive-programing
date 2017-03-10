#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
static const int NMAX = 10000;
#define INF (1 << 30)

// Dijkstra's Algorithm
int main() {
  int n;
  cin >> n;
  vector<pair<int, int>> adj[NMAX];

  for (int i = 0; i < n; i++) {
    int id, nn;
    cin >> id >> nn;
    for (int j = 0; j < nn; j++) {
      int to, weight;
      cin >> to >> weight;
      // use negative weights for priority_queue
      adj[id].push_back(make_pair(-weight, to));
    }
  }

  bool visited[n];
  int dist[n];
  for (int i = 0; i < n; i++) {
    visited[i] = false;
    dist[i] = -INF;
  }

  priority_queue<pair<int, int>> distQ;

  // add node 0
  for (int i = 0; i < adj[0].size(); i++) {
    distQ.push(adj[0][i]);
    int weight = adj[0][i].first;
    int id = adj[0][i].second;
    dist[id] = weight;
  }
  visited[0] = true;

  while (!distQ.empty()) {
    // find nearest node
    int minnode = distQ.top().second;
    distQ.pop();

    // add node
    visited[minnode] = true;

    // update dist
    for (int i = 0; i < adj[minnode].size(); i++) {
      int weight = adj[minnode][i].first;
      int id = adj[minnode][i].second;

      if (visited[id] == false) {
        int newWeight = dist[minnode] + weight;
        if (-newWeight < -dist[id]) {
          distQ.push(make_pair(newWeight, id));
          dist[id] = newWeight;
        }
      }
    }
  }

  dist[0] = 0;
  for (int i = 0; i < n; i++)
    cout << i << " " << -dist[i] << endl;
}
