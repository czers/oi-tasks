#include <cstdio>
#include <climits>
#include <algorithm>

typedef unsigned long int uint64t;

using std::sort;
using std::max;

const int kMaximumShopsNumber = 100000;

class Shop {
  public:
    class Comparer {
      public:
        Comparer(int (*coord_accessor)(const Shop&))
                : coord_accessor_(coord_accessor) {}
        bool operator()(const Shop &a, const Shop &b);
      private:
        int (*coord_accessor_)(const Shop&);
    };

    static const int kInitX = 0;
    static const int kInitY = 0;
    static const int kInitVisitCount = -1;

    Shop() : x_(kInitX), y_(kInitY), visit_count_(kInitVisitCount) {}

    int x() const { return x_; }
    int y() const { return y_; }
    uint64t visit_count() const { return visit_count_; }
    static int GetX(const Shop &s) { return s.x_; }
    static int GetY(const Shop &s) { return s.y_; }
    void Init(int x, int y, int visit_count);
    void Rotate();

  private:
    int x_;
    int y_;
    uint64t visit_count_;
};

bool Shop::Comparer::operator()(const Shop &a, const Shop &b) {
    return (*coord_accessor_)(a) < (*coord_accessor_)(b);
}

void Shop::Init(int x, int y, int visit_count) {
    x_ = x;
    y_ = y;
    visit_count_ = visit_count;
}

void Shop::Rotate() {
    int x = x_;
    x_ = x - y_;
    y_ = x + y_;
}

int GetNthCoord(const Shop sorted_shops[], uint64t nth,
        int (*coord_accessor)(const Shop&)) {
    int i = 0;
    int retval = 0;
    uint64t shops_passed = 0;
    while (shops_passed < nth) {
        retval = (*coord_accessor)(sorted_shops[i]);
        shops_passed += sorted_shops[i].visit_count();
        ++i;
    }
    return retval;
}

int GetMedianCoord(Shop shops[], int n, uint64t median_visit,
        int (*coord_accessor)(const Shop&)) {
    Shop::Comparer shop_comparer = Shop::Comparer(coord_accessor);
    sort(shops, shops + n, shop_comparer);
    return GetNthCoord(shops, median_visit, coord_accessor);
}

int Distance(int x1, int y1, int x2, int y2) {
    return max(abs(x1 - x2), abs(y1 - y2));
}

uint64t TotalDistance(int x, int y, const Shop shops[], int n) {
    uint64t total = 0;
    for (int i = 0; i < n; ++i)
        total += shops[i].visit_count() * static_cast<uint64t>(
                Distance(x, y, shops[i].x(), shops[i].y()));
    return total;
}

int main() {
    int n = 0;
    uint64t total_visit_count = 0;
    Shop shops[kMaximumShopsNumber];
    Shop rotated_shops[kMaximumShopsNumber];

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int x, y, visit_count;
        scanf("%d%d%d", &x, &y, &visit_count);
        total_visit_count += visit_count;
        shops[i].Init(x, y, static_cast<uint64t>(visit_count));
        rotated_shops[i].Init(x, y, static_cast<uint64t>(visit_count));
        rotated_shops[i].Rotate();
    }

    const uint64t median_visit = (total_visit_count + 1) / 2;
    const int best_x_rotated = GetMedianCoord(rotated_shops, n,
                                              median_visit,
                                              &Shop::GetX);
    const int best_y_rotated = GetMedianCoord(rotated_shops, n,
                                              median_visit,
                                              &Shop::GetY);
    const int x = (best_x_rotated + best_y_rotated) / 2;
    const int y = (best_y_rotated - best_x_rotated) / 2;
    const int xs[] = { 0, 1, 0, 1 };
    const int ys[] = { 0, 1, 1, 0 };
    int best_x = x;
    int best_y = y;
    uint64t lowest_total_distance = ULONG_MAX;
    for (int i = 0; i < 4; i++) {
        int current_x = x + xs[i];
        int current_y = y + ys[i];
        uint64t current_distance = TotalDistance(current_x, current_y,
                                                 shops, n);
        //printf("%d %d TD: %lu\n", current_x, current_y, current_distance);
        if (current_distance < lowest_total_distance) {
            lowest_total_distance = current_distance;
            best_x = current_x;
            best_y = current_y;
        }
    }
    printf("%d %d\n", best_x, best_y);
    return 0;
}
