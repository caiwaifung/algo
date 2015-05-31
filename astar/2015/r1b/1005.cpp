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

const int MAXN=100010;
const int MAXV=1100010;

int a[MAXN], n;

void init() {
    scanf("%d", &n);
    forint(i, 1, n) scanf("%d", &a[i]);
    forint(i, 1, n) a[i]+=n-i;
}

template<class T> class FenwickTree {
    std::vector<T> a;
    int n; T v0;
public:
    FenwickTree() { }
    FenwickTree(int n, T v) : a(size_t(n+1), v), n(n), v0(v) { }
    void add(int x, T v) { for(; x<=n; x+=(x&-x)) a[(size_t)x]=min(a[(size_t)x], v); }
    T get(int x) const { T r=v0; for(; x>=1; x-=(x&-x)) r=min(r, a[(size_t)x]); return r; }
};

int f[MAXN];

void solve(int cs) {
    FenwickTree<int> tr(MAXV, 1<<30);
    tr.add(1, 0);
    forint(i, 1, n) {
        f[i]=tr.get(a[i])+i-1;
        tr.add(a[i], f[i]-i);
    }
    int ans=1<<30;
    forint(i, 1, n) setmin(ans, f[i]+n-i);
    printf("Case #%d:\n", cs);
    printf("%d\n", ans);
}

int main() {
    int csn; scanf("%d", &csn);
    forint(cs, 1, csn) {
        init();
        solve(cs);
    }
    return 0;
}
