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
typedef vector<string> VS;
template<class T> bool setmax(T &_a, T _b) { if(_b>_a) { _a=_b; return true; } return false; }
template<class T> bool setmin(T &_a, T _b) { if(_b<_a) { _a=_b; return true; } return false; }
template<class T> T gcd(T _a, T _b) { return _b==0?_a:gcd(_b,_a%_b); }

bool solve(VPI a) {
    if(a.size()==1) {
        return a[0].se==4;
    }
    if(a.size()==2) {
        PII x=a[0], y=a[1];
        if(x.se>y.se) swap(x, y);
        if(x.se!=2) return false;
        return y.se<=x.fi+1;
    }
    rep(l, sz(a)-2, sz(a)-1) if(a[l].se>=2) {
        VPI b=a; b[l].se-=2; if(b[l].se==0) b.erase(b.begin()+l);
        const LL top=a[l].fi;
        repn(i, sz(b)) if(b[i].se>=2 && b[i].fi>1) {
            const LL per=b[i].fi-1;
            LL cnt=0, tot=0;
            repn(j, sz(b)) if(j!=i) {
                LL cur=(b[j].se-1)/per+1;
                cnt+=cur;
                tot+=cur*b[j].fi;
            }
            if(tot>top) {
                continue;
            } else if(tot==top) {
                if(cnt==b[i].se-1) return true;
                continue;
            } else {
                if(b[i].se-2<cnt) continue;
                LL extra=b[i].se-2-cnt;
                if(top-tot-1>=extra) return true;
            }
        }
    }
    return false;
}

int main() {
    int n; scanf("%d", &n);
    VPI a(n); for(PII& p: a) scanf("%d%d", &p.fi,&p.se);
    printf("%s\n", solve(a)?"YES":"NO");
    return 0;
}
