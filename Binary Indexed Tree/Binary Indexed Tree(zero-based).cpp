/* The ith element of the tree is the sum of i&(i+1)..i */
#include <vector>
#include <cstdio>
#include "Binary Indexed Tree.h"

inline int remove_consecutive_right(int x) {
    return x & (x + 1);
}

inline int get_consecutive_right(int x) {
    return (x ^ (x + 1)) >> 1;
}

inline int highest_consecutive_right(int x) {
    return (get_consecutive_right(x) + 1) >> 1;
}

Binary_indexed_tree::Binary_indexed_tree() {
}

Binary_indexed_tree::Binary_indexed_tree(
    const std::vector<int>& initial_vector
) {
    tree.resize(initial_vector.size());
    for (int i = 0; i < initial_vector.size(); ++i) {
        tree[i] = 0;
        increase(i, initial_vector[i]);
    }
}

Binary_indexed_tree::Binary_indexed_tree(
    const int initial_array[], int n
) {
    tree.resize(n);
    for (int i = 0; i < n; ++i) {
        tree[i] = 0;
        increase(i, initial_array[i]);
    }
}

Binary_indexed_tree::Binary_indexed_tree(
    int initial_value, int n
) {
    tree.resize(n);
    for (int i = 0; i < n; ++i)
        tree[i] = (get_consecutive_right(i) + 1) * initial_value;
}

void Binary_indexed_tree::push_back(int new_element) {
    tree.push_back(new_element);
    int p = tree.size() - 1, delta = highest_consecutive_right(p);
    while (delta) {
        tree.back() += tree[p ^ delta];
        delta >>= 1;
    }
}

/* return the sum of l..r(inclusively) */
int Binary_indexed_tree::query(int l, int r) {
    return prefix_sum(r) - prefix_sum(l - 1);
}

/* increase the element at position p by delta */
void Binary_indexed_tree::increase(int p, const int delta) {
    for (; p < tree.size(); p |= p + 1)
        tree[p] += delta;
}

/* return the sum of 0..p */
int Binary_indexed_tree::prefix_sum(int p) {
    int sum = 0;
    for (; p >= 0; p = remove_consecutive_right(p) - 1)
        sum += tree[p];
    return sum;
}

