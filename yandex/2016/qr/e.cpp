#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define sz(a) static_cast<int>(a.size())
#define all(a) a.begin(), a.end()
#define rep(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define irep(i, a, b) for(int i=int(a); i>=int(b); --i)
#define repn(i, n) rep(i, 0, (n)-1)
#define irepn(i, n) irep(i, (n)-1, 0)
#define fillchar(a, x) memset(a, x, sizeof(a))
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
typedef vector<PLL> VPL;
typedef vector<string> VS;
template<class T> bool setmax(T &_a, T _b) { if(_b>_a) { _a=_b; return true; } return false; }
template<class T> bool setmin(T &_a, T _b) { if(_b<_a) { _a=_b; return true; } return false; }
template<class T> T gcd(T _a, T _b) { return _b==0?_a:gcd(_b,_a%_b); }

const int N=4040;

VPL merge(VPL a) {
    VPL b;
    sort(all(a));
    for(const auto& x: a) {
        if(b.empty() || x.fi>b.back().fi) {
            b.pb(x);
        } else {
            b.back().se+=x.se;
        }
    }
    return b;
}

VPL init() {
    int num; scanf("%d", &num);
    VPL a; rep(i, 1, num) {
        int x; scanf("%d", &x);
        a.pb(mp(x, 1));
    }
    return merge(a);
}

void solve(VPL a) {
    LL ans=0;
    for(const auto& x: a) if(x.se>=4) {
        ans+=x.se*(x.se-1)*(x.se-2)*(x.se-3)/1/2/3/4;
    }
    repn(i, sz(a)) rep(j, i+1, sz(a)-1) {
        LL u=a[i].se*(a[i].se-1)/2;
        LL v=a[j].se*(a[j].se-1)/2;
        ans+=u*v;
    }

    struct Pair {
        LL prod, x;
        bool eq;
        LL factor;
        bool operator<(const Pair& other) const {
            if(prod!=other.prod) return prod<other.prod;
            if(x!=other.x) return x<other.x;
            return false;
        }
    };
    vector<Pair> ps;
    repn(i, sz(a)) if(a[i].se>=2) {
        ps.pb(Pair{a[i].fi*a[i].fi, a[i].fi, true, a[i].se*(a[i].se-1)/2});
    }
    repn(i, sz(a)) rep(j, i+1, sz(a)-1) {
        ps.pb(Pair{a[i].fi*a[j].fi, a[i].fi, false, a[i].se*a[j].se});
    }
    sort(all(ps));
    for(int i=0, j; i<sz(ps); i=j) {
        for(j=i; j<sz(ps) && ps[j].prod==ps[i].prod; ++j);
        int x=i; LL s=0;
        rep(y, i, j-1) {
            while(ps[x].x<ps[y].x) {
                if(!ps[x].eq) s+=ps[x].factor;
                ++x;
            }
            ans+=ps[y].factor*s;
        }
    }

    cout<<ans<<endl;
}

int main() {
    VPL a=init();
    solve(a);
    return 0;
}
