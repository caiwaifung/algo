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

const int maxbit = 1000;

class BigNumber {

private:
    vector<int> a;
    
public:
    BigNumber(int num = 0) {
        a.clear();
        while (num > 0) {
            a.push_back(num % maxbit);
            num /= maxbit;
        }
    }
    
    BigNumber(string s) {
        int tbit = maxbit, cbit = 0;
        while (tbit > 1) {
            cbit++;
            tbit /= 10;
        }
        
        int cur = 0, cnt = 0;
        a.clear();
        for (int i = s.size()-1; i >= 0; i --) {
            if (cnt == cbit) {
                a.push_back(cur);
                cur = 0;
                cnt = 0;
            }
            cur = cur*10 + (int)s[i] - (int)'0';
            cnt ++;
        }
        if (cnt > 0) 
            a.push_back(cur);
        while (a.size() > 0 && a.back() == 0)
            a.pop_back();
    }
    
    void div2() {
        for (int r = 0, i = a.size()-1; i >= 0; i --) {
            a[i] += r*maxbit;
            r = a[i] % 2;
            a[i] /= 2;
        }
        while (a.size() > 0 && a.back() == 0)
            a.pop_back();
    }
    
    void mul2() {
        int r = 0;
        for (int i = 0; i < a.size(); i ++) {
            a[i] = a[i]*2 + r;
            r = a[i] / maxbit;
            a[i] %= maxbit;
        }
        while (r > 0) {
            a.push_back(r % maxbit);
            r /= maxbit;
        }
    }
    
    void minus(const BigNumber &b) {
        for (int i = 0; i < a.size(); i ++) {
            if (i < b.a.size())
                a[i] -= b.a[i];
            if (a[i] < 0)
                a[i] += maxbit, a[i+1] --;
        }
    }
    
    friend int cmp(const BigNumber &a, const BigNumber &b) {
        if (a.a.size() != b.a.size())
            return a.a.size() < b.a.size() ? -1 : 1;
        for (int i = a.a.size()-1; i >= 0; i --)
            if (a.a[i] != b.a[i])
                return a.a[i] < b.a[i] ? -1 : 1;
        return 0;        
    }
    
    friend bool operator <(const BigNumber &a, const BigNumber &b) {
        return cmp(a, b) < 0;
    }
    
    friend BigNumber gcd(const BigNumber &pa, const BigNumber &pb) {
        BigNumber a = pa;
        BigNumber b = pb;
        int m2 = 0;
        while (a.a.size() > 0 && b.a.size() > 0) {
            if (a.a[0]%2 == 0 && b.a[0]%2 == 0) {
                m2 ++;
                a.div2();
                b.div2();
                continue;
            }
            if (a.a[0]%2 == 0) {
                a.div2();
                continue;
            }
            if (b.a[0]%2 == 0) {
                b.div2();
                continue;
            }
            if (a < b)
                b.minus(a);
            else
                a.minus(b);
        }
        BigNumber c;
        if (a.a.size() > 0)
            c = a;
        else
            c = b;
        while (m2 --)
            c.mul2();
        return c;
    }
} a[100];
int n;

void init() {
    scanf("%d", &n);
    for (int i = 0; i < n; i ++) {
        string s;
        cin >> s;
        a[i] = BigNumber(s);
    }
}

void solve(int case_id) {
    if (n == 1) {
        printf("Case #%d: 0\n", case_id);
        return;
    }
    sort(a, a + n);
    BigNumber c = a[1];
    c.minus(a[0]);
    for (int i = 2; i < n; i ++) {
        BigNumber tmp = a[i];
        tmp.minus(a[i-1]);
        c = gcd(c, tmp);
    }
    
}

int main() {
    freopen("FILENAME.in", "r", stdin);
    freopen("FILENAME.out", "w", stdout);
    int cs;
    scanf("%d", &cs);
    for (int case_id = 1; case_id <= cs; case_id ++) {
        init();
        solve(case_id);
    }
    return 0;
}
