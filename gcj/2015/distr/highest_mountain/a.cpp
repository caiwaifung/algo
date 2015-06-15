#include <message.h>
#include <highest_mountain.h>
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

int h[1010], n;
int num, id;

bool ans[1010], ans2[1010];

void go() {
    fillchar(ans, true);
    forint(i, 1, n-1) {
        int k=i+1;
        forint(j, i+1, n) {
            if(LL(h[j]-h[i])*LL(k-i) > LL(h[k]-h[i])*LL(j-i)) {
                ans[k]=false;
                k=j;
            }
        }
        //fprintf(stderr,"color %d\n", k);
        //ans[k]=true;
    }
}
 
void solve() {
    n=(int)NumberOfPeaks();
    forint(i, 1, n) h[i]=(int)GetHeight(i-1);
    if(id==0) {
        go();
        memmove(ans2, ans, sizeof(ans));
        reverse(h+1, h+n+1);
        go();
        reverse(ans+1, ans+n+1);
        int cnt=0;
        forint(i, 1, n) if(ans[i] && ans2[i]) ++cnt;
        cout<<cnt<<endl;
    }
}

int main() {
    num=NumberOfNodes(), id=MyNodeId();
    solve();
    return 0;
}
