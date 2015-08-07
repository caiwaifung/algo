// 20:02 - 20:23 - re sample
//       - 20:25 - tle
//       - 20:30 - ac
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

char init[MAXN][MAXN];
int n, m;
bool inside(int x, int y) { return x>=1 && x<=n && y>=1 && y<=m; }

int rside[MAXN][MAXN]; int get_rside(int x, int y) { 
    return rside[x][y]==0 ? y : (rside[x][y]=get_rside(x, rside[x][y]));
}
int dside[MAXN][MAXN]; int get_dside(int x, int y) { 
    return dside[x][y]==0 ? x : (dside[x][y]=get_dside(dside[x][y], y));
}

bool visited[MAXN][MAXN];
queue<PII> to_kill;
void visit(int x, int y) {
    if(visited[x][y]) return; visited[x][y]=true;
    rside[x][y]=y+1; dside[x][y]=x+1;
    to_kill.push(mp(x, y));
}

struct Rect { 
    int x1, y1, x2, y2; 
    Rect(int x=0, int y=0) { x1=x2=x, y1=y2=y; } 
    int size() const { return (y2-y1)*(x2-x1); }
};
PII rt[MAXN][MAXN];
Rect re[MAXN][MAXN];
PII get_rt(PII p) {
    if(rt[p.fi][p.se]==mp(0, 0))
        return p;
    return rt[p.fi][p.se]=get_rt(rt[p.fi][p.se]);
}

void visit_all(int x1, int y1, int x2, int y2) {
    if(x1==x2) {
        while(1) {
            int y=get_rside(x1, y1);
            if(y>y2) break;
            visit(x1, y);
        }
        return;
    }
    if(y1==y2) {
        while(1) {
            int x=get_dside(x1, y1);
            if(x>x2) break;
            visit(x, y1);
        }
        return;
    }
    assert(false);
}

void merge_blocks(PII a, PII b) {
    if(a==b) return;
    Rect new_rect, r1=re[a.fi][a.se], r2=re[b.fi][b.se];
    if(r1.size()>r2.size()) { swap(a, b); swap(r1, r2); }
    rt[a.fi][a.se]=b;
    new_rect.x1=min(r1.x1, r2.x1);
    new_rect.x2=max(r1.x2, r2.x2);
    new_rect.y1=min(r1.y1, r2.y1);
    new_rect.y2=max(r1.y2, r2.y2);
    re[b.fi][b.se]=new_rect;
    while(r2.x1>new_rect.x1) {
        --r2.x1; visit_all(r2.x1, r2.y1, r2.x1, r2.y2);
    }
    while(r2.x2<new_rect.x2) {
        ++r2.x2; visit_all(r2.x2, r2.y1, r2.x2, r2.y2);
    }
    while(r2.y1>new_rect.y1) {
        --r2.y1; visit_all(r2.x1, r2.y1, r2.x2, r2.y1);
    }
    while(r2.y2<new_rect.y2) {
        ++r2.y2; visit_all(r2.x1, r2.y2, r2.x2, r2.y2);
    }
}

bool killed[MAXN][MAXN];
void kill(int x, int y) {
    if(killed[x][y]) return; killed[x][y]=true;
    rt[x][y]=mp(0, 0);
    re[x][y]=Rect(x, y);
    repn(k, 4) {
        int x0=x+dx[k], y0=y+dy[k];
        if(killed[x0][y0]) {
            merge_blocks(get_rt(mp(x, y)), get_rt(mp(x0, y0)));
        }
    }
}

int main() {
    scanf("%d%d", &n,&m);
    rep(i, 1, n) scanf("%s", init[i]+1);

    fillchar(visited, false);
    fillchar(rside, 0);
    fillchar(dside, 0);
    to_kill=queue<PII>();
    rep(i, 1, n) rep(j, 1, m) if(init[i][j]=='.') visit(i, j);

    fillchar(killed, false);
    while(!to_kill.empty()) {
        PII cur=to_kill.front();
        to_kill.pop();
        kill(cur.fi, cur.se);
    }
    rep(i, 1, n) rep(j, 1, m) if(killed[i][j]) init[i][j]='.';
    rep(i, 1, n) printf("%s\n", init[i]+1);

    return 0;
}
