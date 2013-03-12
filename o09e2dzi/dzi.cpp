#include <cstdio>
#include <stack>
#include <utility>

const int kMaxN = 2000;

using std::stack;
using std::pair;
using std::make_pair;

int main() {
    int n, lines_left;
    int best_rectangle = 0;
    int usable_up[kMaxN + 2];
    for (int i = 0; i < kMaxN + 2; ++i)
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
        stack<pair<int, int> > candidates;
        candidates.push(make_pair(0, 0));
        for (int i = 1; i <= n + 1; ++i) {
            int new_start = i;
            while (usable_up[i] < candidates.top().second) {
                pair<int, int> candidate = candidates.top();
                candidates.pop();
                int possible_best = candidate.second * (i - candidate.first);
                if (possible_best > best_rectangle)
                    best_rectangle = possible_best;
                new_start = candidate.first;
            }
            if (candidates.top().second < usable_up[i])
                candidates.push(make_pair(new_start, usable_up[i]));
        }
    }
    printf("%d\n", best_rectangle);
    return 0;
}
