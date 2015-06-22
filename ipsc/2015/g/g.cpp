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
#include "../progressbar.h"
using namespace std;

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

const int MAXN=10010;

int l[MAXN], r[MAXN], c[MAXN];
int n;

void dfs(int x, int d, int color) {
    queue<PII> que;
    que.push(mp(x, d));
    while(!que.empty()) {
        x=que.front().fi;
        d=que.front().se;
        que.pop();
        c[x]=color;
        if(d>0) {
            for(int y=l[x]; y; y=r[y])
                que.push(mp(y, d-1));
        }
    }
}

int main() {
    freopen("g.out", "w", stdout);
    int csn; scanf("%d", &csn);
    progress_start();
    repn(cs, csn) {
        int q; scanf("%d%*d%d", &n,&q);
        fillchar(l, 0);
        rep(i, 2, n) {
            int j; scanf("%d", &j);
            r[i]=l[j], l[j]=i;
        }
        rep(i, 1, n) c[i]=1;
        LL ans=0;
        rep(i, 1, q) {
            if(i%10000==0) progress_update((cs+i/(double)q)/csn);
            int x, d, z; scanf("%d%d%d",&x,&d,&z);
            if(z==0) {
                ans=(ans+LL(c[x])*LL(i))%LL(1e9+7);
            }
            else {
                dfs(x, d, z);
            }
        }
        printf("%d\n", (int)ans);
    }
    return 0;
}
