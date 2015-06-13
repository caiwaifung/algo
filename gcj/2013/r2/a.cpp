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

const LL MOD=1000002013;
LL n, s[1010], t[1010], p[1010];
int m;

void init() {
    cin>>n>>m;
    forint(i, 1, m) cin>>s[i]>>t[i]>>p[i];
}

LL cal(LL i, LL v) {
    // a_0 + ... + (v+1)
    LL ans=v+(i-1)+(v+1);
    ans=ans*(i-1)/2;
    ans=ans%MOD;
    return ans;
}

void solve(int cs) {
    vector<PLL> a;
    LL want=0;
    forint(i, 1, m) {
        (want+=p[i]*(cal(t[i], n-t[i]+s[i])-cal(s[i],n))) %=MOD;
        a.PB(MP(s[i], -p[i]));
        a.PB(MP(t[i], p[i]));
    }
    LL ans=0;
    sort(all(a));
    multiset<PLL> b;
    for(PII x: a) {
        LL i=x.fi, num=x.se;
        if(num<0) {
            num=-num;
            (ans-=cal(i, n)*num) %=MOD;
            b.insert(MP(i,num));
        }
        else {
            while(num>0) {
                PLL k=*(--b.end());
                b.erase(b.find(k));
                LL z=min(k.se, num);
                num-=z, k.se-=z;
                if(k.se>0) b.insert(k);
                (ans+=cal(i, n-i+k.fi)*z) %=MOD;
            }
        }
    }
    ans=((want-ans)%MOD+MOD)%MOD;
    printf("Case #%d: ", cs);
    cout<<ans<<endl;
}

int main() {
    int csn; scanf("%d", &csn);
    forint(cs, 1, csn) {
        init();
        solve(cs);
    }
    return 0;
}
