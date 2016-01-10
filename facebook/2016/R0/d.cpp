#include <cassert>
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

string words[330];
int n, k; 

struct Node {
    int n, sum;
    int c[30];
};

Node tr[100010];
int f[100010][333];
int num;

void dfs(int x) {
    fillchar(f[x], 50);
    rep(i, 0, tr[x].n) f[x][i]=0;
    int have=tr[x].n;
    repn(t, 30) { int y=tr[x].c[t]; if(y) {
        dfs(y);
        have+=tr[y].sum;
        irep(i, have, 0) rep(j, 1, tr[y].sum) {
            if(j>i) break;
            setmin(f[x][i], f[x][i-j]+f[y][j]+2);
        }
    }}
}

void solve(int cs) {
    LL ans=0;
    scanf("%d%d", &n, &k);
    rep(i, 1, n) {
        static char s[100010]; scanf("%s", s);
        words[i]=string(s);
    }

    num=1; fillchar(tr, 0);
    rep(i, 1, n) {
        int x=1; tr[x].sum++;
        for(char c: words[i]) {
            int y=int(c-'a');
            if(tr[x].c[y]==0) tr[x].c[y]=++num;
            x=tr[x].c[y]; tr[x].sum++;
        }
        tr[x].n++;
    }

    dfs(1);
    ans=f[1][k];

    printf("Case #%d: %lld\n", cs, ans+k);
}

int main() {
    int cs; scanf("%d", &cs);
    rep(i, 1, cs) solve(i);
    return 0;
}
