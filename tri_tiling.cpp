#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

int tri_tiling(int n);

int main() {
    string num;
    while (1) {
        getline(cin, num);
        int n = atoi(num.c_str());
        if (n == -1) {
            break;
        }
        if (n & 1 || n == 0) {
            cout << 0 << endl;
            continue;
        }
        int ans = tri_tiling(n);
        cout << ans << endl;
    }
    return 0;
}

int tri_tiling(int n) {
    int **T = new int*[n];
    for (int i = 0; i < n; ++i) {
        T[i] = new int[2];
    }

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
    for (int i = 0; i < n; ++i) {
        delete [] T[i];
    }
    delete [] T;
    return ans;
}
