#include <cstdio>
#include <cstdlib>
#include <limits>
#include <algorithm>

const int kMaxN = 20000;
const int kMaxK = 100;
const int kMaxA = 1000000;
const int kLo = 1;
const int kEq = 2;
const int kGr = 3;

template<class T>
class RangeTree {
  public:
    RangeTree(T (*operation)(const T&, const T&), T init_with,
            int capacity)
        : operation_(operation) {
        int rounded_capacity = 1;
        while (rounded_capacity < capacity)
            rounded_capacity *= 2;
        rounded_capacity_ = rounded_capacity;
        tree_ = new T[2 * rounded_capacity - 1];
        for (int i = 0; i < 2 * capacity; ++i)
            tree_[i] = init_with;
    }

    T GetValueOnInterval(int left, int right) const {
//        printf("[Query]\n");
        return GetValueOnInterval(0, 0, rounded_capacity_ - 1, left, right);
    }

    void UpdatePoint(int point, T value);

    void PrintTree() {
        int idx = 0;
        int level_size = 1;
        while (level_size <= rounded_capacity_) {
            for (int i = 0; i < level_size; i++) {
                printf("%d ", tree_[idx + i]);
            }
            printf("\n");
            idx += level_size;
            level_size *= 2;
        }
    }

  private:
    T* tree_;
    T (*operation_)(const T&, const T&);
    int rounded_capacity_;

    static int GetLeftChild(int idx) {
        return idx * 2 + 1;
    }

    static int GetRightChild(int idx) {
        return idx * 2 + 2;
    }

    static int GetParent(int idx) {
        return (idx - 1) / 2;
    }

    static int GetSubtreeSize(int left, int right) {
        return right - left + 1;
    }

    static bool IsPointInLeftChild(int point, int left, int right) {
        return point < (left + GetSubtreeSize(left, right) / 2);
    }

    static bool IsPointInRightChild(int point, int left, int right) {
        return (left + GetSubtreeSize(left, right) / 2) <= point;
    }

    T GetValueOnInterval(int idx, int subtree_left, int subtree_right,
            int searching_left, int searching_right) const;
};

template<class T>
T RangeTree<T>::GetValueOnInterval(int idx, int subtree_left,
        int subtree_right, int searching_left, int searching_right) const {
//    printf("GVOI: %d v: %d sl: %d sr: %d sel: %d ser: %d\n", idx,
//            tree_[idx], subtree_left, subtree_right, searching_left,
//            searching_right);
    if (subtree_left == searching_left && subtree_right == searching_right)
        return tree_[idx];
    const int left_child_boundary = subtree_left - 1
                                    + GetSubtreeSize(subtree_left,
                                                     subtree_right) / 2;
    T left_result;
    if (IsPointInLeftChild(searching_left, subtree_left, subtree_right)) {
        left_result = GetValueOnInterval(GetLeftChild(idx),
                                         subtree_left,
                                         left_child_boundary,
                                         searching_left,
                                         std::min(searching_right,
                                                  left_child_boundary));
    }
    const int right_child_boundary = left_child_boundary + 1;
    T right_result;
    if (IsPointInRightChild(searching_right, subtree_left, subtree_right)) {
        right_result = GetValueOnInterval(GetRightChild(idx),
                                          right_child_boundary,
                                          subtree_right,
                                          std::max(searching_left,
                                                   right_child_boundary),
                                          searching_right);
    }
    if (IsPointInLeftChild(searching_right, subtree_left, subtree_right))
        return left_result;
    if (IsPointInRightChild(searching_left, subtree_left, subtree_right))
        return right_result;
    return (*operation_)(left_result, right_result);
}

template<class T>
void RangeTree<T>::UpdatePoint(int point, T value) {
    int idx = rounded_capacity_ + point - 1;
    tree_[idx] = value;
    while (idx != 0) {
        idx = GetParent(idx);
        tree_[idx] = (*operation_)(tree_[GetLeftChild(idx)],
                                   tree_[GetRightChild(idx)]);
    }
}

int max_(const int& a, const int& b) {
//    printf("Max %d & %d : %d\n", a, b, std::max(a, b));
    return std::max(a, b);
}

bool cmp_(const int& a, const int& b, const int& cmp) {
    if (cmp == kEq)
        return a == b;
    else if (cmp == kGr)
        return a < b;
    else if (cmp == kLo)
        return a > b;
}

class FindR {
  public:
    FindR() : value_(std::numeric_limits<int>::min()),
            original_index_(std::numeric_limits<int>::min()) {}

    FindR(int value, int original_index) :
            value_(value), original_index_(original_index) {}

    int value() const {
        return value_;
    }

    int original_index() const {
        return original_index_;
    }

  private:
    int value_;
    int original_index_;
};

struct FindRComparer {
    bool operator()(const FindR& a, const FindR& b) {
        if (a.value() != b.value())
            return a.value() < b.value();
        return a.original_index() < b.original_index();
    }
};

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    int a[kMaxN];
    int a_sorted[kMaxN];
    FindR fr[kMaxN];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        fr[i] = FindR(a[i], i);
        a_sorted[i] = a[i];
    }
    std::sort(a_sorted, a_sorted + n);
    int l[kMaxN];
    int u[kMaxN];
    int equal[kMaxA + 1];
    for (int i = 0; i < n; i++) {
        l[i] = std::lower_bound(a_sorted, a_sorted + n, a[i]) - a_sorted;
        u[i] = std::upper_bound(a_sorted, a_sorted + n, a[i]) - a_sorted - 1;
        equal[i] = std::numeric_limits<int>::min();
    }
    std::sort(fr, fr + n, FindRComparer());
    int r[kMaxN];
    int p[kMaxN];
    for (int i = 0; i < n; i++) {
        r[i] = fr[i].original_index();
        p[fr[i].original_index()] = i;
    }
    scanf("\n");
    int s[kMaxK];
    for (int i = 0; i < k; i++) {
        char c;
        scanf("%c ", &c);
        if (c == '<')
            s[i] = kGr;
        else if (c == '>')
            s[i] = kLo;
        else if (c == '=')
            s[i] = kEq;
    }
//    for (int i = 0; i < n; i++)
//        printf("a[%d] = %d  r=%d p=%d l=%d u=%d\n", i, a[i], r[i], p[i], l[i],
//                u[i]); 
    RangeTree<int> greater = RangeTree<int>(max_,
            std::numeric_limits<int>::min(), n);
    RangeTree<int> lower = RangeTree<int>(max_,
            std::numeric_limits<int>::min(), n);
    int position_best[kMaxN];
    for (int i = 0; i < n; i++) {
        int best = equal[a[i]]; 
        if (l[i] > 0)
            best = std::max(best, greater.GetValueOnInterval(0, l[i] - 1));
        if (u[i] < n - 1)
            best = std::max(best, lower.GetValueOnInterval(u[i] + 1, n - 1));
        if (best == std::numeric_limits<int>::min())
            best = 0;
        const int mod_best = best % k;
        ++best;
        position_best[i] = best;
        if (s[mod_best] == kGr)
            greater.UpdatePoint(p[i], best);
        else if (s[mod_best] == kLo)
            lower.UpdatePoint(p[i], best);
        else if (s[mod_best] == kEq)
            equal[a[i]] = std::max(equal[a[i]], best);
    }
    int total_best = std::numeric_limits<int>::min();
    for (int i = 0; i < n; i++)
        total_best = std::max(total_best, equal[a[i]]);
    total_best = std::max(total_best, greater.GetValueOnInterval(0, n - 1));
    total_best = std::max(total_best, lower.GetValueOnInterval(0, n - 1));
    printf("%d\n", total_best);
    int idx = n - 1;
    while (position_best[idx] != total_best)
        --idx;
//    for (int i = 0; i < n; i++)
//        printf("pb[%d]=%d\n", i, position_best[i]);
    int length_to_be_found = total_best - 1;
    bool used_in_final[kMaxN];
    used_in_final[idx] = true;
    while (length_to_be_found) {
        int last_value = a[idx];
        --idx;
        while (position_best[idx] != length_to_be_found || !cmp_(a[idx],
                    last_value, s[(length_to_be_found - 1) % k]))
            --idx;
        used_in_final[idx] = true;
        last_value = a[idx];
        --length_to_be_found;
    }
    for (int i = 0; i < n; i++)
        if (used_in_final[i])
            printf("%d ", a[i]);
    printf("\n");
//    for (int i = 0; i < 10; i++)
//        T.UpdatePoint(i, i);
//    T.PrintTree();
//    for (int i = 0; i < 5; i++)
//        printf("%d\n", T.GetValueOnInterval(i, 9 - i));
    return 0;
}
