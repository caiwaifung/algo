#include <algorithm>
#include <map>
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

const int V=500010;
const int N=7;

VI primes;
int a[N];
int n;

void find_primes() {
    static bool is[V];
    fillchar(is, true);
    primes.clear();
    rep(i, 2, V-1) if(is[i]) {
        primes.pb(i);
        for(int j=i*2; j<V; j+=i) is[j]=false;
    }
}

int f[V];

int solve() {
    irep(cur, V-1, 1) {
        VI as;
        repn(i, n) if(a[i]>=cur) as.pb(a[i]/cur);
        if(as.empty()) {
            f[cur]=0; continue;
        }
        int ans=0;
        for(int x: as) ans+=x;
        for(int p: primes) {
            if(p*LL(cur)>=V) break;
            int tmp=0; for(int x: as) tmp+=x%p;
            setmin(ans, f[cur*p]+tmp);
        }
        f[cur]=ans;
    }
    return f[1];
}

int main() {
    find_primes();

    cin>>n; repn(i, n) cin>>a[i];
    int ans=solve();
    cout<<ans<<endl;
    return 0;
}
