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
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef pair<int,int> PII;
typedef pair<double,double> PDD;
typedef vector<LL> VL;
typedef vector<int> VI;
typedef vector<PII> VPI;
typedef vector<string> VS;
template<class T> void setmax(T &a, T b) { if(b>a) a=b; }
template<class T> void setmin(T &a, T b) { if(b<a) a=b; }
template<class T> T gcd(T a, T b) { return b==0?a:gcd(b,a%b); }


int a[1010][1010];
int n, m;

void init() {
    scanf("%d%d", &n,&m);
    forint(i, 1, n) forint(j, 1, m) scanf("%d", &a[i][j]);
}

const int dx[4]={0,1,0,-1};
const int dy[4]={1,0,-1,0};

int f[1010*1010];
int gf(int x) {
    return f[x]==0 ? x : (f[x]=gf(f[x]));
}
int d(int x, int y) {
    x-=y; if(x<0) x=-x;
    return x;
}

pair<int,PII> es[1010*1010*2];
int en;

void solve(int cs) {
    fillchar(f, 0);
    en=0;
    forint(i, 1, n) forint(j, 1, m) {
        forn(k, 2) {
            int i0=i+dx[k], j0=j+dy[k];
            if(i0>=1 && i0<=n && j0>=1 && j0<=m)
                es[en++]=MP(d(a[i][j],a[i0][j0]), MP((i-1)*m+j, (i0-1)*m+j0));
        }
    }
    sort(es, es+en);
    int ans=0;
    forn(i, en) {
        int x=es[i].se.fi;
        int y=es[i].se.se;
        if(gf(x)!=gf(y)) {
            ans+=es[i].fi;
            f[gf(x)]=gf(y);
        }
    }
    printf("Case #%d:\n", cs);
    printf("%d\n", ans);
}

int main() {
    //printf("%.3lf\n", (sizeof(es)+sizeof(a)+sizeof(f))/1024./1024.);
    int csn; scanf("%d", &csn);
    forint(cs, 1, csn) {
        init();
        solve(cs);
    }
    return 0;
}
