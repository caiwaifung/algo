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

struct St {
    LL x[44];
};
int n;

double go(St s, int k, LL r) {
    forint(i, k+1, n)
        --s.x[i];
    LL sum=0, penalty=0;
    forint(i, 1, n) {
        LL d=s.x[k]-s.x[i];
        if(d>0) {
            s.x[i]+=d;
            r-=d;
            if(i<=k) sum+=d;
            penalty+=d;
        }
    }
    if(r<0) return -1;
    
    double ans=double(36*sum)/double(k)-double(penalty);
    forint(i, k+1, n) if(s.x[i]>s.x[i-1]) {
        LL d=s.x[i]-s.x[i-1], num=i-1;
        setmin(d, r/num);
        forint(j, 1, i-1) {
            s.x[j]+=d;
            r-=d;
            if(j<=k) sum+=d;
            penalty+=d;
        }
        setmax(ans, double(36*sum)/double(k)-double(penalty));
    }
    return ans;
}

St st; LL B;

void init() {
    cin>>B>>n;
    fillchar(st.x, 0);
    forint(i, 1, n) cin>>st.x[i];
    n=37;
    sort(st.x+1, st.x+n+1);
}

void solve(int cs) {
    double ans=0;
    forint(i, 1, n) setmax(ans, go(st, i, B));
    printf("Case #%d: ", cs);
    printf("%.17lf\n", ans);
}

int main() {
    int csn; scanf("%d", &csn);
    forint(cs, 1, csn) {
        init();
        solve(cs);
    }
    return 0;
}
