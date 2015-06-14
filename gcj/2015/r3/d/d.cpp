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
template<class T> bool setmax(T &_a, T _b) { if(_b>_a) { _a=_b; return true; } return false; }
template<class T> bool setmin(T &_a, T _b) { if(_b<_a) { _a=_b; return true; } return false; }
template<class T> T gcd(T _a, T _b) { return _b==0?_a:gcd(_b,_a%_b); }

map<LL, LL> a;
int n;

void init() {
    int m; cin>>m;
    static LL p[55555], f[55555];
    a.clear();
    forint(i, 1, m) cin>>p[i];
    forint(i, 1, m) cin>>f[i];
    LL sum=0;
    forint(i, 1, m) {
        a[p[i]]+=f[i];
        sum+=f[i];
    }
    n=0;
    while((1LL<<n)<sum) ++n;
    assert((1LL<<n)==sum);
}

LL ans[66];

bool reduce(map<LL, LL> &s, LL d) {
    vector<PLL> vs(all(s));
    if(d==0) {
        s.clear();
        for(PLL p: vs) {
            if(p.se%2!=0) return false;
            s[p.fi]=p.se/2;
        }
        return true;
    }
    LL tmp=0;
    if(d<0) { d=-d; tmp=d; }
    for(PLL p: vs) {
        LL num=s[p.fi];
        if(s[p.fi+d]<num) return false;
        s[p.fi+d]-=num;
    }
    map<LL, LL> t;
    for(PLL p: s) if(p.se!=0)
        t[p.fi+tmp]=p.se;
    s=t;
    return true;
}

void solve(int cs) {
    assert(a[0]>0);

    forint(i, 1, n) {
        bool found=false;
        for(PLL p: a) if(p.se>0) {
            map<LL, LL> b=a;
            if(reduce(b, p.fi)) {
                found=true;
                ans[i]=p.fi;
                a=b;
                break;
            }
        }
        assert(found);
    }

    printf("Case #%d: ", cs); fflush(stdout);
    forint(i, 1, n) cout<<ans[i]<<" "; cout<<endl;
}

int main() {
    int csn; scanf("%d", &csn);
    forint(cs, 1, csn) {
        init();
        solve(cs);
    }
    return 0;
}
