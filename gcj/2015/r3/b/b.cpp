#include <algorithm>
#include <iostream>
#include <sstream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <set>
#include <map>
using namespace std;

#define _ (size_t)
#define all(a) a.begin(), a.end()
#define forint(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define forintdown(i, a, b) for(int i=int(a); i>=int(b); --i)
#define forn(i, n) forint(i, 0, (n)-1)
#define forndown(i, n) forintdown(i, (n)-1, 0)
#define fillchar(a, x) memset(a, x, sizeof(a))
#define fi first
#define se second
#define PB push_back
#define MP make_pair
#ifdef DEBUG
    #define _debug(args...) { fprintf(stderr, args); fflush(stderr); }
#else
    #define _debug(args...) {}
#endif
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

const int MAXN=1010;
const int MAXK=110;

int s[MAXN];
int n, k;

void init() {
    cin>>n>>k;
    forint(i, k, n) cin>>s[i];
}

int u[MAXK], d[MAXK];
int val[MAXN];

void solve(int cs) {
    forint(i, 1, k) {
        val[i]=0;
        u[i]=d[i]=0;
    }
    forint(i, k+1, n) {
        val[i]=val[i-k]+(s[i]-s[i-1]);
        setmax(u[(i-1)%k+1], val[i]);
        setmin(d[(i-1)%k+1], val[i]);
    }

    int ans=0, r=0;
    forint(i, 1, k) {
        val[i]=-d[i];
        setmax(ans, val[i]+u[i]);
    }
    forint(i, 1, k) r+=ans-(val[i]+u[i]);
    int sum=0;
    forint(i, 1, k) sum+=val[i];
    sum=(sum%k+k)%k;
    int need=(s[k]%k+k)%k;
    int delta=((need-sum)%k+k)%k;
    if(delta>r) ++ans;

    printf("Case #%d: ", cs);
    cout<<ans<<endl;
}

int main() {
    freopen("b.out", "w", stdout);
    int csn; scanf("%d", &csn);
    forint(cs, 1, csn) {
        _debug("cs=%d/%d\n", cs,csn);
        init();
        solve(cs);
    }
    return 0;
}
