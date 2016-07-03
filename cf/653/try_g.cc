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

int main() {
    rep(n, 1,17) if(2) {
        printf("%2d: ", n);
        VI c(n);
        repn(s, 1<<n) {
            VI a; repn(i, n) if(s&(1<<i)) a.pb(i);
            int mid=sz(a)/2;
            if(sz(a)%2==0) {
                rep(i, 0, mid-1) c[a[i]]--;
                rep(i, mid, sz(a)-1) c[a[i]]++;
            } else {
                rep(i, 0, mid-1) c[a[i]]--;
                rep(i, mid+1, sz(a)-1) c[a[i]]++;
            }
        }
        repn(i, (17-n)/2) printf("       "); if(n%2==0) printf("    ");
        repn(i, n) printf("%6d ", c[i]); printf("\n");
    }
    return 0;
}
