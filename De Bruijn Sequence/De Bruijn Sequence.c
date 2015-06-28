#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int alphabet_size, sub_length, num_vertice;
/* state[i] == x means vertex i's edges numbered less than x were visited */
int *state;
char alphabet[10000];

/* potential bug : overflow */
int power(int base, int exponent) {
    int result = 1;
    while(exponent) {
        if (exponent & 1)
            result *= base;
        exponent >>= 1;
        base *= base;
    }
    return result;
}

void DFS(const int x) {
    if (state[x] < alphabet_size) {
        putchar(alphabet[state[x]]);
        DFS(x * alphabet_size % num_vertice + state[x]++);
    }
}

int main() {
    puts("Input the alphabet: ");
    scanf("%s", alphabet);
    puts("Input subsequence length: ");
    scanf("%d", &sub_length);

    /* special case : string on vertex would be empty*/
    if (sub_length == 1) {
        puts(alphabet);
        return 0;
    }
    alphabet_size = strlen(alphabet);
    num_vertice = power(alphabet_size, sub_length - 1);
    state = (int *)malloc(num_vertice * sizeof(*state)); 
    memset(state, 0, num_vertice * sizeof(*state));

    DFS(num_vertice - 1);
    putchar('\n');

    free(state);
    return 0;
}

