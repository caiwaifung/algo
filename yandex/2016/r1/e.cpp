#include <cassert>
#include <algorithm>
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

const int N=1000010;

int a[N], n;

void init() {
    int m; scanf("%d%d", &n,&m);
    static int p[N];
    rep(i, 1, n) scanf("%d", &p[i]);
    sort(p+1, p+n+1);
    p[0]=0, p[n+1]=m+1;
    rep(i, 0, n) a[i]=p[i+1]-p[i]-1;
}

void solve() {
    int ans=n, l=0, r=0;
    rep(i, 0, n) {
        if(l>a[i]) {
            ++ans;
            l=0, r=a[i];
            continue;
        }
        setmin(r, a[i]);
        int l2=a[i]-r, r2=a[i]-l;
        l=l2, r=r2;
    }
    if(l>0) ++ans;
    --ans;
    printf("%d\n", ans);
}

int main() {
    init();
    solve();
    return 0;
}
