#include <cstdio>
#include <set>

const int kMaxN = 50000;

class MapPoint {
  public:
    int x;
    int y;
    bool is_extraction;
} points[2*kMaxN];

int pair[kMaxN];

struct XAxisSort {
    bool operator()(const int &a, const int &b) {
        if (points[a].x == points[b].x)
            return points[a].y > points[b].y;
        return points[a].x < points[b].x;
    }
};
typedef std::set<int, XAxisSort>::iterator XIter;

struct YAxisSort {
    bool operator()(const int &a, const int &b) {
        if (points[a].y == points[b].y)
            return points[a].x > points[b].x;
        return points[a].y < points[b].y;
    }
};
typedef std::set<int, YAxisSort>::iterator YIter;

int main() {
    int n;
    scanf("%d", &n);
    std::set<int, XAxisSort> x_sorted;
    int i;
    for (i = 0; i < n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        points[i].x = x;
        points[i].y = y;
        points[i].is_extraction = true;
        x_sorted.insert(i);
    }
    for (/**/; i < 2 * n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        points[i].x = x;
        points[i].y = y;
        points[i].is_extraction = false;
        x_sorted.insert(i);
    }
    std::set<int, YAxisSort> y_sorted;
    long long int total_cost = 0;
    for (XIter it = x_sorted.begin(); it != x_sorted.end(); ++it) {
        if (points[*it].is_extraction) {
            y_sorted.insert(*it);
        } else {
            YIter ext = y_sorted.upper_bound(*it);
            pair[*ext] = (*it) - n;
            total_cost += (long long int) (points[*ext].y - points[*it].y +
                                           points[*it].x - points[*ext].x);
            y_sorted.erase(ext);
        }
    }
    printf("%lld\n", total_cost);
    for (i = 0; i < n; i++) {
        printf("%d %d\n", i + 1, pair[i] + 1);
    }
    return 0;
}
