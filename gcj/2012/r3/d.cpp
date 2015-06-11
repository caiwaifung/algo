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

string s; 

void init() {
    int k; cin>>k; 
    assert(k==2);
    cin>>s;
}

char trans(char c) {
    if(c=='o') return '0';
    if(c=='i') return '1';
    if(c=='e') return '3';
    if(c=='a') return '4';
    if(c=='s') return '5';
    if(c=='t') return '7';
    if(c=='b') return '8';
    if(c=='g') return '9';
    return c;
}

bool g[266][266], vis[266];
int in_deg[266], out_deg[266];
VI cur;

void dfs(int x) {
    cur.PB(x); vis[x]=true;
    forn(y, 255) if(g[x][y] || g[y][x])
        if(!vis[y]) dfs(y);
}

void solve(int cs) {
    fillchar(g, false);
    forn(i, s.size()-1) {
        char c1=s[i], c2=s[i+1];
        int i1=int(c1), i2=int(c2);
        int j1=int(trans(c1)), j2=int(trans(c2));
        g[i1][i2]=true;
        g[i1][j2]=true;
        g[j1][i2]=true;
        g[j1][j2]=true;
    }
    fillchar(in_deg, 0);
    fillchar(out_deg, 0);
    forn(i, 255) forn(j, 255) if(g[i][j]) { ++in_deg[j]; ++out_deg[i]; }

    int ans=0;
    fillchar(vis, false);
    forn(i, 255) if(!vis[i]) {
        cur.clear();
        dfs(i);
        int cnt=0;
        for(int x: cur) {
            int d=out_deg[x]-in_deg[x];
            if(d>0) cnt+=d;
        }

        int en=0;
        for(int x: cur) en+=out_deg[x];

        if(en>0) {
            if(cnt==0) cnt=1;
        }
        else
            assert(cnt==0);
        ans+=en+cnt;
    }
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
