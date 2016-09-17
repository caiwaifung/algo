// 8:40 - 9:35
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

struct Hashes {
    const int n;
    VL h1, h2, pow;
    Hashes(const string& s) : n(sz(s)) {
        h1.resize(n+1);
        repn(i, n) {
            h1[i+1]=(h1[i]*kP+int(s[i]))%kM;
        }
        h2.resize(n+1);
        irepn(i, n) {
            h2[i]=(h2[i+1]*kP+int(s[i]))%kM;
        }
        pow.resize(n+1);
        pow[0]=1;
        repn(i, n) pow[i+1]=pow[i]*kP%kM;
    }
    bool is_mirror(int i1, int j1, int i2, int j2) const {
        assert(j1-i1==j2-i2);
        LL v1=((h1[j1]-h1[i1]*pow[j1-i1])%kM+kM)%kM;
        LL v2=((h2[i2]-h2[j2]*pow[j2-i2])%kM+kM)%kM;
        return v1==v2;
    }
private:
    static constexpr LL kP=107;
    static constexpr LL kM=LL(1e9)+7;
};

VI compute_palin(const string& s) {
    VI r(sz(s));
    int p=-1, pr=-1;
    repn(i, sz(s)) {
        if(pr>=i) r[i]=min(pr-i, r[p*2-i]);
        while(i-r[i]>0 && i+r[i]<sz(s)-1 && s[i-r[i]-1]==s[i+r[i]+1]) {
            ++r[i];
        }
        if(r[i]>pr-p) {
            p=i, pr=i+r[i];
        }
    }
    return r;
}

struct RMQ {
    vector<VPI> c;
    VI log;

    RMQ(const VI& a) {
        const int n=sz(a);
        constexpr int kLog=20;
        c.resize(n, VPI(kLog));
        repn(i, n) {
            c[i][0]=mp(a[i], i);
        }
        replr(j, 1, kLog) {
            repn(i, n-(1<<j)+1) {
                c[i][j]=max(c[i][j-1], c[i+(1<<(j-1))][j-1]);
            }
        }
        log.resize(n+1);
        repn(j, kLog) {
            replr(i, 1<<j, min(n+1,1<<(j+1))) {
                log[i]=j;
            }
        }
    }
    PII getmax(int l, int r) {
        int j=log[r-l];
        return max(c[l][j], c[r-(1<<j)][j]);
    }
};

int main() {
    string s; cin>>s;
    const int n=sz(s);

    Hashes hashes(s);
    //printf("#1\n");
    VI palin=compute_palin(s);
    //printf("#2\n");
    RMQ rmq(palin);

    //printf("#3\n");

    const auto find_palin=[&](int l, int r) {
        int le=0, ri=(r-l-1)/2;
        while(le<ri) {
            int mid=(le+ri+1)/2;
            if(rmq.getmax(l+mid, r-mid).fi>=mid) {
                le=mid;
            } else {
                ri=mid-1;
            }
        }
        int i=rmq.getmax(l+le, r-le).se;
        return PII(i-le, i+le+1);
    };
    pair<int, VPI> ans;
    {
        auto p=find_palin(0, n);
        ans=mp(p.se-p.fi, VPI{p});
    }
    int i=0;
    irepn(j, n) {
        const int len=n-j;
        bool ok=false;
        while(1) {
            if(i+len>=j) break;
            //printf("checking %d %d %d %d\n",i+1,i+len,j+1,n);
            if(hashes.is_mirror(i, i+len, j, n)) {
                ok=true; break;
            }
            ++i;
        }
        if(!ok) break;
        //printf("i=%d j=%d len=%d\n", i,j,len);
        PII p=find_palin(i+len, j);
        setmax(ans, mp(len*2+p.se-p.fi, VPI{{i,i+len}, p, {j,n}}));
    }
    cout<<sz(ans.se)<<endl;
    for(const auto& p: ans.se) {
        cout<<p.fi+1<<" "<<p.se-p.fi<<endl;
    }

    return 0;
}
