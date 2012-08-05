#include <cstdio>
#include <algorithm>

using namespace std;

const int kMaximumShopsNumber = 100000;

class Shop {
  public:
    struct XComparer {
        bool operator()(const Shop &x, const Shop &y);
    };
    struct YComparer {
        bool operator()(const Shop &x, const Shop &y);
    };

    static const int kInitX = 0;
    static const int kInitY = 0;
    static const int kInitVisitCount = -1;

    Shop() : x_(kInitX), y_(kInitY), visit_count_(kInitVisitCount) {};

    int x() const { return x_; }
    int y() const { return y_; }
    int visit_count() const { return visit_count_; }
    void Init(int x, int y, int visit_count);
    void Rotate();

  private:
    int x_;
    int y_;
    int visit_count_;
};

bool Shop::XComparer::operator()(const Shop &a, const Shop &b) {
    return a.x_ < b.x_;
}

bool Shop::YComparer::operator()(const Shop &a, const Shop &b) {
    return a.y_ < b.y_;
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

int GetNthX(const Shop shops[], int nth) {
    int i = 0;
    int retval = 0;
    int shops_passed = 0;
    while (shops_passed < nth) {
        retval = shops[i].x();
        shops_passed += shops[i].visit_count();
        ++i;
    }
    return retval;
}

int GetNthY(const Shop shops[], int nth) {
    int i = 0;
    int retval = 0;
    int shops_passed = 0;
    while (shops_passed < nth) {
        retval = shops[i].y();
        shops_passed += shops[i].visit_count();
        ++i;
    }
    return retval;
}

int main() {
    int n = 0;
    int total_visit_count = 0;
    Shop shops[kMaximumShopsNumber];
    Shop rotated_shops[kMaximumShopsNumber];

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int x, y, visit_count;
        scanf("%d%d%d", &x, &y, &visit_count);
        total_visit_count += visit_count;
        shops[i].Init(x, y, visit_count);
        rotated_shops[i].Init(x, y, visit_count);
        rotated_shops[i].Rotate();
    }

    const int median_visit = (total_visit_count + 1) / 2;

    Shop::XComparer shop_x_comparer;
    sort(rotated_shops, rotated_shops + n, shop_x_comparer);
    const int best_x_rotated = GetNthX(rotated_shops, median_visit);
    sort(shops, shops + n, shop_x_comparer);
    const int median_x = GetNthX(shops, median_visit);

    Shop::YComparer shop_y_comparer;
    sort(rotated_shops, rotated_shops + n, shop_y_comparer);
    const int best_y_rotated = GetNthY(rotated_shops, median_visit);
    sort(shops, shops + n, shop_y_comparer);
    const int median_y = GetNthY(shops, median_visit);

    if ((best_x_rotated + best_y_rotated) % 2 == 0) {
        printf("%d %d", (best_x_rotated + best_y_rotated) / 2,
               (best_x_rotated - best_y_rotated) / 2);
        return 0;
    }

    const float best_x_unrotated
        = static_cast<float>(best_x_rotated + best_y_rotated) / 2;
    if (best_x_unrotated < static_cast<float>(median_x))
        printf("%d", median_x);
    else
        printf("%d", median_x + 1);

    printf(" ");

    const float best_y_unrotated
        = static_cast<float>(best_x_rotated - best_y_rotated) / 2;
    if (best_y_unrotated < static_cast<float>(median_y))
        printf("%d", median_y);
    else
        printf("%d", median_y + 1);

    return 0;
}
