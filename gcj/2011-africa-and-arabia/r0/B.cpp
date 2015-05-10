#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
using namespace std;

int price[13];
int totalMoney;

void init() {
    scanf("%d", &totalMoney);
    for (int i = 1; i <= 12; i ++)
        scanf("%d", &price[i]);
}

void solve(int case_id) {
    int maxProfit = 0, minPrice = 0, monthBuy = -1, monthSell = -1;
    for (int i = 1; i <= 12; i ++)
        for (int j = i+1; j <= 12; j ++) {
            int amount = totalMoney / price[i];
            int pain = amount * price[i];
            int gain = amount * price[j];
            int profit = gain - pain;
            if (profit > maxProfit || (profit == maxProfit && price[i] < minPrice)) {
                maxProfit = profit;
                minPrice = price[i];
                monthBuy = i;
                monthSell = j;
            }
        }
    if (maxProfit == 0)
        printf("Case #%d: IMPOSSIBLE\n", case_id);
    else
        printf("Case #%d: %d %d %d\n", case_id, monthBuy, monthSell, maxProfit);
}

int main() {
    freopen("B-large-practice.in", "r", stdin);
    freopen("B-large-practice.out", "w", stdout);
    int cs;
    scanf("%d", &cs);
    for (int case_id = 1; case_id <= cs; case_id ++) {
        init();
        solve(case_id);
    }
    return 0;
}
