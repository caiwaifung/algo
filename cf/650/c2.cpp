#include <cassert>
#include <queue>
#include <functional>
#include <set>
#include <map>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
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

vector<vector<int>> a, cnt;
vector<set<PII>> rows, cols;
int n, m;

struct Ret {
    int ans, x, y;
    Ret() : ans(-1), x(0), y(0) {}
    Ret(int ans) : ans(ans), x(0), y(0) {}
    Ret(int x, int y) : ans(-1), x(x), y(y) {}
};
vector<vector<Ret>> ret;
int resolve_ret(int i, int j) {
    if(ret[i][j].ans<0) ret[i][j].ans=resolve_ret(ret[i][j].x, ret[i][j].y);
    return ret[i][j].ans;
}

vector<PII> que;
int ss, tt, ans;

int main() {
    scanf("%d%d", &n,&m);
    a.resize(n, VI(m));
    rows.resize(n);
    cols.resize(m);
    repn(i, n) repn(j, m) {
        scanf("%d", &a[i][j]);
        rows[i].emplace(a[i][j], j);
        cols[j].emplace(a[i][j], i);
    }
    cnt.resize(n, VI(m));
    repn(i, n) repn(j, m) {
        cnt[i][j]=0;
        if(*rows[i].begin()<mp(a[i][j], j)) ++cnt[i][j];
        if(*cols[j].begin()<mp(a[i][j], i)) ++cnt[i][j];
    }

    ret.resize(n, vector<Ret>(m));

    que.resize(n*m+1);
    ss=tt=0; repn(i, n) repn(j, m) if(cnt[i][j]==0) que[++tt]=mp(i, j);
    ans=0;
    while(ss<tt) {
        ++ans; bool used=false;
        int tt_holder=tt;
        while(ss<tt_holder) {
            int i, j; tie(i,j)=que[++ss];
            rows[i].erase(rows[i].begin());
            cols[j].erase(cols[j].begin());
            #define dec(i, j) if(--cnt[i][j]==0) que[++tt]=mp(i,j)
            if(!rows[i].empty()) dec(i, rows[i].begin()->se);
            if(!cols[j].empty()) dec(cols[j].begin()->se, j);
            if(!rows[i].empty() && rows[i].begin()->fi==a[i][j]) {
                ret[i][j]=Ret(i, rows[i].begin()->se);
                continue;
            }
            if(!cols[j].empty() && cols[j].begin()->fi==a[i][j]) {
                ret[i][j]=Ret(cols[j].begin()->se, j);
                continue;
            }
            ret[i][j]=Ret(ans); used=true;
        }
        if(!used) --ans;
    }

    repn(i, n) { repn(j, m) printf("%d ", resolve_ret(i, j)); printf("\n"); }

    return 0;
}
