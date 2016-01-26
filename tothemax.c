#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int find_max_sub_rectangle(int **matrix, int n);

int main() {
    int n;
    scanf("%d", &n);
    int **matrix = malloc(sizeof(int**)*n);
    for (int i = 0; i < n; ++i) {
        matrix[i] =  malloc(sizeof(int*)*n);
    }
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < n; ++y) {
            scanf("%d", &matrix[x][y]);
        }
    }
    int ans = find_max_sub_rectangle((int**)matrix, n);
    printf("%d\n", ans);
    return 0;
}

int find_max_sub_rectangle(int **matrix, int n) {
    int ***table = malloc(sizeof(int**)*n);
    for (int i = 0; i < n; ++i) {
        table[i] =  malloc(sizeof(int*)*n);
    }
    int max = INT_MIN;
    for (int c = 0; c < n; ++c) {
        for (int r = 0; r < n; ++r) {
            table[c][r] = malloc(sizeof(int)*(c+1)*(r+1));
            table[c][r][0] = matrix[c][r];
            if (table[c][r][0] > max) {
                max = table[c][r][0];
            }
            int h;
            for (h = 1; h <= r; ++h) {
                table[c][r][h] = table[c][r][h-1] + matrix[c][r-h];
                printf("%d %d %d = %d + %d\n", c, r, h, table[c][r][h-1], matrix[c][r-h]);

                if (table[c][r][h] > max) {
                    max = table[c][r][h];
                }
            }
            if (r > 0) {
                // The indexing below here is goofed up
                for (; h < (c+r); ++h) {
                    table[c][r][h] = table[c][r-1][h] + table[c][r][h-1];
                    printf("%d %d %d = c\n", c, r, h);
                    //printf("%d %d %d = %d + %d\n", c, r, h, table[c][r-1][h], matrix[c][r-h]);
                    if (table[c][r][h] > max) {
                        max = table[c][r][h];
                    }
                }
                for (; h < (c+1)*(1+r); ++h) {
                    table[c][r][h] = table[c][r][(c+1)*r] + table[c][r][r-h];
                    printf("%d %d %d = c\n", c, r, h);
                    //printf("%d %d %d = %d + %d\n", c, r, h, table[c][r-1][h], matrix[c][r-h]);
                    if (table[c][r][h] > max) {
                        max = table[c][r][h];
                    }
                }
            } else {
                printf("%d %d %d = ?\n", c, r, h);
            }
        }
    }
    // Printing
    for (int c = 0; c < n; ++c) {
        for (int r = 0; r < n; ++r) {
            int *arr = table[c][r];
            printf("(%d, %d): ", c, r);
            for (int h = 0; h < (c+1)*(r+1); ++h) {
                printf("%d, ", arr[h]);
            }
            printf("\n");
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
