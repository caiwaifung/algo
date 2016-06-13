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

const int MAXN=110;
const int MAXL=110;

bool check(VI a, int mx) {
    //printf("check %d\n",mx);
    //for(int x: a) printf("%d ", x); printf("\n");

    static bool f[MAXL][MAXL][2][MAXL][2];
    fillchar(f, false);
    rep(i, 0, mx) repn(iz, 2) {
        f[0][i][iz][i][iz]=true;
    }
    rep(l, 0, 99) rep(i, 0, mx) repn(iz, 2) {
        rep(j, 0, mx) repn(jz, 2) if(f[l][i][iz][j][jz]) {
            if(j>0) {
                if(l+j<=100) f[l+j][i][iz][j-1][j==1]=true;
            }
            if(j<mx && jz==1) {
                if(l+j+1<=100) f[l+j+1][i][iz][j+1][1]=true;
            }
        }
    }

    static bool g[MAXN][MAXL][2];
    fillchar(g, false);
    g[0][mx][0]=true;
    repn(k, sz(a)) rep(i, 0, mx) repn(iz, 2) if(g[k][i][iz]) {
        rep(j, 0, mx) repn(jz, 2) if(f[a[k]][i][iz][j][jz]) {
            g[k+1][j][jz]=true;
        }
    }
    return g[sz(a)][mx][1];
}

bool check1(VI a) {
    int s=0; 
    for(int x: a) s+=x;
    return s==2;
}

int main() {
    int n; scanf("%d", &n);
    VI a(n); for(int& x: a) scanf("%d", &x);
    int mx=n==1?a[0]/2:min(a[0], a.back());
    irep(i, mx, 2) {
        VI b=a;
        b[0]-=i; if(b[0]==0) b.erase(b.begin());
        b.back()-=i; if(b.back()==0) b.pop_back();
        if(check(b, i-1)) {
            printf("%d\n", i); return 0;
        }
    }
    if(check1(a)) {
        printf("1\n");
    } else {
        printf("no quotation\n");
    }
    return 0;
}
