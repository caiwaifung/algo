// 10:28 - 10:58 - no idea
// 11:38
// 12:04 - 12:36 - wa sam - wrong algo
// 8:47pm
//   - read solutions
// 10:54 - 11:09 - ac
#include <cassert>
#include <queue>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <cmath>
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

const int MAXN=10010;
const int MAXE=50010;

VI es[MAXN]; int ea[MAXE], eb[MAXE];
int n, m;

void read_input() {
    scanf("%d%d", &n,&m);
    rep(i, 1, n) es[i].clear();
    rep(i, 1, m) {
        int a, b; scanf("%d%d", &a,&b);
        ++a, ++b;
        es[a].pb(b), es[b].pb(a);
        ea[i]=a, eb[i]=b;
    }
}

int d[MAXN][MAXN], c[MAXE], cnt;
bool has[MAXN][MAXE];

bool bfs(int start) {
    queue<int> que;
    fillchar(d[start], 0xff);
    que.push(start); d[start][start]=0;
    while(!que.empty()) {
        int x=que.front(); que.pop();
        for(int y: es[x]) if(d[start][y]<0) {
            d[start][y]=d[start][x]+1;
            que.push(y);
        }
    }
    rep(i, 1, m) if(d[start][ea[i]]==d[start][eb[i]])
        return false;
    return true;
}

bool same(int i, int j) {
    return d[ea[i]][ea[j]]==d[eb[i]][eb[j]] && d[ea[i]][eb[j]]==d[eb[i]][ea[j]];
}

int solve() {
    rep(i, 1, n) if(!bfs(i)) return -1;

    fillchar(c, 0xff);
    cnt=0;
    rep(i, 1, m) if(c[i]<0) {
        c[i]=++cnt;
        rep(j, i+1, m) if(c[j]<0 && same(i, j))
            c[j]=cnt;
    }
    rep(i, 1, m) rep(j, i+1, m)
        if(same(i, j)!=(c[i]==c[j]))
            return -1;
    
    return cnt;
}

int main() {
    freopen("/Users/fqw/Downloads/restaurant_chains.txt", "r", stdin); freopen("out.txt", "w", stdout);
    int csn; scanf("%d", &csn);
    rep(cs, 1, csn) { fprintf(stderr, "\033[0;31m### [%d/%d]\033[0m\n",cs,csn);
        read_input();
        int ans=solve();
        printf("Case #%d: %d\n", cs, ans);
    }
    return 0;
}

