#include <message.h>
#include <load_balance.h>
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

VL make(VL xs) {
    VL p;
    forn(s, 1<<xs.size()) {
        LL t=0;
        forn(j, xs.size()) if(s&(1<<j)) t+=xs[j];
        p.PB(t);
    }
    return p;
}

bool go(VL xs, LL want) {
    if(want<0) return false;
    VL ys, zs;
    forn(i, xs.size())
        if(i&1) ys.PB(xs[i]);
            else zs.PB(xs[i]);
    VL as=make(ys);
    VL bs=make(zs);
    for(LL &b: bs) b=want-b;
    sort(all(as));
    sort(all(bs));
    size_t j=0;
    for(size_t i=0; i<as.size(); ++i) {
        while(j<bs.size() && bs[j]<as[i]) ++j;
        if(j<bs.size() && bs[j]==as[i])
            return true;
    }
    return false;
}

int main() {
    int num=NumberOfNodes(), id=MyNodeId();
    int n=GetN();
    int m=0;
    while(m<n && (1<<(m+1))<num) ++m;

    if(id<(1<<m)) {
        int ans=0;

        LL sum=0;
        forn(i, n) sum+=GetWeight(i);
        if(sum%2==0) {
            LL want=sum/2;
            VL xs;
            forn(i, n) {
                if(i<m) {
                    if(id&(1<<i)) want-=GetWeight(i);
                } else
                    xs.PB(GetWeight(i));
            }
            if(go(xs, want)) ans=1;
        }

        PutInt(num-1, ans);
        Send(num-1);
    }
    if(id==num-1) {
        int ans=0;
        forn(i, 1<<m) {
            Receive(i);
            ans|=GetInt(i);
        }
        cout<<(ans?"POSSIBLE":"IMPOSSIBLE")<<endl;
    }
    return 0;
}
