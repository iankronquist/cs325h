#include <stdio.h>
#include <stdlib.h>

int find_max_sub_rectangle(int **matrix, int n);

int main() {
    int n;
    scanf("%*[ \n\t]%d", &n);
    int **matrix = malloc(sizeof(int**)**sizeof(int**)n*n);
    for (int x = 0; x < n*n; ++x) {
        for (int y = 0; y < n*n; ++y) {
            scanf("%*[ \n\t]%d", &matrix[x][y]);
        }
    }
    int ans = find_max_sub_rectangle(matrix, n);
    printf("%d\n", ans);
    return 0;
}

int find_max_sub_rectangle(int **matrix, int n) {
    int **table = malloc(sizeof(int**)**sizeof(int**)n*n);
    int max = INT_MIN;
    for (int c = 0; c < n; ++c) {
        for (int r = 0; r < n; ++r) {
            table[c][r] = malloc(sizeof(int)*(c+1)*(r+1));
            table[c][r][0] = matrix[c][r];
            if (table[c][r][0] > max) {
                max = table[c][r][0];
            }
            for (int h = 1; h < r; ++h) {
                table[c][r][h] = table[c][r][h-1] + matrix[c][r];

                if (table[c][r][h] > max) {
                    max = table[c][r][h];
                }
            }
            if (r > 0) {
                for (h < (c+1)(r+1); ++h) {
                    table[c][r][h] = table[c][r-1][h] + table[c][r][h];
                    if (table[c][r][h] > max) {
                        max = table[c][r][h];
                    }
                }
            }
        }
    }
    // Let the OS collect our garbage
    /*
    for (int i = 0; i < n*n; ++i) {
        free(table[i]);
    }
    free(table);
    */
    return max;
}
