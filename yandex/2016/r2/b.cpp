#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define sz(a) static_cast<int>(a.size())
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

const int B=44;

LL cnt[B][2];

void go(LL n, LL coef) {
    repn(i, B) {
        LL u=1LL<<i;
        LL x=n/(u*2), y=n%(u*2);
        cnt[i][0]+=coef*x*u;
        cnt[i][1]+=coef*x*u;
        if(y<=u) {
            cnt[i][0]+=coef*y;
        } else {
            cnt[i][0]+=coef*u;
            cnt[i][1]+=coef*(y-u);
        }
    }
}

int main() {
    LL l, r; cin>>l>>r;

    fillchar(cnt, 0);
    go(r+1, +1);
    go(l, -1);

    //repn(i, 4) printf("i=%d, 0:%d 1:%d\n",i,int(cnt[i][0]), int(cnt[i][1]));

    LL ans=0;
    repn(i, B) if(cnt[i][1]>cnt[i][0]) ans+=1LL<<i;
    cout<<ans<<endl;
    return 0;
}
