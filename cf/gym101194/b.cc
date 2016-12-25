#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <memory>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

#define all(a) (a).begin(), (a).end()
#define sz(a) static_cast<int>((a).size())
#define fillchar(a, x) memset(a, x, sizeof(a))
#define rep(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define irep(i, a, b) for(int i=int(a); i>=int(b); --i)
#define replr(i, a, b) rep(i, a, (b)-1)
#define reprl(i, a, b) irep(i, (b)-1, a)
#define repn(i, n) rep(i, 0, (n)-1)
#define irepn(i, n) irep(i, (n)-1, 0)
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
template<class T, class S> ostream& operator<<(ostream& os, const pair<T, S>& v) { return os<<"("<<v.first<<", "<<v.second<<")"; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& v) { os<<"["; repn(i, sz(v)) { if(i) os<<", "; os<<v[i]; } return os<<"]"; }
template<class T> bool setmax(T &_a, T _b) { if(_b>_a) { _a=_b; return true; } return false; }
template<class T> bool setmin(T &_a, T _b) { if(_b<_a) { _a=_b; return true; } return false; }
template<class T> T gcd(T _a, T _b) { return _b==0?_a:gcd(_b,_a%_b); }

const LL inf=LL(2e18);
const int N=100010;

LL pow2[N];

struct HemiBuilder {
    const int n;
    string cur;
    bool failed=false, demo_failed;
    char demo_ch;
    
    int a, p;

    HemiBuilder(int _n) : n(_n) {
        a=n, p=(n+1)/2;
    }

    void demo(char c) {
        demo_ch=c;
        demo_failed=false;

        a=n-sz(cur)-1;

        if(failed) {
            p=-1;
        } else {
            int i=sz(cur), j=n-i-1;
            if(j<i) {
                if(c==cur[j]) {
                    p=0;
                } else {
                    p=-1;
                    demo_failed=true;
                }
            } else {
                int r=max(j-i-1, 0);
                p=(r+1)/2;
            }
        }
    }

    void apply() {
        cur+=demo_ch;
        if(demo_failed) failed=true;
    }
};

struct Builder {
    const int n;
    string cur;
    char demo_ch;
    HemiBuilder even, odd;

    Builder(int _n) : n(_n), even((n+1)/2), odd(n/2) {}

    void demo(char c) {
        if(sz(cur)%2==0) {
            even.demo(c);
        } else {
            odd.demo(c);
        }
        demo_ch=c;
    }

    void apply() {
        if(sz(cur)%2==0) {
            even.apply();
        } else {
            odd.apply();
        }
        cur+=demo_ch;
    }

    LL count() const {
        //printf("count (%d %d) (%d %d)\n",odd.a,odd.p,even.a,even.p);
        VPI v;
        if(odd.a>=0 && even.p>=0) {
            v.pb(mp(odd.a+even.p, 1));
        }
        if(odd.p>=0 && even.a>=0) {
            v.pb(mp(odd.p+even.a, 1));
        }
        if(odd.p>=0 && even.p>=0) {
            v.pb(mp(odd.p+even.p, -1));
        }
        if(v.empty()) {
            return 0;
        }
        sort(all(v), greater<PII>());
        LL x=v[0].se; int t=v[0].fi;
        replr(i, 1, sz(v)) {
            int d=t-v[i].fi;
            if(x>inf/pow2[d]) return inf;
            if(x<-inf/pow2[d]) return -inf;
            x*=pow2[d], t-=d;
            x+=v[i].se;
        }
        if(x>inf/pow2[t]) return inf;
        if(x<-inf/pow2[t]) return -inf;
        x*=pow2[t];
        //printf("   result=%lld\n",x);
        return x;
    }
};

string solve(int n, LL k) {
    Builder builder(n);
    if(builder.count()<k) {
        return "NOT FOUND!";
    }
    repn(i, n) {
        builder.demo('0');
        if(builder.count()<k) {
            k-=builder.count();
            builder.demo('1');
            assert(builder.count()>=k);
        }
        builder.apply();
    }
    return builder.cur;
}

void check(int n, int p) {
    Builder b(8);
    for(char ch: string("0000100")) {
        b.demo(ch);
        b.apply();
    }
    printf("%lld\n", b.count());


    vector<string> s;
    repn(k, 1<<n) {
        string cur, odd, even;
        irepn(i, n) {
            char ch=(k&(1<<i))?'1':'0';
            (i%2==0?odd:even)+=ch;
            cur+=ch;
        }
        string rodd=odd; reverse(all(rodd));
        string reven=even; reverse(all(reven));
        if(odd==rodd || even==reven) s.pb(cur);
    }
    rep(i, 1, p) {
        string std; if(i-1<sz(s)) std=s[i-1];
        string ans=solve(n, i);
        printf("%d: %s %s\n", i,std.c_str(), ans.c_str());
        if(!std.empty()) assert(std==ans);
    }
}

int main() {
    pow2[0]=1;
    replr(i, 1, N) {
        pow2[i]=min(pow2[i-1]*2, inf);
    }

    //check(20, 99999); exit(0);

    int cs; scanf("%d", &cs);
    rep(i, 1, cs) {
        int n; LL k;
        scanf("%d%lld\n", &n, &k);
        string s=solve(n, k);
        printf("Case #%d: %s\n", i,s.c_str());
    }
    return 0;
}
