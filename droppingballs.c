#include <stdio.h>
#include <stdlib.h>

int drop_balls(int node, int balls, int max);

int main() {
    int num_lines;
    scanf("%d", &num_lines);
    for (int i = 0; i < num_lines; i++) {
        int I, D;
        scanf("%d %d", &I, &D);
        // max = 2 raised to the D
        int max = 1 << D;
        printf("max, I, D %d %d %d\n", max, I, D);
        printf("%d\n", drop_balls(1, I, max));
    }

    return 0;
}

/*
int drop_balls(int node, int balls, int max) {
    int i;
    for (i = 0; i < max && node*2 < max && node *2+1 < max; i++) {
        if ((balls & 1) == 0) {
            node = node * 2 + 1;
            balls /= 2;
        } else {
            node *= 2;
            balls = balls/2 + 1;
        }
    }
    return node;
}
*/

// Recursive solution
int drop_balls(int node, int balls, int max) {
    int left = node * 2;
    int right = node * 2 + 1;
    if (left < max && right < max) {
        if ((balls & 1) == 0) { // Even
            return drop_balls(right, balls/2, max);
        } else { // Odd
            return drop_balls(left, balls/2 + 1, max);
        }
    }
    return node;
}
