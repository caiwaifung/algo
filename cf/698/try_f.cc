#include <algorithm>
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
    int a[100];
    while(1) {
        int n; cin>>n;
        rep(i, 1, n) a[i]=i;
        int cnt=0;
        do {
            bool ok=true;
            rep(i, 1, n-1) rep(j, i+1, n) {
                if((gcd(i,j)==1) != (gcd(a[i],a[j])==1)) ok=false;
            }
            if(ok) {
                ++cnt;
                rep(i, 1, n) printf("%d ", a[i]); printf("\n");
            }
        } while(next_permutation(a+1, a+n+1));
        printf("cnt=%d\n",cnt);
    }
    return 0;
}
