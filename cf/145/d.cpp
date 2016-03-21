#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#define _ (int)
#define all(a) a.begin(), a.end()
#define rep(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define irep(i, a, b) for(int i=int(a); i>=int(b); --i)
#define repn(i, n) rep(i, 0, (n)-1)
#define irepn(i, n) irep(i, (n)-1, 0)
#define fillchar(a, x) memset(a, x, sizeof(a))
#define fi first
#define se second
#define pb push_back
#define mp std::make_pair
typedef long long LL;
typedef std::pair<LL,LL> PLL;
typedef std::pair<int,int> PII;
typedef std::pair<double,double> PDD;
typedef std::vector<LL> VL;
typedef std::vector<int> VI;
typedef std::vector<PII> VPI;
typedef std::vector<std::string> VS;
template<class T> bool setmax(T &_a, T _b) { if(_b>_a) { _a=_b; return true; } return false; }
template<class T> bool setmin(T &_a, T _b) { if(_b<_a) { _a=_b; return true; } return false; }
template<class T> T gcd(T _a, T _b) { return _b==0?_a:gcd(_b,_a%_b); }

const int N=100010;
const int L=1010;
const int K=1010;

int lp[L], lk[L];
int n, lcnt, kcnt;

int rank[K];
LL bonus[K];

LL solve(int m) {
    fillchar(rank, 0);
    static int h[L]; int hlen=0;
    irep(i, lcnt, 1) if(lp[i]<=m) {
        if(rank[lk[i]]>0) continue;
        h[++hlen]=i;
        rank[lk[i]]=hlen;
    }

    fillchar(bonus, 0);
    LL cur=0; int la=m;
    static PII s[L]; int slen=0;
    auto f=[](LL x) { return x*(x+1)/2; };
    rep(i, 1, lcnt) if(lp[i]>m && rank[lk[i]]>0) {
        cur+=f(lp[i]-la-1); la=lp[i];
        while(slen>0) {
            int j=s[slen].fi;
            if(rank[lk[j]]<rank[lk[i]]) break;
            bonus[lk[j]]+=LL(s[slen].se)*LL(lp[i]-lp[j]-1);
            --slen;
        }
        int z=slen==0?m:lp[s[slen].fi];
        bonus[lk[i]]+=lp[i]-z;
        s[++slen]=mp(i, lp[i]-z);
    }
    cur+=f(n-la);
    while(slen>0) {
        int j=s[slen].fi;
        bonus[lk[j]]+=LL(s[slen].se)*LL(n-lp[j]);
        --slen;
    }
    //printf("m=%d cur=%lld bonus=%lld\n",m,cur,bonus[1]);

    LL ans=0; la=0;
    irep(z, hlen, 1) {
        int i=h[z];
        //printf("m=%d i=%d cur=%lld lp-la=%d\n",m,i,cur,lp[i]-la);
        ans+=cur*LL(lp[i]-la);
        la=lp[i];
        cur+=bonus[lk[i]];
    }
        //printf("m=%d cur=%lld n-la=%d\n",m,cur,n-la);
    ans+=cur*(m-la);
    //printf("%lld\n",ans);
    return ans;
}

int main() {
    scanf("%d", &n); lcnt=kcnt=0;
    std::map<int, int> x_to_k;
    auto is_lucky=[](int x) {
        while(x>0) {
            if(x%10!=4 && x%10!=7) return false;
            x/=10;
        }
        return true;
    };
    rep(i, 1, n) {
        int x; scanf("%d", &x);
        if(is_lucky(x)) {
            lp[++lcnt]=i;
            if(x_to_k.count(x)==0) x_to_k[x]=++kcnt;
            lk[lcnt]=x_to_k[x];
        }
    }
    //rep(i, 1, lcnt) printf("lp[%d]=%d lk=%d\n",i,lp[i],lk[i]);

    LL ans=0;
    rep(i, 1, n-1) ans+=solve(i);
    std::cout<<ans<<std::endl;

    return 0;
}
