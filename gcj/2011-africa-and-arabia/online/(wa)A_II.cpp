#include <iostream>
using namespace std;

typedef long double real;

char num_str[100][20];
pair<real, int> num[100];
pair<pair<int, real>, int> list[100];
int round[100];
int n;

void go(int dep, real st, real en, int si, int ei) {
    if (dep > 40) {
        for (int i = si; i <= ei; i ++)
            round[num[i].second] = dep;
        return;
    }
    if (si > ei) return;
    real m1 = (st * 2.0 + en) / 3.0;
    real m2 = (st + en * 2.0) / 3.0;
    int i = si;
    while (i <= ei && num[i].first < m1)
        i ++;
    go(dep+1, st, m1, si, i-1);
    while (i <= ei && num[i].first <= m2)
        round[num[i ++].second] = dep;
    go(dep+1, m2, en, i, ei);
}

void solve(int cs) {
    scanf("%d", &n);
    for (int i = 0; i < n; i ++) {
        scanf("%s", num_str[i]);
        real a = 0;
        real b = 1;
        for (int k = 2; k < strlen(num_str[i]); k ++) {
            a = a*10.0 + (real)(int)(num_str[i][k]-'0');
            b *= 10.0;
        }
        num[i].first = a/b;
        num[i].second = i;
    }
    for (int i = 0; i < n; i ++)
        list[i] = make_pair(make_pair(0xFF, num[i].first), i);
    sort(num, num+n);
    go(1, 0.0, 1.0, 0, n-1);
    for (int i = 0; i < n; i ++)
        list[i].first.first = round[i];
    sort(list, list+n);
    printf("Case #%d:\n", cs);
    for (int i = 0; i < n; i ++)
        printf("%s\n", num_str[list[i].second]);
}

int main() {
    freopen("A-large-practice.in", "r", stdin);
    freopen("A-large-practice.out", "w", stdout);
    int cs;
    scanf("%d", &cs);
    for (int i = 1; i <= cs; i ++)
        solve(i);
    return 0;
}
