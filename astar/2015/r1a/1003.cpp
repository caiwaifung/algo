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

LL a[100010], b[100010];
int n;

void init() {
    scanf("%d", &n); int x;
    forint(i, 1, n) {
        scanf("%d", &x); a[i]=x;
    }
}

bool ok(LL lim) {
    b[1]=a[1]-lim;
    forint(i, 2, n) {
        LL le=a[i]-lim, ri=a[i]+lim;
        setmax(le, b[i-1]+1);
        if(le>ri) return false;
        b[i]=le;
    }
    return true;
}

void solve() {
    LL le=0, ri=1LL<<50;
    while(le<ri) {
        LL mid=(le+ri)/2;
        if(ok(mid)) ri=mid;
            else le=mid+1;
    }
    cout<<le<<endl;
}

int main() {
    int cs=0, csn; scanf("%d", &csn); 
    while(csn--) {
        init();
        printf("Case #%d:\n", ++cs);
        solve();
    }
    return 0;
}
