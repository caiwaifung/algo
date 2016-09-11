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

const int N=150;

int a[N][N], n;

int mincost_match() {
    VI x(n, -1000), y(n), matched(n, -1);
    repn(cur, n) {
        VI slack(n, 1<<30), pre(n, -1);
        vector<bool> vis(n, false);
        int j0=-1;
        while(1) {
            const int i0=(j0<0 ? cur : matched[j0]);
            if(i0<0) break;
            int minv=1<<30, minj=-1;
            repn(j, n) if(!vis[j]) {
                if(setmin(slack[j], a[i0][j]-x[i0]-y[j])) {
                    pre[j]=j0;
                }
                if(setmin(minv, slack[j])) {
                    minj=j;
                }
            }
            x[cur]+=minv;
            repn(j, n) if(vis[j]) {
                x[matched[j]]+=minv;
                y[j]-=minv;
            } else {
                slack[j]-=minv;
            }
            j0=minj, vis[j0]=true;
        }
        while(j0>=0) {
            const int j=pre[j0];
            matched[j0]=(j<0 ? cur : matched[j]), j0=j;
        }
    }
    return accumulate(all(x), 0)+accumulate(all(y), 0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin>>n;
    int sum=0;
    repn(i, n) repn(j, n) {
        int x; cin>>x;
        sum+=x;
        a[i][j]=-x;
    }
    sum+=mincost_match();
    cout<<sum<<endl;
    return 0;
}
