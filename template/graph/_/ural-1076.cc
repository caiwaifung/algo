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

int match() {
    VI cx(n, 0), cy(n, 0);
    VI lnk(n, -1);
    repn(cur, n) {
        VI slack(n, 1<<30), pre(n, -1);
        vector<bool> vis(n, false);
        int j0=-1;
        while(1) {
            if(j0>=0) vis[j0]=true;
            int i0=(j0<0?cur:lnk[j0]); if(i0<0) break;
            int minv=1<<30, minj=-1;
            repn(j, n) if(!vis[j]) {
                if(setmin(slack[j], a[i0][j]-cx[i0]-cy[j]))
                    pre[j]=j0;
                if(setmin(minv, slack[j]))
                    minj=j;
            }
            cx[cur]+=minv;
            repn(j, n) if(vis[j]) {
                cx[lnk[j]]+=minv;
                cy[j]-=minv;
            } else {
                slack[j]-=minv;
            }
            j0=minj;
        }
        while(j0>=0) {
            int j=pre[j0];
            lnk[j0]=(j<0?cur:lnk[j]), j0=j;
        }
    }
    int ans=0; repn(j, n) ans+=a[lnk[j]][j];
    return ans;
}

int main() {
    scanf("%d", &n);
    repn(i, n) repn(j, n) scanf("%d", &a[i][j]);
    int ans=-100*n;
    repn(i, n) repn(j, n) {
        ans+=a[i][j]; a[i][j]=100-a[i][j];
    }
    ans+=match();
    printf("%d\n", ans);
    return 0;
}
