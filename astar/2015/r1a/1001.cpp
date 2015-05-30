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
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef pair<int,int> PII;
typedef pair<double,double> PDD;
typedef vector<LL> VL;
typedef vector<int> VI;
typedef vector<PII> VPI;
typedef vector<string> VS;
template<class T> void setmax(T &a, T b) { if(b>a) a=b; }
template<class T> void setmin(T &a, T b) { if(b<a) a=b; }
template<class T> T gcd(T a, T b) { return b==0?a:gcd(b,a%b); }


// ------------------------ template ends here ------------------------ //

const int MAXN=10010;
LL a[MAXN]; int n;
LL m, k;

void init() {
    int _m, _k;
    scanf("%d%d%d", &n,&_m,&_k); m=_m, k=_k;
    forint(i, 1, n) scanf("%lld", &a[i]);
}

bool solve() {
    sort(a+1, a+n+1);
    int j=0;
    while(j<n && a[j+1]<=m) ++j;
    if(j==0) return false;
    if(j==n) return true;
    m=a[j];
    while(k>0) {
        int i=j;
        while(i<n && a[i+1]<=m+k) ++i;
        if(i==j) return false;
        if(i==n) return true;
        j=i;
        m=a[j],--k;
    }
    return false;
}

int main() {
    int cs=0, csn; scanf("%d", &csn); 
    while(csn--) {
        init();
        bool ans=solve();
        printf("Case #%d:\n", ++cs);
        printf("%s\n", ans?"why am I so diao?":"madan!");
    }
    return 0;
}
