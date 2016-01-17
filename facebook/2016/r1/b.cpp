// 1:07
// 1:21 - 1:50
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm>
using namespace std;

//{{{
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
template<class T> T absv(T _x) { return _x>0?_x:-_x; }
//}}}

int n, nw, nd, D, W[100010];

void read_input() {
    scanf("%d%d%d%d", &n,&nw,&nd,&D);
    rep(i, 1, nw) scanf("%d", &W[i]);
}

LL solve() {
    typedef pair<LL,int> PLI;
    int y=0, idle=nd;
    multiset<PLI> a;
    rep(i, 1, nw) a.insert(mp((LL)W[i], i));
    int tot=0;
    while(1) {
        PLI cur=*a.begin(); a.erase(a.begin());
        if(cur.se>0) { // washer
            if(idle>0) {
                --idle; a.insert(mp(cur.fi+D, -1));
            } else ++y;
            if(LL(tot)+LL(nd-idle)+LL(y)<LL(n))
                a.insert(mp(cur.fi+W[cur.se], cur.se));
        } else { // dryer
            ++tot; if(tot==n) return cur.fi;
            if(y>0) {
                --y; a.insert(mp(cur.fi+D, -1));
            } else {
                ++idle;
            }
        }
    }
    return 0;
}

int main() {
    freopen("/Users/fqw/Downloads/laundro_matt.txt", "r", stdin); freopen("out.txt", "w", stdout);
    int csn; scanf("%d", &csn);
    rep(cs, 1, csn) { fprintf(stderr, "\033[0;31m### [%d/%d]\033[0m\n",cs,csn);
        read_input();
        LL ans=solve();
        printf("Case #%d: %lld\n", cs, ans);
    }
    return 0;
}

