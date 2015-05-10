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

int segLength[1000];
int segColor[1000];
int nSeg;

void init() {
    scanf("%d", &nSeg);
    for (int i = 0; i < nSeg; i ++) {
        char ch;
        scanf("%d%c", &segLength[i], &ch);
        segColor[i] = (ch == 'R' ? 1 : 2);
    }
}

void solve(int case_id) {
    vector<int> a, b;
    for (int i = 0; i < nSeg; i ++)
        if (segColor[i] == 1)
            a.push_back(segLength[i]);
        else
            b.push_back(segLength[i]);
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    int ans = 0;
    int i = a.size()-1, j = b.size()-1;
    while (i >= 0 && j >= 0)
        ans += a[i--] + b[j--] - 2;
    printf("Case #%d: %d\n", case_id, ans);
}

int main() {
    freopen("A-large-practice.in", "r", stdin);
    freopen("A-large-practice.out", "w", stdout);
    int cs;
    scanf("%d", &cs);
    for (int case_id = 1; case_id <= cs; case_id ++) {
        init();
        solve(case_id);
    }
    return 0;
}
