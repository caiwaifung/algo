#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>
using namespace std;

int dist[550][550];
int city_count;

void init() {
    int road_count;
    memset(dist, 50, sizeof(dist));
    scanf("%d%d", &city_count, &road_count);
    for (int i = 0; i <= city_count; i ++)
        dist[i][i] = 0;
    while (road_count --) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        dist[x][y] = min(dist[x][y], z);
        dist[y][x] = min(dist[y][x], z);
    }
    for (int k = 0; k <= city_count; k ++)
        for (int i = 0; i <= city_count; i ++)
            for (int j = 0; j <= city_count; j ++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    //for (int i = 0; i <= city_count; i ++)
    //    for (int j = 0; j <= city_count; j ++)
    //        printf("dist[%d][%d] = %d\n", i, j, dist[i][j]);
}

int dp[2][550][550];

void solve() {
    int o1 = 0, o2 = o1^1;
    memset(dp, 50, sizeof(dp));
    int max_val = dp[0][0][0];
    dp[o1][0][0] = 0;
    for (int k = 0; k < city_count; k ++, o1 = o2, o2 ^= 1) {
        memset(dp[o2], 50, sizeof(dp[o2]));
        for (int i = 0; i <= k; i ++)
            for (int j = i; j <= k; j ++) {
                int cur_v = dp[o1][i][j]; //if (cur_v == max_val) continue;
                //printf("dp[%d][%d][%d] = %d\n", k, i, j, cur_v);
                dp[o2][i][j] = min(dp[o2][i][j], cur_v + dist[k][k+1]);
                dp[o2][i][k] = min(dp[o2][i][k], cur_v + dist[j][k+1]);
                dp[o2][j][k] = min(dp[o2][j][k], cur_v + dist[i][k+1]);
            }
    }
    int ans = 1<<30;
    for (int i = 0; i <= city_count; i ++)
        for (int j = i; j <= city_count; j ++)
            ans = min(ans, dp[o1][i][j] + dist[0][i] + dist[0][j] + dist[0][city_count]);
    printf("%d\n", ans);
}

int main() {
    //freopen("d.in", "r", stdin);
    //freopen("d.out", "w", stdout);
    init();
    solve();
    return 0;
}
