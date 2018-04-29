#include "../base/header.h"

template <class T> T det(vector<vector<T>> a, T mod) {
    const int n = len(a);
    repn(i, n) assert(len(a[i]) == n);
    LL ans = 1;
    repn(i, n) replr(j, i + 1, n) {
        while (a[j][i] != 0) {
            int tmp = a[i][i] / a[j][i];
            replr(k, i, n) {
                a[i][k] = (a[i][k] - tmp * a[j][k]) % mod;
                swap(a[i][k], a[j][k]);
            }
            ans = -ans;
        }
    }
    repn(i, n) ans = ans * a[i][i] % mod;
    return (ans % mod + mod) % mod;
}
