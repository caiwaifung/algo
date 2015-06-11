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

LL M, F, P[220], S[220];
int n;

void init() {
    cin>>M>>F>>n;
    forint(i, 1, n) {
        cin>>P[i]>>S[i];
        ++S[i];
    }
    forint(i, 1, n) forint(j, i+1, n)
        if(P[i]>P[j]) {
            swap(P[i], P[j]);
            swap(S[i], S[j]);
        }
    int tn=n; n=1;
    forint(i, 2, tn) {
        if(S[i]<=S[n]) continue;
        if(P[i]==P[n]) {
            S[n]=S[i]; continue;
        }
        ++n; S[n]=S[i], P[n]=P[i];
    }
}

LL cal(LL t) {
    LL r=M-F*t, ans=0;
    LL la=0;
    forint(i, 1, n) {
        LL lim=S[i]-la; la=S[i];
        LL x=r/P[i]; if(lim<=x/t+5) setmin(x, lim*t);
        ans+=x;
        r-=x*P[i];
    }
    return ans;
}

void solve(int cs) {
    LL le=1, ri=M/F;
    while(le+50<ri) {
        LL m1=le/3*2+ri/3;
        LL m2=le/3+ri/3*2;
        LL v1=cal(m1), v2=cal(m2);
        if(v1>v2) ri=m2;
            else le=m1;
    }
    LL ans=0;
    while(le<=ri) setmax(ans, cal(le++));
    printf("Case #%d: ", cs);
    cout<<ans<<endl;
    //forint(i, 1, M/F) cout<<"  cal("<<i<<")="<<cal(i)<<endl;
}

int main() {
    int csn; scanf("%d", &csn);
    forint(cs, 1, csn) {
        init();
        solve(cs);
    }
    return 0;
}
