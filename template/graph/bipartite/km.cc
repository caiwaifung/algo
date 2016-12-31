struct KM {
    int a[N][N], n;
    int mincost_match() {
        VI x(n, -1000), y(n), matched(n, -1);
        repn(cur, n) {
            VI slack(n, 1 << 30), pre(n, -1);
            vector<bool> vis(n, false);
            int j0 = -1;
            while(1) {
                const int i0 = (j0 < 0 ? cur : matched[j0]);
                if(i0 < 0) break;
                int minv = 1 << 30, minj = -1;
                repn(j, n) if(!vis[j]) {
                    if(setmin(slack[j], a[i0][j] - x[i0] - y[j])) {
                        pre[j] = j0;
                    }
                    if(setmin(minv, slack[j])) {
                        minj = j;
                    }
                }
                x[cur] += minv;
                repn(j, n) if(vis[j]) {
                    x[matched[j]] += minv;
                    y[j] -= minv;
                }
                else {
                    slack[j] -= minv;
                }
                j0 = minj, vis[j0] = true;
            }
            while(j0 >= 0) {
                const int j = pre[j0];
                matched[j0] = (j < 0 ? cur : matched[j]), j0 = j;
            }
        }
        return accumulate(all(x), 0) + accumulate(all(y), 0);
    }
};
