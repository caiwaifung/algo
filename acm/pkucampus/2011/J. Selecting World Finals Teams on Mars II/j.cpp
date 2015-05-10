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

struct Team {
    int a, b, c;
    friend bool operator <(const Team &a, const Team &b) {
        return a.a < b.a;
    }
} teams[100010];
int team_count;

void init() {
    scanf("%d", &team_count);
    for (int i = 1; i <= team_count; i ++)
        scanf("%d%d%d", &teams[i].a, &teams[i].b, &teams[i].c);
}

bool ta[110][110];

void ta_insert(int x, int y) {
    for (int i = x; i <= 100; i += (i&-i))
        for (int j = y; j <= 100; j += (j&-j))
            ta[i][j] = true;
}

bool ta_find(int x, int y) {
    for (int i = x; i >= 1; i -= (i&-i))
        for (int j = y; j >= 1; j -= (j&-j))
            if (ta[i][j])
                return true;
    return false;
}

void solve() {
    int ans = team_count;
    sort(teams + 1, teams + team_count + 1);
    for (int i = 1, j; i <= team_count; i = j + 1) {
        for (j = i; j < team_count && teams[j+1].a == teams[j].a; j ++);
        for (int k = i; k <= j; k ++)
            if (ta_find(teams[k].b - 1, teams[k].c - 1))
                ans --;
        for (int k = i; k <= j; k ++)
            ta_insert(teams[k].b, teams[k].c);
    }
    printf("%d\n", ans);
}

int main() {
    //freopen("j.in", "r", stdin);
    //freopen("j.out", "w", stdout);
    init();
    solve();
    return 0;
}
