#include <stdio.h>
#include <stdlib.h>

int tri_tiling(int n);

int main() {
    char *line = NULL;
    size_t linecap = 0;
    long linelen;
    while ((linelen = getline(&line, &linecap, stdin)) > 0) {
        int n = atoi(line);
        if (n == -1) {
            break;
        }
        int ans = tri_tiling(n);
        fprintf(stdout, "%d\n", ans);
    }

}

int tri_tiling(int n) {
    int T[n][2];

    // Base cases
    T[0][0] = 0;
    T[0][1] = 1;
    T[1][0] = 3;
    T[1][1] = 0;

    for (int i = 2; i < n; ++i) {
        T[i][0] = 2*T[i-1][1] + T[i-2][0];
        T[i][1] = T[i-1][0] + T[i-2][1];
    }
    int ans =  T[n-1][0] > T[n-1][1] ? T[n-1][0] : T[n-1][1];
    return ans;
}
