#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int find_max_sub_rectangle(int **matrix, int n);

int main() {
    int n;
    scanf("%d", &n);
    printf("n = %d\n", n);
    int **matrix = malloc(sizeof(int**)*n);
    for (int i = 0; i < n; ++i) {
        matrix[i] =  malloc(sizeof(int*)*n);
    }
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < n; ++y) {
            scanf("%d", &matrix[x][y]);
        }
    }
    int ans = find_max_sub_rectangle(matrix, n);
    printf("%d\n", ans);
    return 0;
}

int find_max_sub_rectangle(int **matrix, int n) {
    int max = INT_MIN;
    int ***table = malloc(sizeof(int**) * n);

    for (int i = 0; i < n; ++i) {
        table[i] = malloc(sizeof(int*) * n);
    }

    n--;
    for (int c = 0; c <= n; ++c) {
        for (int r = 0; r <= n; ++r) {
            // Free old values here
            table[n-c][n-r] = malloc(sizeof(int) * (c + 1) * (r + 1));
            int h;
            for (h = 0; h < (n - (n - (r + 1))); ++h) {
                if (h == 0) {
                    table[n-c][n-r][h] = matrix[n-c][n-r];
                    if (table[n-c][n-r][h] > max) {
                        max = table[n-c][n-r][h];
                    }
                } else {
                    table[n-c][n-r][h] = matrix[n-c][n-r] +
                        table[n-c][n-r+1][h-1];
                    if (table[n-c][n-r][h] > max) {
                        max = table[n-c][n-r][h];
                    }
                }
            }

            if (c > 0) {
                int row = 0;
                for (; h < (c+1)*(r+1); ++h) {
                    if ((h%(r+1)) == 0) {
                        row++;
                    }
                    table[n-c][n-r][h] = table[n-c][n-r][h- row*(r+1)] +
                        table[n-c+1][n-r][h-(r+1)];
                    if (table[n-c][n-r][h] > max) {
                        max = table[n-c][n-r][h];
                    }
                }
            }
        }
    }
    n++;

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

    return max;
}
