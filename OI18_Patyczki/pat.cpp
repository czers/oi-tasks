#include <cstdio>
#include <algorithm>
#include <vector>

class Stick {
 public:
  Stick(int color_, int length_) : color(color_), length(length_) {}
  int color;
  int length;
};

struct StickComparer {
  bool operator()(const Stick &a, const Stick &b) {
    if (a.length == b.length) {
      return a.color < b.color;
    }
    return a.length < b.length;
  }
};

int main() {
  int color_count;
  scanf("%d", &color_count);
  std::vector<Stick> sticks;
  for (int color = 1; color <= color_count; color++) {
    int stick_count;
    scanf("%d", &stick_count);
    while (stick_count--) {
      int stick_length;
      scanf("%d", &stick_length);
      sticks.push_back(Stick(color, stick_length));
    }
  }
  std::sort(sticks.begin(), sticks.end(), StickComparer());
  int p1 = -1, p2 = -1, p3 = 0;
  for (int i = 0; p1 == -1 || p2 == -1; i++) {
    if (p2 == -1 && sticks[i].color != sticks[p3].color) {
      p2 = i;
    } else if (p2 != -1 && sticks[i].color != sticks[p3].color &&
               sticks[i].color != sticks[p2].color) {
      p1 = i;
    } else if (p2 != -1 && sticks[i].color == sticks[p2].color) {
      p2 = i;
    } else if (sticks[i].color == sticks[p3].color) {
      p3 = i;
    }
  }
  if (sticks[p2].length + sticks[p3].length > sticks[p1].length) {
    printf("%d %d %d %d %d %d\n", sticks[p1].color, sticks[p1].length,
           sticks[p2].color, sticks[p2].length, sticks[p3].color,
           sticks[p3].length);
    return 0;
  }
  for (int p = p1 + 1; p < sticks.size(); p++) {
    if (sticks[p].color != sticks[p1].color &&
        sticks[p].color != sticks[p2].color) {
      p3 = p2;
      p2 = p1;
      p1 = p;
    } else if (sticks[p].color == sticks[p2].color) {
      p2 = p1;
      p1 = p;
    } else if (sticks[p].color == sticks[p1].color) {
      p1 = p;
    }
    if (sticks[p2].length + sticks[p3].length > sticks[p1].length) {
      printf("%d %d %d %d %d %d\n", sticks[p1].color, sticks[p1].length,
             sticks[p2].color, sticks[p2].length, sticks[p3].color,
             sticks[p3].length);
      return 0;
    }
  }
  printf("NIE\n");
  return 0;
}
