// 2:10 - 2:28
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

int main() {
    int n; scanf("%d", &n);
    vector<VI> es(n);
    repn(i, n) {
        int k; scanf("%d", &k);
        while(k--) {
            static char s[33]; scanf("%s", s);
            int cur=0;
            for(char c: string(s)) {
                cur|=1<<int(c-'a');
            }
            es[i].pb(cur);
        }
    }

    VI log(1<<n);
    repn(i, n) log[1<<i]=i;

    const int kInf=1<<30;
    vector<VI> ans(n, VI(n, kInf));
    VI g(n);
    repn(i, n) {
        ans[i][i]=0;
        g[i]=1<<i;
    }
    rep(steps, 1, n) {
        VI G(1<<n);
        G[0]=(1<<n)-1;
        replr(s, 1, 1<<n) {
            G[s]=G[s&(s-1)]&g[log[s&-s]];
            //printf("%d %d: %d\n",steps,s,G[s]);
        }
        repn(i, n) {
            for(int s: es[i]) g[i]|=G[s];
            repn(j, n) if(g[i]&(1<<j)) setmin(ans[i][j], steps);
        }
    }
    repn(i, n) {
        repn(j, n) printf("%d ", ans[i][j]<kInf?ans[i][j]:-1);
        printf("\n");
    }

    return 0;
}
