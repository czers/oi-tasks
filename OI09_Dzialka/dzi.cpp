#include <cstdio>
#include <stack>
#include <utility>

const int kMaxN = 2000;

using std::stack;
using std::pair;

int main() {
    int n, lines_left;
    int best_rectangle = 0;
    int usable_up[kMaxN + 2];
    for (int i = 0; i < kMaxN + 2; i++)
        usable_up[i] = 0;
    scanf("%d", &n);
    lines_left = n;
    while (lines_left--) {
        for (int i = 1; i <= n; ++i) {
            int busy;
            scanf("%d", &busy);
            if (busy)
                usable_up[i] = 0;
            else
                ++usable_up[i];
        }
    }
    return 0;
}
