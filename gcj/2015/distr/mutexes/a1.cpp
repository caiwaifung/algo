#include <message.h>
#include <mutexes.h>
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

const int MAXV=1<<30;

int a[40010], b[40010];
int n, m;
int num, id;

bool x[100010], y[100010];

bool g[1010][1010];

int go() {
    fillchar(g, false);
    g[0][0]=true;
    fillchar(x, false);
    int ans=MAXV;
    forint(i, 1, n) {
        fillchar(y, false);
        forint(j, 1, m) {
            if(g[i-1][j-1]) {
                //fprintf(stderr,"%d %d\n",i,j);
                if(a[i]>0 && y[a[i]] && b[j]>0 && x[b[j]])
                    setmin(ans, i+j);
            }
            if(g[i-1][j-1]) {
                if(a[i]<0 || !y[a[i]]) g[i][j-1]=true;
                if(b[j]<0 || !x[b[j]]) g[i-1][j]=true;
            }
            if(b[j]>0) y[b[j]]=true; else y[-b[j]]=false;
        }
        if(a[i]>0) x[a[i]]=true; else x[-a[i]]=false;
    }
    return ans;
}

void solve() {
    n=NumberOfOperations(0);
    m=NumberOfOperations(1);
    forint(i, 1, n) a[i]=GetOperation(0, i-1);
    forint(i, 1, m) b[i]=GetOperation(1, i-1);

    if(id==0) {
        int ans=go();
        if(ans==MAXV) printf("OK\n");
            else printf("%d\n", ans);
    }
}

int main() {
    num=NumberOfNodes(), id=MyNodeId();
    solve();
    return 0;
}
