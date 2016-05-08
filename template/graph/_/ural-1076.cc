#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

#define _ (int)
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

const int N=150;

int a[N][N], n;

int solve() {
    static int cx[N], cy[N], lnk[N];
    fillchar(cx, 0); fillchar(cy, 0);
    fillchar(lnk, -1);
    repn(cur, n) {
        static int pre[N], d[N];
        static bool vis[N];
        fillchar(d, 50); fillchar(vis, false);
        int j0=-1;
        while(1) {
            //printf("cur=%d j0=%d\n",cur,j0);
            int i0=j0<0?cur:lnk[j0];
            if(i0<0) break;
            int j1=-1, d1=1<<30;
            repn(j, n) if(!vis[j]) {
                if(setmin(d[j], a[i0][j]-cx[i0]-cy[j])) pre[j]=j0;
                if(setmin(d1, d[j])) j1=j;
            }
            cx[cur]+=d1;
            repn(j, n) if(!vis[j]) {
                d[j]-=d1;
            } else {
                cx[lnk[j]]+=d1;
                cy[j]-=d1;
            }
            vis[j1]=true, j0=j1;
        }
        while(j0>=0) {
            int j=pre[j0];
            lnk[j0]=j<0?cur:lnk[j];
            j0=j;
        }
    }
    int r=0; repn(i, n) r+=a[lnk[i]][i];
    return r;
}

int main() {
    scanf("%d", &n);
    int maxv=0;
    repn(i, n) repn(j, n) {
        scanf("%d", &a[i][j]);
        setmax(maxv, a[i][j]);
    }
    int ans=0;
    repn(i, n) repn(j, n) {
        ans+=a[i][j];
        a[i][j]=maxv-a[i][j];
    }
    ans=ans-maxv*n+solve();
    printf("%d\n", ans);

    return 0;
}
