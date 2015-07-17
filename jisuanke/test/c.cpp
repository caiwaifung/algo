#include <algorithm>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <cmath>
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

char s[111];
bool b[111];
int ans[111];
int n, len;

bool dfs(int cur, int i) {
    if(cur>n) {
        assert(i==len+1);
        rep(k, 1, n) printf("%d ", ans[k]); printf("\n");
        return true;
    }
    int x=int(s[i]-'0');
    if(!b[x]) {
        b[x]=true; ans[cur]=x;
        if(dfs(cur+1, i+1)) return true;
        b[x]=false;
    }
    if(i+1<=len) {
        int y=int(s[i+1]-'0');
        x=x*10+y;
        if(!b[x]) {
            b[x]=true; ans[cur]=x;
            if(dfs(cur+1, i+2)) return true;
            b[x]=false;
        }
    }
    return false;
}

int main() {
    scanf("%s", s+1); len=(int)strlen(s+1);
    n=0; int cnt=0;
    while(cnt<len) {
        ++n; if(n<10) cnt++; else cnt+=2;
    }
    assert(cnt==len);

    fillchar(b, true);
    rep(i, 1, n) b[i]=false;
    assert(dfs(1, 1));
    
    return 0;
}
