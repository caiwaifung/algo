// 10:24
// 10:31 - 10:42 - ac
#include <cassert>
#include <cstring>
#include <iostream>
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

const int N=55;
const int dx[4]={0, 1, 0, -1};
const int dy[4]={1, 0, -1, 0};

int a[N][N];
int n, m;

void read_input() {
    cin>>n>>m; rep(i, 1, n) {
        static char b[N]; scanf("%s", b+1);
        rep(j, 1, m) a[i][j]=int(b[j]-'0');
    }
}

int solve() {
    int ans=0;
    rep(x, 1, n) rep(y, 1, m) repn(d, 4) {
        int sum=0;
#define inside(x, y) ((x)>=1 && (x)<=n && (y)>=1 && (y)<=m)
        for(int x1=x, y1=y; inside(x1, y1); ) {
            sum+=a[x1][y1];
            x1+=dx[d], y1+=dy[d];
            for(int x2=x1, y2=y1, r=sum, v=0; inside(x2, y2); ) {
                r-=a[x2][y2]; if(r<0) break;
                ++v; setmax(ans, v);
                //printf("(%d,%d) (%d,%d) (%d,%d) %d r=%d\n",x,y,x1,y1,x2,y2,v,r);
                x2+=dx[d], y2+=dy[d];
            }
        }
    }
    return ans;
}

int main() {
    freopen("/Users/fqw/Downloads/risky_slide.txt", "r", stdin); freopen("out.txt", "w", stdout);
    int csn; scanf("%d", &csn);
    rep(cs, 1, csn) { fprintf(stderr, "\033[0;31m### [%d/%d]\033[0m\n",cs,csn);
        read_input();
        int ans=solve();
        printf("Case #%d: %d\n", cs, ans);
    }
    return 0;
}

