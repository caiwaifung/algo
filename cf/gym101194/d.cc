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

void solve() {
    int n, k; scanf("%d%d", &n,&k);
    VL a(n);
    repn(i, n) scanf("%lld", &a[i]);
    sort(all(a));

    VI next(n);
    {
        int j=0;
        repn(i, n) {
            while(j<n && a[i]*2>a[j]) ++j;
            next[i]=j;
        }
    }
    const auto check=[&](int num) {
        VI cur;
        repn(i, num) cur.pb(i);
        replr(iter, 1, k) {
            int j=cur.back()+1;
            VI tmp;
            for(int i: cur) {
                setmax(j, next[i]);
                if(j>=n) return false;
                tmp.pb(j);
                ++j;
            }
            cur=tmp;
        }
        return true;
    };

    int l=0, r=n/k;
    while(l<r) {
        int m=(l+r+1)/2;
        if(check(m)) {
            l=m;
        } else {
            r=m-1;
        }
    }
    printf("%d\n", l);
}

int main() {
    int cs; scanf("%d", &cs);
    rep(i, 1, cs) {
        printf("Case #%d: ", i);
        solve();
    }
    return 0;
}
