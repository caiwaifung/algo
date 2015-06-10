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

const int MAXN=1010;
const int MAXM=2010;
const int MAXP=510;

int ea[MAXM], eb[MAXM], el[MAXM], er[MAXM], ec[MAXM];
int path[MAXP];
int n, m, p;

void init() {
    cin>>n>>m>>p;
    forint(i, 1, m) cin>>ea[i]>>eb[i]>>el[i]>>er[i];
    forint(i, 1, p) cin>>path[i];
}

LL dis[MAXN];

void go(int x0, LL v0) {
    fillchar(dis, 50);
    dis[x0]=v0;
    forn(t, n) {
        forint(i, 1, m) {
            setmin(dis[eb[i]], dis[ea[i]]+ec[i]);
        }
    }
}

LL d2[MAXN];

void go2(int x0, LL v0) {
    fillchar(d2, 50);
    if(v0<=dis[x0])
        d2[x0]=v0;
    forn(t, n) {
        forint(i, 1, m) {
            LL d=d2[ea[i]]+ec[i];
            if(d<=dis[eb[i]])
                setmin(d2[eb[i]], d);
        }
    }
}

bool vis[MAXM];

bool ok(int len) {
    fillchar(vis, false);
    forint(i, 1, len) vis[path[i]]=true;
    forint(i, 1, m) {
        if(vis[i])
            ec[i]=el[i];
        else
            ec[i]=er[i];
    }
    
    int cur=eb[path[len]];
    LL c0=0;
    forint(i, 1, len) c0+=ec[path[i]];
    go(1, 0);
    if(dis[cur]<c0)
        return false;
    assert(dis[cur]==c0);

    forint(i, 1, m) ec[i]=el[i];
    go2(cur, dis[cur]);
    if(d2[2]>dis[2])
        return false;

    return true;
}

void solve(int cs) {
    int ans=-1;
    forint(i, 1, p) if(!ok(i)) {
        ans=i; break;
    }
    printf("Case #%d: ", cs);
    if(ans<0) printf("Looks Good To Me\n");
        else printf("%d\n", path[ans]);
}

int main() {
    freopen("c-large.out", "w", stdout);
    int csn; scanf("%d", &csn);
    forint(cs, 1, csn) {
        fprintf(stderr, "cs=%d\n",cs);
        init();
        solve(cs);
    }
    return 0;
}
