#include <algorithm>
#include <cassert>
#include <queue>
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

const LL INF=1LL<<60;

struct Mat {
    vector<VL> a;
    Mat(int n) { a.resize(n, VL(n, -INF)); }
    friend Mat operator*(const Mat& a, const Mat& b) {
        assert(sz(a.a)==sz(b.a));
        const int n=sz(a.a);
        Mat c(n);
        repn(i, n) repn(j, n) {
            repn(k, n) setmax(c.a[i][j], a.a[i][k]+b.a[k][j]);
        }
        return c;
    }
    friend Mat pow(Mat a, LL b) {
        const int n=sz(a.a);
        Mat c(n); repn(i, n) c.a[i][i]=0;
        for(; b>0; b>>=1, a=a*a)
            if(b&1) c=c*a;
        return c;
    }
};

Mat make(int n, const VI& val, const VS& str) {
    static int tr[222][26], v[222];
    fillchar(tr, 0); fillchar(v, 0);
    int num=1;
    repn(i, n) {
        int x=1;
        for(char ch: str[i]) {
            const int c=int(ch-'a');
            if(tr[x][c]==0) tr[x][c]=++num;
            x=tr[x][c];
        }
        v[x]+=val[i];
    }

    /*
    printf("num=%d\n", num);
    rep(i, 1, num) {
        printf("v[%d]=%d, trans:", i,v[i]);
        repn(c, 26) if(tr[i][c]) printf(" (%d)->%d", c,tr[i][c]);
        printf("\n");
    }
    //*/


    static int suffix[222]; fillchar(suffix, 0);
    static int que[222]; int ss=0, tt=0;
    suffix[1]=1;
    repn(c, 26) if(tr[1][c]==0) {
        tr[1][c]=1;
    } else {
        suffix[tr[1][c]]=1; que[++tt]=tr[1][c];
    }
    while(ss<tt) {
        const int x=que[++ss];
        v[x]+=v[suffix[x]];
        repn(c, 26) if(tr[x][c]==0) {
            tr[x][c]=tr[suffix[x]][c];
        } else {
            int y=tr[x][c];
            suffix[y]=tr[suffix[x]][c];
            que[++tt]=y;
        }
    }

    /*
    rep(i, 1, num) {
        printf("trans[%d]:", i);
        repn(c, 26) if(tr[i][c]!=1) printf(" (%d)->%d", c,tr[i][c]);
        printf("\n");
    }
    //*/

    Mat trans(num); repn(i, num) trans.a[i][i]=0;
    rep(j, 1, num) repn(c, 26) {
        int i=tr[j][c];
        trans.a[i-1][j-1]=v[i];
    }

    /*
    repn(i, num) {
        repn(j, num) printf("%lld ", trans.a[i][j]); printf("\n");
    }
    */

    return trans;
}

int main() {
    int n; LL l; cin>>n>>l;
    VI val(n); for(auto& v: val) cin>>v;
    VS str(n); for(auto& s: str) cin>>s;

    Mat trans=make(n, val, str);
    Mat z=pow(trans, l);
    /*
    repn(i, sz(z.a)) {
        repn(j, sz(z.a)) printf("%lld ", z.a[i][j]); printf("\n");
    }
    */
    LL ans=0;
    repn(i, sz(z.a)) setmax(ans,z.a[i][0]);
    cout<<ans<<endl;

    return 0;
}
