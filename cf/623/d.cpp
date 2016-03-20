#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <set>
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

struct Friend {
    double q, Q, R;
    Friend(double p) : q(1-p), Q(1), R(1e50) {}
    Friend advance() const {
        Friend f(0);
        f.q=q, f.Q=Q*q, f.R=(1-f.Q*q)/(1-f.Q);
        return f;
    }
    bool operator <(const Friend& f) const {
        return R>f.R;
    }
};

int main() {
    int n; scanf("%d", &n);
    multiset<Friend> s;
    double cur=1;
    rep(i, 1, n) {
        double p; scanf("%lf", &p), p/=100.;
        Friend f=Friend(p).advance();
        cur*=1-f.Q;
        s.insert(f);
    }
    double ans=n;
    repn(z, 1000000) {
        ans+=1-cur;

        Friend f=*s.begin(); s.erase(s.begin());
        cur*=f.R;
        s.insert(f.advance());
    }
    printf("%.15lf\n", ans);
    return 0;
}
