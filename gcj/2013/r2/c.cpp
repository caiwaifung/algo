#include <algorithm>
#include <bitset>
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

bool g[2020][2020];
int n, a[2020], b[2020];

void init() {
    scanf("%d", &n);
    forint(i, 1, n) scanf("%d", &a[i]);
    forint(i, 1, n) scanf("%d", &b[i]);
}

int ans[2020];

void go(VI as, int le, int ri) {
    assert((int)as.size()==ri-le+1);
    if(as.empty()) return;
    sort(all(as));

    int x=as.front();
    int cnt=0;
    VI s1, s2;
    for(int y: as) {
        if(y==x) continue;
        if(g[y][x]) ++cnt, s1.PB(y);
            else s2.PB(y);
    }
    ans[x]=le+cnt;
    go(s1, le, le+(int)s1.size()-1);
    go(s2, ri-(int)s2.size()+1, ri);
}

bitset<2020> acc[2020];
int deg[2020];
void pre() {
    forint(i, 1, n) {
        acc[i].reset();
        acc[i][i]=1;
    }
    fillchar(deg, 0);
    forint(i, 1, n) forint(j, 1, n) if(g[i][j]) ++deg[j];
    queue<int> que;
    forint(i, 1, n) if(deg[i]==0) que.push(i);
    int visited=0;
    while(!que.empty()) {
        ++visited;
        int x=que.front(); que.pop();
        forint(y, 1, n) if(g[x][y]) {
            if(--deg[y]==0) que.push(y);
            acc[y]|=acc[x];
        }
    }
    assert(visited==n);

    forint(i, 1, n) forint(j, 1, n)
        g[i][j]=(acc[j][i]);
}

void solve(int cs) {
    fillchar(g, false);
    forint(i, 1, n) {
        forint(j, 1, i-1) 
            if(a[j]>=a[i]) g[i][j]=true;
        forintdown(j, i-1, 1)
            if(a[j]==a[i]-1) {
                g[j][i]=true; break;
            }
    }
    forint(i, 1, n) {
        forint(j, i+1, n)
            if(b[j]>=b[i]) g[i][j]=true;
        forint(j, i+1, n)
            if(b[j]==b[i]-1) {
                g[j][i]=true; break;
            }
    }

    pre();
    fillchar(ans, 0);
    VI full; forint(i, 1, n) full.PB(i);
    go(full, 1, n);

    printf("Case #%d: ", cs);
    forint(i, 1, n) printf("%d ", ans[i]); printf("\n");
}

int main() {
    freopen("c-large.out", "w", stdout);
    int csn; scanf("%d", &csn);
    forint(cs, 1, csn) {
        fprintf(stderr, "cs=%d/%d\n",cs,csn); fflush(stderr);
        init();
        solve(cs);
    }
    return 0;
}
