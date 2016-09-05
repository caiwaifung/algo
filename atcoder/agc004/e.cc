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

const int N=110;

int a[N][N], sx[N][N], sy[N][N], n, m, ex, ey;

void init() {
    scanf("%d%d", &n,&m);
    fillchar(a, 0);
    fillchar(sx, 0);
    fillchar(sy, 0);
    rep(i, 1, n) {
        static char buf[N];
        scanf("%s", buf+1);
        rep(j, 1, m) {
            if(buf[j]=='E') ex=i, ey=j;
            a[i][j]=(buf[j]=='o'?1:0);
            sx[i][j]=a[i][j]+sx[i][j-1];
            sy[i][j]=a[i][j]+sy[i-1][j];
        }
    }
}
int sumx(int x, int y1, int y2) { 
    if(y1>y2) return 0;
    return sx[x][y2]-sx[x][y1-1];
}

int sumy(int x1, int x2, int y) {
    if(x1>x2) return 0;
    return sy[x2][y]-sy[x1-1][y];
}

int f[2][N][N][N];

void solve() {
    int ans=0;
    fillchar(f, 0xff);
    int o1=0, o2=1;
    f[o1][0][0][0]=0;
    rep(l, 0, m) {
        fillchar(f[o2], 0xff);
        rep(r, 0, m-l) rep(u, 0, n) rep(d, 0, n-u) {
            const int val=f[o1][r][u][d]; if(val<0) continue;
            setmax(ans, val);
            const int ex1=ex-d, ex2=ex+u;
            const int ey1=ey-r, ey2=ey+l;
            const int X1=1+u, X2=n-d, Y1=1+l, Y2=m-r;
            if(ey2+1<=Y2) {
                setmax(f[o2][r][u][d], val+sumy(max(X1,ex1), min(X2,ex2), ey2+1));
            }
            if(ey1-1>=Y1) {
                setmax(f[o1][r+1][u][d], val+sumy(max(X1,ex1), min(X2,ex2), ey1-1));
            }
            if(ex2+1<=X2) {
                setmax(f[o1][r][u+1][d], val+sumx(ex2+1, max(Y1,ey1), min(Y2,ey2)));
            }
            if(ex1-1>=X1) {
                setmax(f[o1][r][u][d+1], val+sumx(ex1-1, max(Y1,ey1), min(Y2,ey2)));
            }
        }
        swap(o1, o2);
    }
    printf("%d\n", ans);
}

int main() {
    init();
    solve();
    return 0;
}
