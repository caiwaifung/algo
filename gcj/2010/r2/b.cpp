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

int dp[12][1100][12];
int cost[12][1100];
int limit[1100];
int n;

void init() {
    scanf("%d", &n);
    for (int i = 1; i <= (1<<n); i ++)
        scanf("%d", &limit[i]);
    for (int i = 1; i <= n; i ++)
        for (int j = 1; j <= (1<<(n-i)); j ++)
            scanf("%d", &cost[i][j]);
}

void solve(int case_id) {
    memset(dp, 50, sizeof(dp));
    for (int i = 1; i <= (1<<n); i ++)
        for (int j = 0; j <= limit[i]; j ++)
            dp[0][i][j] = 0;
    for (int k = 1; k <= n; k ++)
        for (int i = 1; i <= (1<<(n-k)); i ++) {
            int lc = i*2-1, rc = i*2;
            for (int j = 0; j <= n; j ++) {
                dp[k][i][j] = min(dp[k][i][j], dp[k-1][lc][j+1] + dp[k-1][rc][j+1]);
                dp[k][i][j] = min(dp[k][i][j], dp[k-1][lc][j] + dp[k-1][rc][j] + cost[k][i]);
            }
        }
    printf("Case #%d: %d\n", case_id, dp[n][1][0]);
}

int main() {
    freopen("B-large-practice.in", "r", stdin);
    freopen("B-large-practice.out", "w", stdout);
    int case_count;
    scanf("%d", &case_count);
    for (int case_id = 1; case_id <= case_count; case_id ++) {
        init();
        solve(case_id);
    }
    return 0;
}
