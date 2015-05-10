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

typedef long long int64;
const int64 MODULE = 1000000007;

struct Matrix {
    int64 a[6][6];
    Matrix() {
        memset(a, 0, sizeof(a));
    }
    friend Matrix operator *(const Matrix &a, const Matrix &b) {
        Matrix c;
        for (int i = 0; i < 6; i ++)
            for (int j = 0; j < 6; j ++)
                for (int k = 0; k < 6; k ++)
                    c.a[i][j] = (c.a[i][j] + a.a[i][k]*b.a[k][j]) % MODULE;
        return c;
    }
    friend Matrix power(Matrix a, int n) {
        Matrix c;
        for (int i = 0; i < 6; i ++)
            c.a[i][i] = 1;
        for (; n > 0; n /= 2, a = a*a)
            if (n%2 == 1)
                c = c*a;
        return c;
    }
};

void solve(int case_id) {
    Matrix t;
    int n;
    cin >> n;
    if (n == 1) {
        cout << "Case " << case_id << ": 1" << endl;
        return;
    }
    t.a[0][0] = t.a[0][4] = t.a[0][5] = 1;
    t.a[1][1] = t.a[1][2] = t.a[1][3] = 1;
    t.a[2][0] = t.a[2][3] = t.a[2][4] = t.a[2][5] = 1;
    t.a[3][0] = t.a[3][2] = t.a[3][4] = t.a[3][5] = 1;
    t.a[4][1] = t.a[4][2] = t.a[4][3] = t.a[4][5] = 1;
    t.a[5][1] = t.a[5][2] = t.a[5][3] = t.a[5][4] = 1;
    t = power(t, n - 2);
    /*
    for (int i = 0; i < 6; i ++) {
        for (int j = 0; j < 6; j ++)
            cout << t.a[i][j] << " ";
        cout << endl;
    }*/
    int64 ans = 0;
    for (int i = 0; i < 6; i ++)
        for (int j = 0; j < 6; j ++)
            ans = (ans + t.a[i][j]) % MODULE;
    cout << "Case " << case_id << ": " << ans << endl;
}

int main() {
    freopen("f.in", "r", stdin);
    freopen("f.out", "w", stdout);
    int cs;
    scanf("%d", &cs);
    for (int case_id = 1; case_id <= cs; case_id ++)
        solve(case_id);
    return 0;
}
