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

const int MAXN=200010;
const int MAXNodes=MAXN*18;

int a[MAXN];
int n, m;

struct FunctionalSegmentTree {
    struct Node {
        int minv, buf;
        int l, r;
    } tr[MAXNodes];
    int roots[MAXN];
    int curtime, num;

    // return timestamp
    int init() {
        curtime=0;
        roots[0]=0;
        num=0;
        return 0;
    }

    int minv(int x) { return x==0 ? 0 : tr[x].minv; }
    int acquire(int x, bool need_new) {
        if(x!=0 && !need_new)
            return x;
        int cur=++num;
        if(x==0) {
            tr[x].minv=tr[x].buf=0;
            tr[x].l=tr[x].r=0;
        }
        else {
            memmove(&tr[cur], &tr[x], sizeof(Node));
        }
        return cur;
    }

    int add(int x, int s, int t, int st, int en, int val, bool need_new=true) {
        x=acquire(x, need_new);
        if(st<=s && t<=en) {
            tr[x].minv+=val;
            tr[x].buf+=val;
            return x;
        }

        bool newed=false;
        if(tr[x].buf!=0) {
            newed=true;
            tr[x].l=acquire(tr[x].l, true);
            tr[tr[x].l].minv+=tr[x].buf;
            tr[tr[x].l].buf+=tr[x].buf;
            tr[x].r=acquire(tr[x].r, true);
            tr[tr[x].r].minv+=tr[x].buf;
            tr[tr[x].r].buf+=tr[x].buf;

            tr[x].buf=0;
        }

        int mid=(s+t)/2;
        if(st<=mid)
            tr[x].l=add(tr[x].l, s, mid, st, en, val, !newed);
        if(mid<en)
            tr[x].r=add(tr[x].r, mid+1, t, st, en, val, !newed);
        tr[x].minv=min(minv(tr[x].l), minv(tr[x].r));
        return x;
    }
    int getmin(int x, int s, int t, int st, int en) {
        if(x==0)
            return 0;
        if(st<=s && t<=en)
            return tr[x].minv;
        int mid=(s+t)/2, ans=1<<30;
        if(st<=mid)
            setmin(ans, getmin(tr[x].l, s, mid, st, en));
        if(mid<en)
            setmin(ans, getmin(tr[x].r, mid+1, t, st, en));
        return ans+tr[x].buf;
    }

    // return timestamp
    int add(int l, int r, int v) {
        ++curtime;
        roots[curtime]=add(roots[curtime-1], 1, n, l, r, v);
        return curtime;
    }

    int getmin(int timestamp, int l, int r) {
        assert(0<=timestamp && timestamp<=curtime);
        int ans=getmin(roots[timestamp], 1, n, l, r);
        return ans;
    }
} tree;

int timestamps[MAXN];
int vals[MAXN];
PII as[MAXN];

void preprocess() {
    forint(i, 1, n)
        as[i]=MP(a[i], i);
    sort(as+1, as+n+1);

    timestamps[0]=tree.init();
    forint(i, 1, n) {
        vals[i]=as[i].fi;
        int pos=as[i].se;
        int l=max(pos-m+1, 1), r=pos;
        //printf("p=%d l=%d r=%d\n",pos,l,r);
        timestamps[i]=tree.add(l, r, 1);
    }
}

int query(int l, int r, int q) {
    int i=int(lower_bound(vals+1, vals+n+1, q)-vals);
    assert(i>=1 && i<=n+1);
    //printf("q=%d i=%d\n",q,i);
    int ans=tree.getmin(i-1, l, r);
    return ans;
}

int main() {
    //printf("%.4lf\n", (sizeof(tree)+sizeof(as))/1024./1024.);
    scanf("%d%d", &n,&m);
    forint(i, 1, n) scanf("%d", &a[i]);

    preprocess();

    int cs; scanf("%d", &cs);
    int preans=0;
    while(cs--) {
        int l, r, x;
        scanf("%d%d%d", &l,&r,&x);
        int q=x^preans;

        int ans=query(l, r, q);
        printf("%d\n", ans);
        preans=ans;
    }

    return 0;
}
