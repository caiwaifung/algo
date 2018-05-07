#include "../base/header.h"

// Returns (min_cost, match).
template <class T> pair<T, VI> mincost_match(const vector<vector<T>>& a) {
    const int n = len(a);
    vector<T> x(n, numeric_limits<T>::min() / 2), y(n);
    VI matched(n, -1);
    repn(cur, n) {
        vector<T> slack(n, numeric_limits<T>::max());
        VI pre(n, -1);
        vector<bool> vis(n, false);
        int j0 = -1;
        while (1) {
            const int i0 = (j0 < 0 ? cur : matched[j0]);
            if (i0 < 0) break;
            T minv = numeric_limits<T>::max();
            int minj = -1;
            repn(j, n) if (!vis[j]) {
                if (setmin(slack[j], a[i0][j] - x[i0] - y[j])) {
                    pre[j] = j0;
                }
                if (setmin(minv, slack[j])) {
                    minj = j;
                }
            }
            x[cur] += minv;
            repn(j, n) if (vis[j]) {
                x[matched[j]] += minv;
                y[j] -= minv;
            }
            else {
                slack[j] -= minv;
            }
            j0 = minj, vis[j0] = true;
        }
        while (j0 >= 0) {
            const int j = pre[j0];
            matched[j0] = (j < 0 ? cur : matched[j]), j0 = j;
        }
    }
    VI r(n);
    repn(i, n) r[matched[i]] = i;
    return mp(accumulate(all(x), (T)0) + accumulate(all(y), (T)0), r);
}
