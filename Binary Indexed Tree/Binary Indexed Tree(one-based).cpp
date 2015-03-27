/*
 * For consistentcy,
 * only the indice of elements in the tree are one-based,
 * and the parameter of the methods are still zero-based.
 */
/* The ith element of the tree is the sum of ((i&(i-1)) + 1)..i */
#include <vector>
#include <cstdio>
#include "Binary Indexed Tree.h"

inline int low_bit(int x) {
    return x & -x;
}

Binary_indexed_tree::Binary_indexed_tree() {
    tree.push_back(0);
}

Binary_indexed_tree::Binary_indexed_tree(
    const std::vector<int>& initial_vector
) {
    tree.resize(initial_vector.size() + 1);
    tree[0] = 0;
    for (int i = 0; i < initial_vector.size(); ++i) {
        tree[i + 1] = 0;
        increase(i, initial_vector[i]);
    }
}

Binary_indexed_tree::Binary_indexed_tree(
    const int initial_array[], int n
) {
    tree.resize(n + 1);
    tree[0] = 0;
    for (int i = 0; i < n; ++i) {
        tree[i + 1] = 0;
        increase(i, initial_array[i]);
    }
}

Binary_indexed_tree::Binary_indexed_tree(
    int initial_value, int n
) {
    tree.resize(n + 1);
    tree[0] = 0;
    for (int i = 1; i <= n; ++i)
        tree[i] = low_bit(i) * initial_value;
}

void Binary_indexed_tree::push_back(int new_element) {
    tree.push_back(new_element);
    int p = tree.size() - 1, delta = low_bit(p);
    while (delta > 1) {
        delta >>= 1;
        tree.back() += tree[p - delta];
    }
}

/* return the sum of l..r(inclusively) */
int Binary_indexed_tree::query(int l, int r) {
    return prefix_sum(r) - prefix_sum(l - 1);
}

/* increase the element at position p by delta */
void Binary_indexed_tree::increase(int p, const int delta) {
    for (p += 1; p < tree.size(); p += low_bit(p))
        tree[p] += delta;
}

/* return the sum of 0..p */
int Binary_indexed_tree::prefix_sum(int p) {
    int sum = 0;
    for (p += 1; p; p &= p - 1)
        sum += tree[p];
    return sum;
}

