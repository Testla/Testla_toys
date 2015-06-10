#include <stdio.h>
#include <stdlib.h> 

#define ver1
/*The version of implementation, ver1 is the classical one,
 *and ver2 is the one on page 143 of the ppt
 *which maybe faster when the number of "1"s is medium*/

int main() {
    int n, i, j, k, **Matrix, **Closure;
    printf("Please enter an integer, the size of the matrix: ");
    scanf("%d", &n);
    Matrix = (int **)malloc(n * sizeof(int *));
    Closure = (int **)malloc(n * sizeof(int *));
    for (i = 0; i < n; i++) {
        Matrix[i] = (int *)malloc(n * sizeof(int));
        Closure[i] = (int *)malloc(n * sizeof(int));
    }
    puts("Please enter the matrix (not necessary to use spaces to separate):");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            scanf("%1d", &Matrix[i][j]);
            Closure[i][j] = Matrix[i][j];
        }
    
    /*Warshall's algorithm*/
    #ifdef ver1
    
    for (k = 0; k < n; k++)
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                Closure[i][j] |= Closure[i][k] & Closure[k][j];
    
    #else
    #ifdef ver2
    
    /*This version remembers the position of "1"s on the kth row and column*/
    int *row, *col, nrow, ncol;
    row = (int *)malloc(n * sizeof(int));
    col = (int *)malloc(n * sizeof(int));
    for (k = 0; k < n; k++) {
        nrow = 0;
        ncol = 0;
        for (i = 0; i < n; i++) {
            if (Closure[i][k] == 1) {
                col[ncol] = i;
                ncol++;
            }
            if (Closure[k][i] == 1 && i != k/*aovid unnecessary operation*/) {
                row[nrow] = i;
                nrow++;
            }
        }
        for (i = 0; i < ncol; i++)
            for (j = 0; j < nrow; j++)
                Closure[col[i]][row[j]] = 1;
    }
    free(row);
    free(col);
    
    #else
    
    puts("Error implementation version, please correct the macro.");
    return 1;
    
    #endif
    #endif
    
    puts("\nThe transitive closure of the matrix is");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            printf("%d%c", Closure[i][j], (j == n - 1) ? '\n' : ' ');
    
    for (i = 0; i < n; i++) {
        free(Matrix[i]);
        free(Closure[i]);
    }
    free(Matrix);
    free(Closure);
    system("pause");
    return 0;
}

