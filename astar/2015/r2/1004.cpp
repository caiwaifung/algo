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

int a[MAXN*2];
int n, d;

void init() {
    scanf("%d%d",&n,&d);
    forint(i, 1, n) scanf("%d",&a[i]);
    forint(i, 1, n) a[i+n]=a[i];
}

struct DQue {
    PLL q[MAXN*2];
    int qi[MAXN*2];
    int ss, tt, limit;

    void init(int limit) {
        this->limit=limit;
        ss=1, tt=0;
    }
    void add(int i, PLL p) {
        while(ss<=tt && q[tt]>=p) --tt;
        if(ss<=tt && qi[ss]<=i-limit) ++ss;
        q[++tt]=p;
        qi[tt]=i;
    }
    PLL get() {
        assert(ss<=tt);
        return q[ss];
    }
} que;

void solve(int cs) {
    PII ansi=MP(0,0); LL ans=0;

    que.init(n/2);
    forint(i, 1, n*2) {
        int id=i; if(id>n) id-=n;

        if(i>1) {
            PLL t=que.get();
            LL val=LL(a[i])+LL(i)*LL(d)-t.fi;
            PII vi=MP(id, (int)t.se);
            if(vi.fi>vi.se) swap(vi.fi, vi.se);
            if(MP(-val,vi) < MP(-ans,ansi)) {
                ans=val;
                ansi=vi;
            }
        }
        
        LL v=LL(i)*LL(d)-LL(a[i]);
        que.add(i, MP(v,(LL)id));
    }
    //printf("ans=%lld\n",ans);

    printf("Case #%d:\n", cs);
    printf("%d %d\n", ansi.fi,ansi.se);
}

int main() {
    int csn; scanf("%d", &csn);
    forint(cs, 1, csn) {
        init();
        solve(cs);
    }
    return 0;
}
