#include <cassert>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
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
template<class T> T ext_gcd(T a, T b, T &x, T &y) {
    if(b==0) { x=1, y=0; return a; }
    LL nx, ny, d; d=ext_gcd(b, a%b, nx, ny);
    x=ny, y=nx-(a/b)*ny;
    return d;
}

const LL MOD=LL(1e9)+7;

bool parallel(LL x1, LL y1, LL x2, LL y2) { //{{{
    return x1*y2==x2*y1;
    /*
    if(x1==0 && y1==0) return true;
    if(x2==0 && y2==0) return true;
    LL g1=gcd(x1, y1), g2=gcd(x2, y2);
    x1/=g1, y1/=g1, x2/=g2, y2/=g2;
    if(x1+y1<0) x1=-x1, y1=-y1;
    if(x2+y2<0) x2=-x2, y2=-y2;
    return x1==x2 && y1==y2;
    */
} //}}}

struct Solution;
Solution f(LL a1, LL a2, LL b1, LL b2);

struct Solution { //{{{
    enum {
        MULTI, SINGLE, NONE, ALL
    } type;
    LL i, j, di, dj;

    Solution() 
        : type(NONE) {}
    Solution(bool b) 
        : type(b?ALL:NONE) {}
    Solution(LL i, LL j) 
        : type(SINGLE), i(i), j(j) {}
    Solution(LL i, LL j, LL di, LL dj) 
        : type(MULTI), i(i), j(j), di(di), dj(dj) { 
            assert(di>0 || dj>0); }

    Solution proj() const {
        if(type==MULTI) {
            if(di>0) return Solution(i, 0, di, 0);
            else return Solution(i, 0);
        }
        if(type==SINGLE) return Solution(i, 0);
        if(type==ALL) return Solution(0, 0, 1, 0);
        return Solution();
    }
    bool contains(LL x, LL y) const {
        if(type==ALL) return true;
        if(type==NONE) return false;
        if(type==SINGLE) return x==i && y==j;

        if(i>x || j>y) return false;
        LL dx=x-i, dy=y-j;
        if(!parallel(di, dj, dx, dy)) return false;
        LL u=dx+dy, v=di+dj;
        return u%v==0 && u/v>=0;
    }

    friend Solution intersect(Solution s1, Solution s2) {
        if(s1.type==NONE || s2.type==NONE) return Solution();
        if(s1.type==ALL) return s2;
        if(s2.type==ALL) return s1;
        if(s1.type==SINGLE) {
            if(s2.contains(s1.i, s1.j)) return s1;
            return Solution();
        }
        if(s2.type==SINGLE) {
            if(s1.contains(s2.i, s2.j)) return s2;
            return Solution();
        }
        // now MULTI
        if(parallel(s1.di, s1.dj, s2.di, s2.dj)) {
            LL dx=s1.i-s2.i, dy=s1.j-s2.j;
            if(!parallel(s1.di, s1.dj, dx, dy)) return Solution();
            Solution tmp;
            if(s1.di>0) {
                tmp=f(s1.i, s2.i, s1.di, s2.di);
            } else {
                tmp=f(s1.j, s2.j, s1.dj, s2.dj);
            }
            return Solution(s1.i+s1.di*tmp.i, s1.j+s1.dj*tmp.i, s1.di*tmp.di, s1.dj*tmp.di);
        } else {
            // must has one intersection
            auto make_line=[](LL x1, LL y1, LL x2, LL y2, LL &a, LL &b, LL &c) {
                a=y2-y1, b=x1-x2, c=-(a*x1+b*y1);
            };
            LL a1, b1, c1; make_line(s1.i, s1.j, s1.i+s1.di, s1.j+s1.dj, a1, b1, c1);
            LL a2, b2, c2; make_line(s2.i, s2.j, s2.i+s2.di, s2.j+s2.dj, a2, b2, c2);
            LL t=a1*b2-a2*b1, x=b1*c2-c1*b2, y=c1*a2-a1*c2;
            _debug("    intersect: multi, not parallel - t=%lld,x=%lld,y=%lld\n",t,x,y);
            assert(t!=0);
            if(x%t!=0 || y%t!=0) return Solution();
            x/=t, y/=t;
            _debug("    intersect: x=%lld y=%lld\n",x,y);
            if(s1.contains(x, y) && s2.contains(x, y))
                return Solution(x, y);
            return Solution();
        }
    }
}; //}}}

// (a1,b1), (a2,b2) -> (i,j) s.t. a1+b1*i = a2+b2*j
Solution f(LL a1, LL a2, LL b1, LL b2) { //{{{
    _debug("    f (%lld %lld) (%lld %lld)\n", a1,b1,a2,b2);
    if(b1==0 && b2==0) return Solution(a1==a2);
    if(b1==0) {
        if((a1-a2)%b2!=0 || (a1-a2)/b2<0) 
            return Solution();
        return Solution(0, (a1-a2)/b2, 1, 0);
    }
    if(b2==0) {
        if((a2-a1)%b1!=0 || (a2-a1)/b1<0)
            return Solution();
        return Solution((a2-a1)/b1, 0, 0, 1);
    }

    // now a1 a2 >= 0, b1 b2 >= 1
    LL i0, j0, g=ext_gcd(b1, b2, i0, j0); j0=-j0;
    if((a2-a1)%g!=0)
        return Solution();
    LL d=(a2-a1)/g; i0*=d, j0*=d;
    // now a1+b1*i0 = a2+b2*j0
    LL di=b2/g, dj=b1/g; // (i,j)+k(di,dj) is still solution

    LL t;
    t=max((-i0-1)/di, (-j0-1)/dj)+1;
    if(t>0) i0+=t*di, j0+=t*dj;
    t=min(i0/di, j0/dj); 
    if(t>0) i0-=t*di, j0-=t*dj;

    return Solution(i0, j0, di, dj);
} //}}}

// (a1,b1), (a2,b2) -> (i,j) s.t. a1*b1^i = a2*b2^j
Solution go(LL a1, LL a2, LL b1, LL b2) { //{{{
    _debug("go (%lld %lld) (%lld %lld)\n", a1,b1,a2,b2);
    auto factorize=[](LL n) {
        VL vec;
        for(LL x=2; x*x<=n; ++x)
            if(n%x==0) {
                vec.pb(x);
                while(n%x==0) n/=x;
            }
        if(n>1) vec.pb(n);
        return vec;
    };
    auto to_vec=[](const VL &ps, LL n) {
        VL vec;
        for(LL p: ps) {
            LL cur=0; 
            while(n%p==0) ++cur, n/=p;
            vec.pb(cur);
        }
        return vec;
    };

    VL primes, tmp;
    tmp=factorize(a1); primes.insert(primes.end(), all(tmp));
    tmp=factorize(a2); primes.insert(primes.end(), all(tmp));
    tmp=factorize(b1); primes.insert(primes.end(), all(tmp));
    tmp=factorize(b2); primes.insert(primes.end(), all(tmp));
    sort(all(primes)); 
    primes.erase(unique(all(primes)), primes.end());

    VL x1=to_vec(primes, a1);
    VL x2=to_vec(primes, a2);
    VL y1=to_vec(primes, b1);
    VL y2=to_vec(primes, b2);
    Solution sol(true);
    repn(i, primes.size()) {
        _debug("  f_begin prime=%lld\n",primes[i]);
        Solution tmp=f(x1[i], x2[i], y1[i], y2[i]);
        _debug("  f_end tmp=(%d,%lld,%lld,%lld,%lld)\n",tmp.type,tmp.i,tmp.j,tmp.di,tmp.dj);
        sol=intersect(sol, tmp);
        _debug("  intersect_end sol=(%d,%lld,%lld,%lld,%lld)\n",sol.type,sol.i,sol.j,sol.di,sol.dj);
    }
    _debug("go_end sol=(%d,%lld,%lld,%lld,%lld)\n",sol.type,sol.i,sol.j,sol.di,sol.dj);
    return sol;
} //}}}

LL solve(VPI as) { //{{{
    if(as.size()==1) return as[0].fi;

    _debug("solve #1\n");

    Solution sol(true); // all
    for(PII a: as) {
        Solution tmp=go(as[0].fi, a.fi, as[0].se, a.se).proj();
        sol=intersect(sol, tmp);
    }

    _debug("solve #2\n");

    LL k=0;
    if(sol.type==Solution::NONE)
        return -1;
    if(sol.type==Solution::ALL) k=0;
        else k=sol.i;

    auto pow=[](LL a, LL b) {
        LL c=1;
        for(; b>0; b>>=1, a=a*a%MOD)
            if(b&1) c=c*a%MOD;
        return c;
    };
    LL ans=as[0].fi*pow(as[0].se, k)%MOD;
    return ans;
} //}}}

int main() {
    int n; scanf("%d", &n);
    VPI as(n); for(PII &p: as) scanf("%d%d", &p.fi,&p.se);
    LL ans=solve(as);
    printf("%d\n", (int)ans);
    return 0;
}
