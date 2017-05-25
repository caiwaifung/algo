#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define sz(a) static_cast<int>(a.size())
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

const int N=5010;

int a[N][N];
int n, m;

int get(int i, int j) {
    return a[i][j]==0?j:a[i][j]=get(i, a[i][j]);
}

int solve() {
    int ans=0;
    rep(i, 1, n) {
        static int st[N];
        int top=0; st[0]=0;
        //printf("\n");
        rep(j, 1, m+1) {
            //printf("%d ", a[i][j]);
            while(top>0 && a[i][st[top]]>=a[i][j]) {
                setmax(ans, (j-st[top-1]-1)*a[i][st[top]]);
                --top;
            }
            st[++top]=j;
        }
    }
    return ans;
}

int main() {
    scanf("%d%d", &n,&m);
    fillchar(a, 0);
    int k; scanf("%d", &k);
    int ans=0;
    while(k--) {
        int x1, y1, x2, y2; scanf("%d%d%d%d", &x1,&y1,&x2,&y2);
        if(x1>x2) swap(x1, x2); ++x1;
        if(y1>y2) swap(y1, y2); ++y1;
        setmax(ans, (x2-x1+1)*(y2-y1+1));
        x1=max(1, x1-1); x2=min(n, x2+1);
        y1=max(1, y1-1); y2=min(m, y2+1);
        rep(x, x1, x2) {
            for(int y=get(x, y1); y<=y2; y=get(x, y+1)) {
                a[x][y]=y+1;
            }
        }
    }
    rep(x, 1, n) rep(y, 1, m) {
        if(a[x][y]==0) {
            a[x][y]=a[x-1][y]+1;
        } else {
            a[x][y]=0;
        }
    }
    setmax(ans, solve());
    printf("%d\n", ans);
    return 0;
}
