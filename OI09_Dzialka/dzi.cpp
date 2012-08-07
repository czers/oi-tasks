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
        printf("Line: %d Usable:", lines_left);
        for (int i = 0; i < n + 2; i++)
            printf(" %d", usable_up[i]);
        printf("\n");
        stack<pair<int, int> > candidates;
        //candidates.push(make_pair<int, int>(0, 0));
        pair<int, int> first_candidate;
        pair<int, int> second_candidate;
        for (int i = 1; i <= n + 1; ++i) {
            bool popped = false;
            if (!candidates.empty())
            {
                first_candidate = candidates.top();
                printf("1ToppedA: %d,%d\n", first_candidate.first,
                       first_candidate.second);
            }
            while (!candidates.empty() && first_candidate.second >
                   usable_up[i]) {
                int possible_best = (i - first_candidate.first) *
                    usable_up[i];
                if (possible_best > best_rectangle)
                    best_rectangle = possible_best;
                printf("Possible best rectangle (i:%d,G:%d): %d\n", i,
                       usable_up[i], possible_best);
                second_candidate = candidates.top();
                candidates.pop();
                popped = true;
                printf("2Popped: %d,%d\n", second_candidate.first,
                       second_candidate.second);
                if (!candidates.empty()) {
                    first_candidate = candidates.top();
                    printf("1ToppedB: %d,%d\n", first_candidate.first,
                           first_candidate.second);
                }
            }
            if ((candidates.empty() && usable_up[i] > 0) ||
                    first_candidate.second < usable_up[i]) {
                if (popped)
                    candidates.push(make_pair<int, int>(second_candidate.first, usable_up[i]));
                else
                    candidates.push(make_pair<int, int>(i, usable_up[i]));
                printf("Pushed: %d,%d\n", candidates.top().first,
                       candidates.top().second);
            }
        }
    }
    printf("%d\n", best_rectangle);
    return 0;
}
