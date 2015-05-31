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
    /*
    while(times%10==0 && x%10==0) {
        x/=10, times/=10;
        --tlen;
    }
    */
    p10[0]=1;
    forint(i, 1, 18) p10[i]=p10[i-1]*10;
}

VL ans;
int n;

bool check(int i, LL a) {
    int r=n-i; // done
    LL t=a*x;
    if(r<=tlen) {
        // last r digits are zeros
        if(t%p10[r]!=0) return false;
    }
    if(r>=tlen+1) {
        LL a1=(t/p10[tlen])%10, an=a%10;
        LL maxa=a1*p10[n-1]+p10[n-1]-1;
        if(maxa<an*p10[n-1]*times) return false;
        LL mina=a1*p10[n-1];
        if(mina>(an*p10[n-1]+p10[n-1])*times) return false;
    }
    if(r>=tlen+2) {
        // digits 8~r = a's digits 2~(r-6)
        LL u=(t/p10[tlen+1])%p10[r-tlen-1];
        LL v=(a/10)%p10[r-tlen-1];
        if(u!=v) return false;
    }
    if(i==0) {
        LL a1=a/p10[n-1], a2=a%10;
        LL b=a-a1*p10[n-1]-a2+a2*p10[n-1]+a1;
        //printf("i=%d a=%lld b=%lld t=%lld\n",i,a,b,t);
        if(b*times!=t) return false;
    }
    return true;
}

int cnt;

void dfs(int i, LL a) {
    ++cnt;
    if(!check(i, a)) return;
    //printf("i=%d a=%lld\n",i,a);
    if(i==0) {
        ans.PB(a); return;
    }
    int le=(i>1?0:1), ri=9;
    forint(d, le, ri)
        dfs(i-1, a+p10[n-i]*d);
}

void solve(int cs) {
    ans.clear();
    cnt=0;
    for(n=1; n<=10; ++n) {
        dfs(n, 0);
    }
    //printf("cnt=%d\n",cnt);
    printf("Case #%d:\n", cs);
    printf("%d\n", (int)ans.size());
    if(ans.size()>0) {
        forn(i, ans.size()) cout<<ans[i]<<" ";
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
