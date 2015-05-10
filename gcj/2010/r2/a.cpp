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

int diamond[110][110], st[110], en[110];
int n;

void init() {
    memset(diamond, 0, sizeof(diamond));
    scanf("%d", &n);
    for (int i = 1; i <= 2*n-1; i ++) {
        st[i] = 1 + abs(i-n), en[i] = 2*n - st[i];
        for (int j = st[i]; j <= en[i]; j += 2)
            scanf("%d", &diamond[i][j]);
    }
}

bool sym_x[110], sym_y[110];

bool valid(int i, int j) {
    return (i >= 1 && i <= 2*n-1 && j >= st[i] && j <= en[i]);
}

void solve(int case_id) {
    for (int x = 1; x <= 2*n-1; x ++) {
        sym_x[x] = true;
        for (int i = 1; i <= 2*n-1; i ++)
            for (int j = 1; j <= 2*n-1; j ++) {
                int i2 = 2*x - i, j2 = j;
                if (valid(i, j) && valid(i2, j2) && diamond[i][j] != diamond[i2][j2])
                    sym_x[x] = false;
            }
    }
    for (int y = 1; y <= 2*n-1; y ++) {
        sym_y[y] = true;
        for (int i = 1; i <= 2*n-1; i ++)
            for (int j = 1; j <= 2*n-1; j ++) {
                int i2 = i, j2 = 2*y - j;
                if (valid(i, j) && valid(i2, j2) && diamond[i][j] != diamond[i2][j2])
                    sym_y[y] = false;
            }
    }
    int min_delta = 1000;
    for (int i = 1; i <= 2*n-1; i ++)
        for (int j = 1; j <= 2*n-1; j ++)
            if (sym_x[i] && sym_y[j])// {
               // printf("%d %d %d\n", i, j,abs(i-n) + abs(j-n));
                min_delta = min(min_delta, abs(i-n) + abs(j-n));
            //}
    //printf("%d - %d\n", (n + min_delta), n);
    int ans = (n + min_delta) * (n + min_delta) - n * n;
    printf("Case #%d: %d\n", case_id, ans);
}

int main() {
    freopen("A-large-practice.in", "r", stdin);
    freopen("A-large-practice.out", "w", stdout);
    //freopen("A.in", "r", stdin);
    //freopen("A.out", "w", stdout);
    int case_count;
    scanf("%d", &case_count);
    for (int case_id = 1; case_id <= case_count; case_id ++) {
        init();
        solve(case_id);
    }
    return 0;
}
