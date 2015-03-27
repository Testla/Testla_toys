#include <cstdio>
#include "Binary indexed tree.h"

int main() {
    Binary_indexed_tree T;
    T.push_back(1);
    T.push_back(1);
    T.push_back(1);
    T.increase(1, 2);
    /* 1 3 1 */
    printf("%d\n", T.query(0, 2));  // 5
    T.increase(0, 3);
    T.increase(2, -2);
    /* 4 3 -1 */
    printf("%d\n", T.query(0, 2));  // 6
    printf("%d\n", T.query(0, 1));  // 7
    printf("%d\n", T.query(2, 2));  // -1
    T.push_back(8);
    /* 4 3 -1 8 */
    printf("%d\n", T.query(0, 3));  // 14
    printf("%d\n", T.query(1, 2));  // -2
    T.push_back(-100);
    T.push_back(200);
    T.increase(4, -99);
    /* 4 3 -1 8 -199 200 */
    printf("%d\n", T.query(0, 5));  // 15
    printf("%d\n", T.query(0, 0));  // 4
    return 0;
}

