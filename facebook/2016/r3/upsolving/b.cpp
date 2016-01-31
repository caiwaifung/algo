#include <cassert>
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

const int MAXN=110;
const int MAXK=1010;

char field[MAXN][MAXN];
int n, m, k;

void read_input() {
    scanf("%d%d%d",&n,&m,&k);
    rep(i, 1, n) scanf("%s", field[i]+1);
}

int f[2][MAXK], o1, o2;

void go(const vector<int>& a) {
    int num=(int)a.size();
    static int g[MAXN][MAXN][2];
    fillchar(g, 50);
    g[0][0][0]=0;
    repn(i, num) rep(c, 0, num) repn(x, 2) {
        repn(y, 2) {
            int c0=c+(a[i]==y?0:1);
            int v0=g[i][c][x]+((x==1 && y==0)?1:0);
            setmin(g[i+1][c0][y], v0);
        }
    }
    static int sel[MAXN];
    rep(i, 0, num) sel[i]=min(g[num][i][0], g[num][i][1]);

    fillchar(f[o2], 50);
    rep(i, 0, k) rep(j, 0, min(i,num))
        setmin(f[o2][i], f[o1][i-j]+sel[j]);
    swap(o1, o2);
}

int solve() {
    fillchar(f, 50); o1=0, o2=1;
    f[o1][0]=0;

    rep(i, 1, n) {
        vector<int> a;
        rep(j, 1, m) a.pb((field[i][j]=='B' || field[i][j]=='C')?1:0);
        go(a);
    }
    rep(j, 1, m) {
        vector<int> a;
        rep(i, 1, n) a.pb((field[i][j]=='C' || field[i][j]=='D')?1:0);
        go(a);
    }

    int ans=1<<30;
    rep(i, 0, k) setmin(ans, f[o1][i]);

    return ans;
}

int main() {
    freopen("/Users/fqw/Downloads/farm.txt", "r", stdin); freopen("out.txt", "w", stdout);
    int csn; scanf("%d", &csn);
    rep(cs, 1, csn) { fprintf(stderr, "\033[0;31m### [%d/%d]\033[0m\n",cs,csn);
        read_input();
        int ans=solve();
        printf("Case #%d: %d\n", cs, ans);
    }
    return 0;
}

