// 11:09
// 11:13 - 11:28 - wa sample
// 11:52 - 11:57 - ac
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

const int NUM=20010;
const int M=110;

int tr[NUM][33], dep[NUM], is[NUM];
int n, m, num;

void read_input() {
    scanf("%d%d", &n,&m);
    fillchar(tr, 0); fillchar(is, 0);
    num=1; dep[1]=0;
    rep(i, 1, n) {
        static char s[NUM]; scanf("%s", s+1);
        int len=(int)strlen(s+1);
        int x=1;
        rep(j, 1, len) {
            int ch=int(s[j]-'a');
            if(tr[x][ch]==0) {
                tr[x][ch]=++num;
                dep[num]=dep[x]+1;
            }
            x=tr[x][ch];
        }
        is[x]=1;
    }
}

int f[NUM][M];

void go(int x) {
    fillchar(f[x], 55);
    f[x][0]=0;
    if(is[x]) f[x][1]=dep[x];
    for(int ch=0; ch<26; ++ch) {
        int y=tr[x][ch]; if(y==0) continue;
        go(y);
        irep(i, m, 0) rep(j, 1, m-i)
            setmin(f[x][i+j], f[x][i]+f[y][j]);
    }
    setmin(f[x][1], max(1,dep[x]));
}

int solve() {
    go(1);
    return f[1][m];
}

int main() {
    freopen("/Users/fqw/Downloads/autocomplete_strikes_back.txt", "r", stdin); freopen("out.txt", "w", stdout);
    int csn; scanf("%d", &csn);
    rep(cs, 1, csn) { fprintf(stderr, "\033[0;31m### [%d/%d]\033[0m\n",cs,csn);
        read_input();
        int ans=solve();
        printf("Case #%d: %d\n", cs, ans);
    }
    return 0;
}

