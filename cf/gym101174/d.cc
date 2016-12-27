#include <algorithm>
#include <set>
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

const int N=55;

int n, d, AB, A, B;

void init() {
    int c;
    scanf("%d%d%d", &n,&d,&c);
    set<int> as;
    repn(i, c) { int a; scanf("%d", &a); as.insert(a); }
    AB=0, A=B=c;
    repn(i, c) {
        int a; scanf("%d", &a);
        if(as.count(a)) ++AB, --A, --B;
    }
}

double f[N][N][N];
double binom[N][N];

void solve() {
    repn(i, N) binom[i][0]=binom[i][i]=1;
    repn(i, N) rep(j, 1, i-1) binom[i][j]=binom[i-1][j-1]+binom[i-1][j];

    fillchar(f, 0);
    rep(x, 0, A) rep(y, 0, B) rep(z, 0, AB) {
        if(x+z==0 || y+z==0) continue;
        double self=0, s=0;
        rep(u, 0, x) rep(v, 0, min(y,d-u)) rep(w, 0, min(z,d-u-v)) {
            double c=binom[x][u]*binom[y][v]*binom[z][w]*binom[n-x-y-z][d-u-v-w];
            c/=binom[n][d];
            if(u==0 && v==0 && w==0) {
                self=c;
            } else {
                s+=f[x-u][y-v][z-w]*c;
            }
        }
        f[x][y][z]=(1+s)/(1-self);
    }
    printf("%.9lf\n", f[A][B][AB]);
}

int main() {
    init();
    solve();
    return 0;
}
