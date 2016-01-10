#include <cassert>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

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

const int N=200010;
const int Q=200010;

struct Query {
    int l, r, l2, r2, x;
};

int a[N], n;
Query q[Q]; int  qnum;
int ans[Q];

template<class T> class FenwickTree {
    std::vector<T> a;
    int n; T v0;
public:
    FenwickTree() { }
    FenwickTree(int _n, T _v) : a(size_t(_n+1), _v), n(_n), v0(_v) { }
    void add(int x, T v) { for(; x<=n; x+=(x&-x)) a[(size_t)x]+=v; }
    T get(int x) const { T r=v0; for(; x>=1; x-=(x&-x)) r+=a[(size_t)x]; return r; }
    T get(int l, int r) { return get(r)-get(l-1); }
};

void solve() {
    vector<PII> vec;
    rep(i, 1, n) vec.pb(mp(-a[i], i));
    rep(i, 1, qnum) vec.pb(mp(-q[i].x, -i));
    sort(all(vec));

    //rep(i,1,qnum) printf("(%d) %d %d %d %d",q[i].x,q[i].l,q[i].r,q[i].l2,q[i].r2);

    FenwickTree<int> tr(n, 0);
    repn(i, vec.size()) {
        int k=vec[i].se;
        if(k>0) {
            tr.add(k, 1);
        } else {
            k=-k;
            int ret=0;
            ret+=tr.get(q[k].l, q[k].r);
            if(q[k].l2>0)
                ret+=tr.get(q[k].l2, q[k].r2);
            ans[k]=ret;
        }
    }

    rep(i, 1, qnum) printf("%d\n", ans[i]);
}

int main() {
    scanf("%d", &n);
    rep(i, 1, n) scanf("%d", &a[i]);

    qnum=0;
    int num; scanf("%d", &num);
    int offset=0;
    while(num--) {
        char s[5]; scanf("%s", s);
        if(s[0]=='L') offset=(offset+1)%n;
        if(s[0]=='R') offset=(offset+n-1)%n;
        if(s[0]=='H') {
            int l, r, x; scanf("%d%d%d", &l,&r,&x);
            l+=offset, r+=offset;
            Query cur; cur.x=x;
            if(r<n) {
                cur.l=l+1, cur.r=r+1;
                cur.l2=-1;
            } else if (l>=n) {
                cur.l=l+1-n, cur.r=r+1-n;
                cur.l2=-1;
            } else {
                cur.l=l+1, cur.r=n;
                cur.l2=1, cur.r2=r-n+1;
            }
            q[++qnum]=cur;
        }
    }

    solve();

    return 0;
}
