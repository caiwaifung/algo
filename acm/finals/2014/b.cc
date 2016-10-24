// 7:36 - 8:04
//      - 8:42 - ac
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
typedef vector<double> VD;
typedef vector<string> VS;
template<class T, class S> ostream& operator<<(ostream& os, const pair<T, S>& v) { return os<<"("<<v.first<<", "<<v.second<<")"; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& v) { os<<"["; repn(i, sz(v)) { if(i) os<<", "; os<<v[i]; } return os<<"]"; }
template<class T> bool setmax(T &_a, T _b) { if(_b>_a) { _a=_b; return true; } return false; }
template<class T> bool setmin(T &_a, T _b) { if(_b<_a) { _a=_b; return true; } return false; }
template<class T> T gcd(T _a, T _b) { return _b==0?_a:gcd(_b,_a%_b); }

const LL kInf=1LL<<60;

struct DiscreteDish {
    LL w, t, dt;
};

VL solve_single(const VL& f, LL t, LL dt) {
    const int m=sz(f)-1;
    if(dt==0) {
        VL g=f;
        LL cur=-kInf;
        rep(i, 0, m) {
            if(cur>-kInf) cur+=t;
            g[i]=cur=max(g[i], cur);
        }
        return g;
    }

    VL benefit(m+1);
    rep(i, 1, m) benefit[i]=benefit[i-1]+t-dt*(i-1);
    const auto lose_time=[&](int i, int j) {
        // when option i lose to j
        assert(i<j);
        LL d=f[i]+benefit[j-i]-f[j], rate=(j-i)*dt;
        if(d<=0) return j;
        return (int)min(LL(m+1), j+(d+rate-1)/rate);
    };

    VL g(m+1, -kInf);
    deque<int> que;
    rep(i, 0, m) {
        if(f[i]>-kInf) {
            while(sz(que)>=2) {
                int j=que.back(); que.pop_back();
                if(lose_time(que.back(), j)<lose_time(j, i)) {
                    que.push_back(j);
                    break;
                }
            }
            que.push_back(i);
        }
        while(sz(que)>=2) {
            int j=que.front(); que.pop_front();
            if(lose_time(j, que.front())>i) {
                que.push_front(j);
                break;
            }
        }
        if(!que.empty()) {
            int j=que.front();
            g[i]=f[j]+benefit[i-j];
        }
    }
    return g;
}

VL solve_discrete(const vector<DiscreteDish>& a, int m) {
    VL f(m+1, -kInf);
    f[0]=0;
    for(const auto& dish: a) {
        repn(p, dish.w) {
            VL g;
            for(int i=p; i<=m; i+=dish.w) g.pb(f[i]);
            g=solve_single(g, dish.t, dish.dt);
            repn(k, sz(g)) f[p+k*dish.w]=g[k];
        }
    }
    return f;
}

struct ContinuousDish {
    double t, dt;
    bool operator<(const ContinuousDish& d) const {
        return t<d.t;
    }
};

VD solve_continuous(vector<ContinuousDish> a, int m) {
    VD f(m+1, 0);
    sort(all(a));
    rep(i, 1, m) {
        double demand=1, value=0;
        while(demand>0) {
            double cur=demand;
            if(sz(a)>1 && a.back().dt>0) {
                setmin(cur, (a.back().t-a[sz(a)-2].t)/a.back().dt);
            }
            value+=cur*(a.back().t*2-a.back().dt*cur)/2;
            demand-=cur;
            a.back().t-=a.back().dt*cur;
            while(sz(a)>1 && a.back().t<a[sz(a)-2].t+1e-9) {
                if(a[sz(a)-2].dt>0 && a.back().dt>0) {
                    a[sz(a)-2].dt=1/(1/a.back().dt+1/a[sz(a)-2].dt);
                } else {
                    a[sz(a)-2].dt=0;
                }
                a.pop_back();
            }
        }
        f[i]=f[i-1]+value;
    }
    return f;
}

int main() {
    int n, m; scanf("%d%d", &n,&m);
    vector<DiscreteDish> ds;
    vector<ContinuousDish> cs;
    repn(i, n) {
        char type[5]; scanf("%s", type);
        if(type[0]=='D') {
            int w, t, dt; scanf("%d%d%d", &w,&t,&dt);
            if(w<=m) {
                ds.pb(DiscreteDish{(LL)w, (LL)t, (LL)dt});
            }
        } else {
            int t, dt; scanf("%d%d", &t,&dt);
            cs.pb(ContinuousDish{(double)t, (double)dt});
        }
    }

    VL fd=solve_discrete(ds, m);
    if(cs.empty()) {
        if(fd[m]==-kInf) {
            printf("impossible\n");
        } else {
            printf("%lld\n", fd[m]);
        }
    } else {
        VD fc=solve_continuous(cs, m);
        double ans=-1e60;
        rep(i, 0, m) setmax(ans, fd[i]+fc[m-i]);
        printf("%.9lf\n", ans);
    }

    return 0;
}
