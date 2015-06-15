#include <message.h>
#include <johnny.h>
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

int num, id;
int n;

bool v[1010];

int go(int i) {
    fillchar(v, true);
    queue<int> que;
    que.push(i); v[i]=false;
    int cnt=n;
    while(!que.empty()) {
        int x=que.front(); que.pop();
        --cnt;
        forn(y, n) if(v[y] && !IsBetter(y, x)) {
            v[y]=false;
            que.push(y);
        }
    }
    return cnt;
}

void solve() {
    n=(int)NumberOfCards();
    int each=(n-1)/num+1;
    int s=each*id, t=min(each*(id+1), n);

    int ans=0;
    for(int i=s; i<t; ++i) setmax(ans, go(i));

    if(id>0) {
        PutInt(0, ans); Send(0);
    }
    else {
        forint(i, 1, num-1) {
            Receive(i); int tmp=GetInt(i);
            setmax(ans, tmp);
        }
        if(ans==0) printf("IMPOSSIBLE\n");
        else printf("%d\n", ans);
    }
}

int main() {
    num=NumberOfNodes(), id=MyNodeId();
    solve();
    return 0;
}
