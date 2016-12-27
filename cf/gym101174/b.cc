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

int solve_best(const VPI& a) {
    int base=0;
    vector<pair<PII, int>> es;
    replr(i, 1, sz(a)) {
        int x=a[i].fi-a[0].fi, y=a[i].se-a[0].se;
        if(x<=0 && y<=0) {
            ++base; continue;
        }
        if(x>0 && y>0) {
            continue;
        }
        if(x>0) {
            es.pb(mp(mp(-y, x), 1));
        } else {
            base++;
            es.pb(mp(mp(y, -x), -1));
        }
    }
    sort(all(es), [](const pair<PII,int>& u, const pair<PII,int>& v) {
        int x1=u.fi.fi, y1=u.fi.se;
        int x2=v.fi.fi, y2=v.fi.se;
        int det=x1*y2-x2*y1;
        if(det!=0) return det>0;
        if(u.se!=v.se) return u.se>0;
        return false;
    });
    int ans=base, cur=base;
    for(const auto& e: es) {
        cur+=e.se;
        setmax(ans, cur);
    }
    return ans;
}

int solve_worst(const VPI& a) {
    int base=0;
    vector<pair<PII, int>> es;
    replr(i, 1, sz(a)) {
        int x=a[i].fi-a[0].fi, y=a[i].se-a[0].se;
        if(x>=0 && y>=0) {
            ++base; continue;
        }
        if(x<0 && y<0) {
            continue;
        }
        if(y<0) {
            ++base;
            es.pb(mp(mp(-y, x), -1));
        } else {
            es.pb(mp(mp(y, -x), 1));
        }
    }
    sort(all(es), [](const pair<PII,int>& u, const pair<PII,int>& v) {
        int x1=u.fi.fi, y1=u.fi.se;
        int x2=v.fi.fi, y2=v.fi.se;
        int det=x1*y2-x2*y1;
        if(det!=0) return det>0;
        if(u.se!=v.se) return u.se>0;
        return false;
    });
    int ans=base, cur=base;
    for(const auto& e: es) {
        cur+=e.se;
        setmax(ans, cur);
    }
    return ans;
}

int main() {
    int n; scanf("%d", &n);
    VPI a(n); repn(i, n) scanf("%d%d", &a[i].fi,&a[i].se);

    int best=n-solve_best(a);
    int worst=solve_worst(a)+1;
    printf("%d %d\n", best, worst);
    return 0;
}
