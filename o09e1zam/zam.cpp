#include <cstdio>
#include <vector>
#include <queue>
#include <stack>

#define MAXN 100
#define MAXS 1001

using std::vector;
using std::queue;
using std::stack;

class Node {
  public:
    Node(int chamber, int path_cost, Node *from)
        : chamber_(chamber), path_cost_(path_cost), from_(from) {}
    int chamber() { return chamber_; }
    int path_cost() { return path_cost_; }
    Node *from() { return from_; }
  private:
    int chamber_;
    int path_cost_;
    Node *from_;
};

int main() {
  int n, m, w, k, s;
  scanf("%d%d%d%d%d", &n, &m, &w, &k, &s);
  w--;
  k--;
  int cost[MAXN];
  for (int i = 0; i < n; i++) {
    scanf("%d", &cost[i]);
  }
  vector<int> edges[MAXN];
  for (int i = 0; i < m; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    a--;
    b--;
    edges[a].push_back(b);
    edges[b].push_back(a);
  }
  Node *nodes[MAXN][MAXS];
  for (int i = 0; i < MAXN; i++)
      for (int j = 0; j < MAXS; j++)
          nodes[i][j] = (Node*)NULL;
  queue<Node*> bfs;
  Node *start_node = new Node(w, cost[w], (Node*)NULL);
  Node *end_node = (Node*)NULL;
  bfs.push(start_node);
  while (!bfs.empty() && end_node == NULL) {
      Node *current_node = bfs.front();
      bfs.pop();
      int current_chamber = current_node->chamber();
      int current_path_cost = current_node->path_cost();
      if (current_chamber == k && current_path_cost == s) {
          end_node = current_node;
      } else if (current_path_cost < s) {
          for (unsigned int i = 0; i < edges[current_chamber].size(); i++) {
              int next_chamber = edges[current_chamber][i];
              int next_cost = current_path_cost + cost[next_chamber];
              if (next_cost <= s &&
                        nodes[next_chamber][next_cost] == (Node*)NULL) {
                  Node *next_node = new Node(
                      next_chamber, current_path_cost + cost[next_chamber],
                      current_node);
                  nodes[next_chamber][next_cost] = next_node;
                  bfs.push(next_node);
              }
          }
      }
  }
  stack<int> path;
  Node *path_node = end_node;
  while (path_node != (Node*)NULL) {
      path.push(path_node->chamber());
      path_node = path_node->from();
  }
  while (!path.empty()) {
      printf("%d ", path.top() + 1);
      path.pop();
  }
  return 0;
}
