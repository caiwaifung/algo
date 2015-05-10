#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

int candys[1010];
int candyCount;

void init() {
    scanf("%d", &candyCount);
    for (int i = 1; i <= candyCount; i ++)
        scanf("%d", &candys[i]);
}

void solve(int case_id) {
    int sum = 0;
    int minVal = 2147483647;
    int xorSum = 0;
    for (int i = 1; i <= candyCount; i ++) {
        xorSum ^= candys[i];
        sum += candys[i];
        minVal = min(candys[i], minVal);
    }
    if (xorSum == 0)
        printf("Case #%d: %d\n", case_id, sum-minVal);
    else
        printf("Case #%d: NO\n", case_id);
}

int main() {
    freopen("C-large.in", "r", stdin);
    freopen("C-large.out", "w", stdout);
    int cs;
    scanf("%d", &cs);
    for (int case_id = 1; case_id <= cs; case_id ++) {
        init();
        solve(case_id);
    }
    return 0;
}
