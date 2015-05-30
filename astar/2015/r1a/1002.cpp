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

int a[10010], n,m;
int id[10010];

void init() {
    scanf("%d%d", &n,&m);
    forint(i, 1, n) scanf("%d", &a[i]);
    VI as; forint(i, 1, n) as.PB(a[i]);
    sort(all(as));
    as.erase(unique(all(as)), as.end());
    forint(i, 1, n) id[i]=(int)(lower_bound(all(as),a[i]) - as.begin()+1);
}

struct Que {
    int q[10010], qi[10010], ss, tt;
    int k, i;
    void init(int k) {
        this->k=k;
        ss=1, tt=0;
        i=0;
    }
    int minv() {
        return q[ss];
    }
    void add(int x) {
        ++i;
        while(ss<=tt && q[tt]>=x) --tt;
        ++tt; q[tt]=x, qi[tt]=i;
        if(ss<=tt && qi[ss]<=i-k) ++ss;
    }
};
Que q1, q2;
int h[10010], num;

int ok(int k) {
    int minv=q1.minv();
    int maxv=-q2.minv();
    return num==k && maxv-minv+1==k;
}

void add(int x, int ix) {
    q1.add(x); q2.add(-x);
    if(h[ix]==0) ++num; ++h[ix];
}
void rm(int ix) {
    --h[ix]; if(h[ix]==0) --num;
}

void answer(int k) {
    int ans=0;
    q1.init(k);
    q2.init(k);
    fillchar(h, 0); num=0;
    forint(i, 1, k) {
        add(a[i], id[i]);
    }
    ans+=ok(k);
    forint(i, k+1, n) {
        rm(id[i-k]);
        add(a[i], id[i]);
        ans+=ok(k);
    }
    printf("%d\n", ans);
}

void solve() {
    forint(i, 1, m) {
        int q; scanf("%d", &q);
        answer(q);
    }
}

int main() {
    int cs=0, csn; 
    //scanf("%d", &csn); 
    csn=1;
    while(csn--) {
        init();
        printf("Case #%d:\n", ++cs);
        solve();
    }
    return 0;
}
