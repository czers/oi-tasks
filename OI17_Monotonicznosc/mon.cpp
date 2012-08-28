#include <cstdio>
#include <cstdlib>
#include <algorithm>

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

int main() {
    RangeTree<int> T = RangeTree<int>(max_, 0, 10);
    for (int i = 0; i < 10; i++)
        T.UpdatePoint(i, i);
//    T.PrintTree();
    for (int i = 0; i < 5; i++)
        printf("%d\n", T.GetValueOnInterval(i, 9 - i));
    return 0;
}
