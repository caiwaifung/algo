#include <algorithm>
#include <iostream>
#include <sstream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <set>
#include <map>
using namespace std;

#define _ (size_t)
#define all(a) a.begin(), a.end()
#define forint(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define forintdown(i, a, b) for(int i=int(a); i>=int(b); --i)
#define forn(i, n) forint(i, 0, (n)-1)
#define forndown(i, n) forintdown(i, (n)-1, 0)
#define fillchar(a, x) memset(a, x, sizeof(a))
#define fi first
#define se second
#define PB push_back
#define MP make_pair
#ifdef DEBUG
    #define _debug(args...) { fprintf(stderr, args); fflush(stderr); }
#else
    #define _debug(args...) {}
#endif
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef pair<int,int> PII;
typedef pair<double,double> PDD;
typedef vector<LL> VL;
typedef vector<int> VI;
typedef vector<PII> VPI;
typedef vector<string> VS;
typedef map<LL, LL> MLL;
template<class T> bool setmax(T &_a, T _b) { if(_b>_a) { _a=_b; return true; } return false; }
template<class T> bool setmin(T &_a, T _b) { if(_b<_a) { _a=_b; return true; } return false; }
template<class T> T gcd(T _a, T _b) { return _b==0?_a:gcd(_b,_a%_b); }

MLL a;

void init() {
    int m; cin>>m;
    static LL p[10010], f[10010];
    a.clear();
    forint(i, 1, m) cin>>p[i];
    forint(i, 1, m) cin>>f[i];
    forint(i, 1, m) a[p[i]]+=f[i];
}

VL ans;

void extract_zeros() {
    LL n1=a.begin()->se;
    LL n2=a.rbegin()->se;
    assert(n1==n2);
    LL n=max(n1, n2);
    //_debug("n=%lld\n",n);
    auto tmp=a;
    a.clear();
    for(PLL p: tmp) {
        assert(p.se%n==0);
        a[p.fi]=p.se/n;
    }
    int num=0;
    while((1LL<<num)<n) {
        ++num;
        ans.PB(0);
    }
}

MLL extract(const MLL &t, LL x) {
    assert(x>=0);
    MLL u=t, r;
    for(PLL p: t) {
        LL num=u[p.fi];
        if(num>0) {
            assert(u[p.fi+x]>=num);
            u[p.fi]-=num;
            u[p.fi+x]-=num;
            r[p.fi]=num;
        }
    }
    return r;
}

bool able(VL xs, LL r) {
    VL us; us.PB(0);
    for(LL x: xs) {
        VL vs;
        for(LL u: us) {
            vs.PB(u);
            vs.PB(u+x);
        }
        sort(all(vs));
        vs.erase(unique(all(vs)), vs.end());
        us=vs;
    }
    return find(all(us), r)!=us.end();
}

void solve(int cs) {
    ans.clear();
    extract_zeros();

    VL xs;
    while(a.size()>1) {
        assert(a.begin()->se==1);
        LL x=(++a.begin())->fi-a.begin()->fi;
        xs.PB(x);
        a=extract(a, x);
    }
    assert(a.size()==1 && a.begin()->se==1);
    LL r=-a.begin()->fi;
    assert(r>=0);

    sort(all(xs));
    while(xs.size()>0) {
        LL x=xs.back();
        xs.pop_back();
        if(able(xs, r-x)) {
            ans.PB(-x);
            r-=x;
        }
        else {
            assert(able(xs, r));
            ans.PB(x);
        }
    }
    assert(r==0);

    sort(all(ans));
    cout<<"Case #"<<cs<<": ";
    for(LL x: ans) cout<<x<<" "; cout<<endl;
}

int main() {
    int csn; scanf("%d", &csn);
    forint(cs, 1, csn) {
        _debug("cs=%d/%d\n",cs,csn);
        init();
        solve(cs);
    }
    return 0;
}
