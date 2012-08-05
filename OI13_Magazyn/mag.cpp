#include <cstdio>
#include <stdint.h>
#include <algorithm>

using namespace std;

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

    Shop() : x_(kInitX), y_(kInitY), visit_count_(kInitVisitCount) {};

    int x() const { return x_; }
    int y() const { return y_; }
    uint64_t visit_count() const { return visit_count_; }
    static int GetX(const Shop &s) { return s.x_; }
    static int GetY(const Shop &s) { return s.y_; }
    void Init(int x, int y, int visit_count);
    void Rotate();

  private:
    int x_;
    int y_;
    uint64_t visit_count_;
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

int GetNthCoord(const Shop sorted_shops[], uint64_t nth,
        int (*coord_accessor)(const Shop&)) {
    int i = 0;
    int retval = 0;
    uint64_t shops_passed = 0;
    while (shops_passed < nth) {
        retval = (*coord_accessor)(sorted_shops[i]);
        shops_passed += sorted_shops[i].visit_count();
        ++i;
    }
    return retval;
}

int GetMedianCoord(Shop shops[], int n, uint64_t median_visit,
        int (*coord_accessor)(const Shop&)) {
    Shop::Comparer shop_comparer = Shop::Comparer(coord_accessor);
    sort(shops, shops + n, shop_comparer);
    return GetNthCoord(shops, median_visit, coord_accessor);
}

int RoundUnrotatedCoord(float unrotated, int median) {
    return static_cast<int>(unrotated) +
        (unrotated < static_cast<float>(median) ? 1 : 0);
}

void DebugShops(int n, const Shop shops[]) {
    printf("shops:%d\n", n);
    for (int i = 0; i < n; ++i)
        printf(" x:%d y:%d\n", shops[i].x(), shops[i].y());
}

int main() {
    int n = 0;
    uint64_t total_visit_count = 0;
    Shop shops[kMaximumShopsNumber];
    Shop rotated_shops[kMaximumShopsNumber];

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int x, y;
        uint64_t visit_count;
        scanf("%d%d%lu", &x, &y, &visit_count);
        total_visit_count += visit_count;
        shops[i].Init(x, y, visit_count);
        rotated_shops[i].Init(x, y, visit_count);
        rotated_shops[i].Rotate();
    }

    const uint64_t median_visit = (total_visit_count + 1) / 2;

    const int best_x_rotated = GetMedianCoord(rotated_shops, n,
                                              median_visit,
                                              &Shop::GetX);
    const int best_y_rotated = GetMedianCoord(rotated_shops, n,
                                              median_visit,
                                              &Shop::GetY);

    if ((best_x_rotated + best_y_rotated) % 2 == 0) {
        printf("%d %d\n", (best_x_rotated + best_y_rotated) / 2,
               (best_y_rotated - best_x_rotated) / 2);
        return 0;
    }

    const float best_x_unrotated =
            static_cast<float>(best_x_rotated + best_y_rotated) / 2;
    const float best_y_unrotated =
            static_cast<float>(best_y_rotated - best_x_rotated) / 2;
    const int median_x = GetMedianCoord(shops, n, median_visit,
                                        &Shop::GetX);
    const int median_y = GetMedianCoord(shops, n, median_visit,
                                        &Shop::GetY);

    printf("%d %d\n", RoundUnrotatedCoord(best_x_unrotated, median_x),
           RoundUnrotatedCoord(best_y_unrotated, median_y));

    return 0;
}
