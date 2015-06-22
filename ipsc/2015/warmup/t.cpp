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

LL d[10], cnt[10];

void go(LL n) {
    if(n==0) return;
    if(n==9) {
        rep(i, 1, 9) cnt[i]++; return;
    }
    LL len=1, tmp=9;
    while(tmp!=n) tmp=tmp*10+9, ++len;
    LL x=(n+1)/100;
    repn(i, 10) cnt[i]+=(len-1)*x*9;
    rep(i, 1, 9) cnt[i]+=x*10;
}

void go2(LL n) {
    int a[99], len=0;
    for(LL t=n; t>0; t/=10) a[++len]=int(t%10);

    rep(i, 1, len) cnt[a[i]]++;
    LL cur=1;
    rep(i, 1, len) {
        rep(v, (i==len?1:0), a[i]-1) {
            rep(k, i, len) {
                int val=a[k]; if(k==i) val=v;
                cnt[val]+=cur;
            }
            repn(k, 10) {
                cnt[k]+=(i-1)*(cur/10);
            }
        }
        cur*=10;
    }
}

bool ok(LL n) {
    fillchar(cnt, 0);
    LL cur=9;
    while(1) {
        if(n>cur) {
            go(cur);
            cur=cur*10+9;
            continue;
        }
        go2(n);
        break;
    }
    repn(i, 10) if(cnt[i]>d[i]) return false;
    return true;
}

void print(LL n) {
    LL c[10]; fillchar(c, 0);
    rep(i, 1, n) {
        for(int x=i; x; x/=10) ++c[x%10];
    }

    fillchar(cnt, 0);
    LL cur=9;
    while(1) {
        if(n>cur) {
            go(cur);
            cur=cur*10+9;
            continue;
        }
        go2(n);
        break;
    }
    repn(i, 10) printf("%d: %d %d\n",i,(int)cnt[i],(int)c[i]);
}

int main() {
    //print(9);
    //print(99999);
    //print(12343234);

    int csn; cin>>csn;
    repn(cs, csn) {
        repn(i, 10) cin>>d[i];
        LL le=0, ri=LL(1e18);
        while(le<ri) {
            LL mid=(le+ri+1)/2;
            if(ok(mid)) le=mid;
                else ri=mid-1;
        }
        cout<<le<<endl;
    }
    return 0;
}
