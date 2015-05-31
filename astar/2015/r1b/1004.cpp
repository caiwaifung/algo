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

LL x, times; int tlen;
LL p10[20];

void init() {
    double a; scanf("%lf", &a);
    x=LL(a*1e6+0.5);
    times=LL(1e6);
    tlen=6;
    while(times%10==0 && x%10==0) {
        x/=10, times/=10;
        --tlen;
    }
    p10[0]=1;
    forint(i, 1, 18) p10[i]=p10[i-1]*10;
}

VL ans;

void go(int n, LL a1, LL an) {
    LL d=(an-a1)*p10[n-1]+(a1-an);
    LL a=d*times/(x-times);

    LL u1=(a/p10[n-1]); if(!(u1>=1 && u1<=9 && u1==a1)) return;
    LL un=a%10; if(!(un==an)) return;
    LL b=a+d;
    if(!(b*times==a*x)) return;
    ans.PB(a);
}

void solve(int cs) {
    ans.clear();
    forint(n, 1, 10) {
        forint(a1, 1, 9) forint(an, 0, 9)
            go(n, a1, an);
    }
    printf("Case #%d:\n", cs);
    printf("%d\n", (int)ans.size());
    if(ans.size()>0) {
        forn(i, ans.size()) {
            if(i>0) cout<<" ";
            cout<<ans[i];
        }
        cout<<endl;
    }
}

int main() {
    int csn; scanf("%d", &csn);
    forint(cs, 1, csn) {
        init();
        solve(cs);
    }
    return 0;
}
