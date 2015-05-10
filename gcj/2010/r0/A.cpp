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

int n, k;

void init() {
    scanf("%d%d", &n, &k);
}

void solve(int case_id) {
    int p = 1 << n;
    k = k % p;
    printf("Case #%d: %s\n", case_id, k == p-1 ? "ON" : "OFF");
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
