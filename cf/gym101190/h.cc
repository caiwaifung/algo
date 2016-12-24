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
    const int minv=-32768, maxv=32767;
    VPI cs;
    while(1) {
        char op1[9]; int v1;
        scanf("%*s%s%d", op1, &v1);
        char sep[9];
        if(scanf("%s", sep)==EOF) {
            if(op1[0]=='>') cs.pb(mp(v1, maxv)); else cs.pb(mp(minv, v1));
            break;
        }
        if(sep[0]=='&') {
            int v2;
            scanf("%*s%*s%d", &v2);
            if(v1<=v2) cs.pb(mp(v1, v2));
            if(scanf("%*s")==EOF) break;
        } else {
            if(op1[0]=='>') cs.pb(mp(v1, maxv)); else cs.pb(mp(minv, v1));
        }
    }
    if(cs.empty()) {
        printf("false\n");
        return;
    }
    sort(all(cs));
    VPI ds;
    for(const auto& c: cs) {
        if(ds.empty() || c.fi>ds.back().se+1) {
            ds.pb(c);
        } else {
            setmax(ds.back().se, c.se);
        }
    }
    if(ds[0]==mp(minv, maxv)) {
        printf("true\n");
        return;
    }
    repn(i, sz(ds)) {
        if(ds[i].fi==minv) {
            printf("x <= %d", ds[i].se);
        } else if(ds[i].se==maxv) {
            printf("x >= %d", ds[i].fi);
        } else {
            printf("x >= %d && x <= %d", ds[i].fi,ds[i].se);
        }
        if(i<sz(ds)-1) printf(" ||");
        printf("\n");
    }
}

int main() {
    freopen("hard.in", "r", stdin);
    freopen("hard.out", "w", stdout);
    solve();
    return 0;
}
