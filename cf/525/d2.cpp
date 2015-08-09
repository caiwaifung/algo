// 22:30 - 22:39 - wa
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
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

const int MAXN=2020;
const int dx[4]={0, 1, 0, -1};
const int dy[4]={1, 0, -1, 0};

char g[MAXN][MAXN];
int n, m;

bool vis[MAXN][MAXN];

void bfs(int sx, int sy) {
    int x1, y1, x2, y2;
    x1=x2=sx, y1=y2=sy;
    queue<PII> que;
    que.push(mp(sx, sy));
    vis[sx][sy]=true;
    while(!que.empty()) {
        int x=que.front().fi;
        int y=que.front().se;
        g[x][y]='.';
        que.pop();
        repn(k, 4) {
            int x0=x+dx[k], y0=y+dy[k];
            if(!vis[x0][y0]) {
                if(g[x0][y0]=='.' || (x0>=x1 && x0<=x2 && y0>=y1 && y0<=y2)) {
                    vis[x0][y0]=true, que.push(mp(x0, y0));
                    setmin(x1, x0); setmax(x2, x0);
                    setmin(y1, y0); setmax(y2, y0);
                }
            }
        }
    }
}

int main() {
    scanf("%d%d", &n,&m);
    fillchar(g, '#');
    rep(i, 1, n) scanf("%s", g[i]+1);

    fillchar(vis, false);
    rep(i, 1, n) rep(j, 1, m)
        if(g[i][j]=='.' && !vis[i][j]) {
            bfs(i, j);
        }
    rep(i, 1, n) printf("%s\n", g[i]+1);

    return 0;
}
