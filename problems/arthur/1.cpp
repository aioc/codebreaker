#include <cstdio>
#include <queue>
#include <set>
#include <vector>

using namespace std;

const int MAXV = 100000+5;

typedef vector< vector<int> > adj;

// Try to 2-colour this graph component, and return the maximum number
// of vertices of a single colour.
//
// Just do this using a simple breadth-first search through the component.
int measureTwoColouredComponent(int v, vector<int>& colour, adj& e) {
  queue<int> q;
  set<int> coloured;
  // First colour the vertices.  Since we are 2-colouring, there are no
  // decisions to make -- on each edge we change from colour i to (i+1)%2.
  q.push(v);
  colour[v] = 0;
  coloured.insert(v);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = 0; i < e[u].size(); i++) {
      int v = e[u][i];
      // Vertices u,v are adjacent.
      if (colour[v] == -1) {
        colour[v] = (colour[u]+1)%2;
        q.push(v);
        coloured.insert(v);
      }
    }
  }
  // Now count vertices with each colour.
  int cnt[3] = {};
  for(auto it=coloured.begin(); it!=coloured.end(); it++) {
    cnt[(int)colour[*it]]++;
  }
  return max(cnt[1], cnt[0]);
}

int main() {
  int n, nodes;
  adj e(MAXV);
  set<int> edges;

  // Read in the input data.
  scanf("%d%d", &nodes, &n);
  for (int i = 1; i <= n; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    e[u].push_back(v);
    e[v].push_back(u);
    edges.insert(min(u, v));
  }

  // Process each connected component.
  vector<int> colour(nodes + 1, -1);
  int res = 0;
  for(auto it=edges.begin(); it!=edges.end(); it++) {
    if (colour[*it] == -1) {
      res += measureTwoColouredComponent(*it, colour, e);
    }
  }

  // Done!
  printf("%d\n", res);
  return 0;
}
