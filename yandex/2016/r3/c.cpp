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

const int N=100010;
const int V=1000010;
const int MV=1000001;

LL a[N], b[N], c[N];
LL sb[N];
int n; LL m;

int tr[V], maxval;
void upt(LL v, int i) {
    if(v<1) return;
    if(v>MV) v=MV;
    for(int x=int(MV-v+1); x<=MV; x+=x&-x)
        setmin(tr[x], i);
}
int get(LL v) {
    if(v<1) return 1;
    if(v>MV) return maxval;
    int r=maxval;
    for(int x=int(MV-v+1); x>=1; x-=x&-x)
        setmin(r, tr[x]);
    return r;
}

LL solve() {
    sb[0]=0; rep(i, 1, n) sb[i]=sb[i-1]+b[i];
    fillchar(tr, 50); maxval=tr[0];
    rep(i, 1, n) upt(a[i]-sb[i-1], i);
    
    static bool vis[V];
    fillchar(vis, false);
    LL ans=0;
    while(1) {
        if(m<=0) return -1;
        if(m>MV) return ans+n;
        if(vis[m]) return -1; vis[m]=true;
        int i=get(m); if(i>=maxval) return ans+n;
        m=m-c[i]+sb[i-1]; ans+=i;
    }
    return 0;
}

int main() {
    int x; scanf("%d%d", &n,&x); m=x;
    rep(i, 1, n) {
        int u, v, w; scanf("%d%d%d", &u,&v,&w);
        a[i]=u, b[i]=v, c[i]=w;
    }
    LL ans=solve();
    cout<<ans<<endl;
    return 0;
}
