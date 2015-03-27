#include <vector>

class Binary_indexed_tree {
private:
    std::vector<int> tree;
public:
    Binary_indexed_tree();
    Binary_indexed_tree(const std::vector<int>& initial_vector);
    Binary_indexed_tree(const int initial_array[], int n);
    Binary_indexed_tree(int initial_value, int n);
    void push_back(int new_element);
    int query(int l, int r);
    void increase(int p, const int delta);
private:
    int prefix_sum(int p);
};

