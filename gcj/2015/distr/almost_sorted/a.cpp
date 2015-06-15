#include <message.h>
#include <almost_sorted.h>
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

const LL MOD=1<<20;

int num, id;
int n;

void solve() {
    n=(int)NumberOfFiles(); int md=(int)MaxDistance();
    int each=(n-1)/num+1;
    int s=each*id, t=min(n, each*(id+1));
    int l=max(0, s-md), r=min(n, t+md);
    VL vec;
    for(int i=l; i<r; ++i) vec.PB(Identifier(i));
    sort(all(vec));
    LL ans=0;
    for(int i=l; i<r; ++i) {
        if(i>=s && i<t) {
            LL cur=vec[i-l];
            cur=(cur%MOD*i)%MOD;
            ans=(ans+cur)%MOD;
        }
    }
    if(id>0) {
        PutLL(0, ans);
        Send(0);
    }
    else {
        forint(i, 1, num-1) {
            Receive(i);
            LL tmp=GetLL(i);
            ans=(ans+tmp)%MOD;
        }
        cout<<ans<<endl;
    }
}

int main() {
    num=NumberOfNodes(), id=MyNodeId();
    solve();
    return 0;
}
