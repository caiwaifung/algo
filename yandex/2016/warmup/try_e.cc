#include <algorithm>
#include <set>
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
typedef unsigned long long ULL;
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

int a[(1<<16)+1], n, m;

int f(int x) {
    int r=0;
    irep(i, n, 0) r=(r*x+a[i])&((1<<m)-1);
    return r;
}

bool solve() {
    set<int> u;
    repn(x, 1<<m) u.insert(f(x));
    return int(u.size())==1<<m;
}

int tot=0;
void dfs(int i) {
    if(i>n) {
        int s=0; rep(k, 1, n) s+=a[k];
        int c=0; for(int k=1; k<=n; k+=2) c+=a[k];
        if(solve()) {
            rep(k, 1, n) printf("%d ", a[k]);
            printf("-> yes %d\n",c%2);
            ++tot;
        }
        /*
        if(m==1) {
            assert(solve()==(s%2==1));
        } else {
            assert(solve()==(a[1]%2==1 && s%2==1 && c%2==1));
        }
        */
        return;
    }
    for(a[i]=0; a[i]<(1<<m); ++a[i]) dfs(i+1);
}

int main() {
    //m=5; for(n=1; n<=10; ++n) {
    m=2; n=4;
    tot=0;
    dfs(1);
    printf("n=%d m=%d tot=%d\n", n,m,tot);
    //}
    return 0;
}
