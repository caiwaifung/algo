#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <memory>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

#define all(a) (a).begin(), (a).end()
#define sz(a) static_cast<int>((a).size())
#define fillchar(a, x) memset(a, x, sizeof(a))
#define rep(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define irep(i, a, b) for(int i=int(a); i>=int(b); --i)
#define replr(i, a, b) rep(i, a, (b)-1)
#define reprl(i, a, b) irep(i, (b)-1, a)
#define repn(i, n) rep(i, 0, (n)-1)
#define irepn(i, n) irep(i, (n)-1, 0)
#define fi first
#define se second
#define pb push_back
#define mp make_pair
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef pair<int,int> PII;
typedef pair<double,double> PDD;
typedef vector<LL> VL;
typedef vector<int> VI;
typedef vector<PII> VPI;
typedef vector<string> VS;
template<class T, class S> ostream& operator<<(ostream& os, const pair<T, S>& v) { return os<<"("<<v.first<<", "<<v.second<<")"; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& v) { os<<"["; repn(i, sz(v)) { if(i) os<<", "; os<<v[i]; } return os<<"]"; }
template<class T> bool setmax(T &_a, T _b) { if(_b>_a) { _a=_b; return true; } return false; }
template<class T> bool setmin(T &_a, T _b) { if(_b<_a) { _a=_b; return true; } return false; }
template<class T> T gcd(T _a, T _b) { return _b==0?_a:gcd(_b,_a%_b); }

VI solve() {
    int n; scanf("%d", &n);
    VPI xs(n);
    repn(i, n) { scanf("%d", &xs[i].fi); --xs[i].fi; xs[i].se=i; }
    sort(all(xs));

    VI r(n*n, -1);
    for(const auto& x: xs) {
        if(r[x.fi]>=0) return VI();
        r[x.fi]=x.se;
    }
    int i=0;
    for(const auto& x: xs) {
        int pos=x.fi, val=x.se, num=x.se;
        while(num--) {
            while(i<pos && r[i]>=0) ++i;
            if(i>=pos) return VI();
            r[i]=val;
        }
    }
    i=n*n-1;
    reverse(all(xs));
    for(const auto& x: xs) {
        int pos=x.fi, val=x.se, num=n-x.se-1;
        while(num--) {
            while(i>pos && r[i]>=0) --i;
            if(i<=pos) return VI();
            r[i]=val;
        }
    }
    return r;
}

int main() {
    VI r=solve();
    if(r.empty()) {
        printf("No\n");
    } else {
        printf("Yes\n");
        for(int x: r) printf("%d ", x+1);
        printf("\n");
    }
    return 0;
}
