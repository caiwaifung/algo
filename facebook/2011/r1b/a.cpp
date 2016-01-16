// 8:44
// 8:47 - 9:07 - ac
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

const int adx[4]={0, 1, 0, -1};
const int ady[4]={1, 0, -1, 0};
const int bdx[4]={1, 1, -1, -1};
const int bdy[4]={1, -1, 1, -1};
const int cdx[8]={-1, -1, -1, 0, 0, 1, 1, 1};
const int cdy[8]={-1, 0, 1, -1, 1, -1, 0, 1};
const int ddx[8]={-2, -1, 1, 2, 2, 1, -1, -2};
const int ddy[8]={1, 2, 2, 1, -1, -2, -2, -1};

int board[22][22]; int N=16;
bool threatened[99]; 

void go(int x, int y, const int dx[], const int dy[], int dn, bool once) {
#define inside(x0, y0) ((x0)>=1 && (x0)<=N && (y0)>=1 && (y0)<=N)
    repn(k, dn) {
        int x0=x, y0=y;
        while(1) {
            x0+=dx[k], y0+=dy[k];
            if(!inside(x0, y0)) break;
            if(board[(x0)][(y0)]>0) { 
                threatened[board[(x0)][(y0)]]=true; 
                break; 
            }
            if(once) break;
        }
    }
}

void solve(int cs) {
    int num; scanf("%d", &num);
    int px[99], py[99]; char tp[99];
    fillchar(board, 0);
    rep(i, 1, num) {
        char buf[9];
        scanf("%s%d%d", buf, &px[i],&py[i]);
        board[px[i]][py[i]]=i;
        tp[i]=buf[0];
    }

    fillchar(threatened, 0);
    rep(i, 1, num) {
        int x=px[i], y=py[i];
        if(tp[i]=='K') {
            go(x, y, cdx, cdy, 8, true);
        } else if(tp[i]=='Q') {
            go(x, y, cdx, cdy, 8, false);
        } else if(tp[i]=='R') {
            go(x, y, adx, ady, 4, false);
        } else if(tp[i]=='B') {
            go(x, y, bdx, bdy, 4, false);
        } else if(tp[i]=='N') {
            go(x, y, ddx, ddy, 8, true);
        } else if(tp[i]=='S') {
            go(x, y, ddx, ddy, 8, false);
        } else if(tp[i]=='A') {
            go(x, y, ddx, ddy, 8, true);
            go(x, y, bdx, bdy, 4, false);
        } else if(tp[i]=='E') {
            rep(k, 1, num) if(k!=i) threatened[k]=true;
        } else printf("BAD!\n");
    }

    int ans=0; rep(k, 1, num) if(threatened[k]) ++ans;

    printf("Case #%d: %d\n", cs, ans);
}

int main() {
    freopen("/Users/fqw/Downloads/chess_.txt", "r", stdin); freopen("out.txt", "w", stdout);
    int csn; scanf("%d", &csn);
    rep(cs, 1, csn) {
        fprintf(stderr, "[%d/%d]\n",cs,csn);
        solve(cs);
    }
    return 0;
}
