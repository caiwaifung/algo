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

const int N=555;

double a[N][N];
int n;

void solve() {
    rep(i, 1, n) {
        int i0=i;
        rep(i1, i, n) if(abs(a[i1][i])>abs(a[i0][i])) i0=i1;
        if(i0!=i) {
            rep(j, 0, n) swap(a[i][j], a[i0][j]);
        }
        rep(i1, i+1, n) {
            double c=a[i1][i]/a[i][i];
            rep(j, 0, n) a[i1][j]-=a[i][j]*c;
        }
    }
    irep(i, n, 1) {
        a[i][0]/=a[i][i];
        rep(i1, 1, i-1) a[i1][0]-=a[i1][i]*a[i][0];
    }
}

int main() {
    scanf("%d", &n);
    rep(i, 1, n) rep(j, 1, n) scanf("%lf", &a[j][i]);
    rep(i, 1, n) a[i][i]-=1, a[i][0]=0;
    rep(i, 0, n) a[n][i]=1;
    solve();
    printf("%.15lf\n", a[1][0]);
    return 0;
}
