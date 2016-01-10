// 11:57 - 
#include <cassert>
#include <algorithm>
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

const LL MOD=LL(1e9)+9;

int num;

struct Mat {
    LL a[260][260];
    Mat() { fillchar(a, 0); }
    Mat(int diag) {
        fillchar(a, 0); repn(i, num) a[i][i]=diag;
    }
};

Mat mul(const Mat& a, const Mat& b) {
    Mat c;
    repn(i, num) repn(j, num) repn(k, num) {
        (c.a[i][j]+=a.a[i][k]*b.a[k][j]) %=MOD;
    }
    return c;
}

Mat pow(Mat a, int b) {
    Mat c(1);
    for(; b>0; b>>=1, a=mul(a,a))
        if(b&1) c=mul(c, a);
    return c;
}

void solve(int n, int m) {
    num=1<<(m*2);

    Mat tr;
    repn(x, num) repn(cur, 1<<m) {
        bool ok=true;
        repn(i, m) if(cur&(1<<i)) {
            if(i-2>=0) if((x>>m)&(1<<(i-2))) ok=false;
            if(i+2<m) if((x>>m)&(1<<(i+2))) ok=false;
            if(i-1>=0) if(x&(1<<(i-1))) ok=false;
            if(i+1<m) if(x&(1<<(i+1))) ok=false;
        }
        if(ok) {
            int y=(x>>m)|(cur<<m);
            tr.a[x][y]+=1;
        }
    }

    Mat fn = pow(tr, n);

    LL ans=0;
    repn(i, num) (ans+=fn.a[0][i])%=MOD;

    printf("%d\n", (int)ans);
}

int main() {
    int cs; scanf("%d", &cs);
    while(cs--) {
        int n, m; scanf("%d%d", &m,&n);
        solve(n, m);
    }
    return 0;
}
