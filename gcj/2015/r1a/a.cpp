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

int main() {
    int ncs; scanf("%d", &ncs);
    forint(cs, 1, ncs) {
        int n; scanf("%d", &n);
        VI a(n); forn(i, n) scanf("%d", &a[i]);
        int ans1=0, d=0;
        forn(i, n-1) if(a[i]>a[i+1]) {
            ans1+=a[i]-a[i+1];
            setmax(d, a[i]-a[i+1]);
        }
        int ans2=0;
        forn(i, n-1) {
            ans2+=min(a[i], d);
        }
        printf("Case #%d: %d %d\n", cs,ans1, ans2);
    }
    return 0;
}
