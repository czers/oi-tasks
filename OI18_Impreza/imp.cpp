#include <cstdio>

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  bool edges[n][n];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      edges[i][j] = false;
    }
  }
  while (m--) {
    int a, b;
    scanf("%d%d", &a, &b);
    a--;
    b--;
    edges[a][b] = edges[b][a] = true;
  }
  bool invited[n];
  for (int i = 0; i < n; i++) {
    invited[i] = true;
  }
  for (int i = 0; i < n; i++) {
    if (invited[i]) {
      for (int j = i + 1; j < n; j++) {
        if (invited[j] && !edges[i][j]) {
          invited[i] = invited[j] = false;
          j = n;
        }
      }
    }
  }
  for (int i = 0, count = 0; 3 * count < n; i++) {
    if (invited[i]) {
      count++;
      printf("%d ", i + 1);
    }
  }
  printf("\n");
  return 0;
}
