// 10:35
// 10:40 - 11:00 - pause
// 10:01pm - 10:25 - re sample
//         - 10:34 - wa sample
//         - 11:26 - pass sample - ac
// code: 45
// debug: 60
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

//{{{
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
template<class T> T absv(T _x) { return _x>0?_x:-_x; }
//}}}

const int N=1000100;
const int M=1000100;
const LL MOD=LL(1e9);

LL S[N], O[M], A[M], B[M], C[M], D[M];
int n, m;

void read_input() {
    cin>>n>>m;
    LL xs, ys, zs; cin>>S[1]>>S[2]>>xs>>ys>>zs;
    LL xo, yo, zo; cin>>O[1]>>O[2]>>xo>>yo>>zo;
    LL xa, ya, za; cin>>A[1]>>A[2]>>xa>>ya>>za;
    LL xb, yb, zb; cin>>B[1]>>B[2]>>xb>>yb>>zb;
    LL xc, yc, zc; cin>>C[1]>>C[2]>>xc>>yc>>zc;
    LL xd, yd, zd; cin>>D[1]>>D[2]>>xd>>yd>>zd;
    rep(i, 3, n) S[i]=(xs*S[i-2]+ys*S[i-1]+zs)%MOD;
    rep(i, 3, m) {
        O[i]=(xo*O[i-2]+yo*O[i-1]+zo)%4+1;
        A[i]=(xa*A[i-2]+ya*A[i-1]+za)%n+1;
        B[i]=(xb*B[i-2]+yb*B[i-1]+zb)%n+1;
        C[i]=(xc*C[i-2]+yc*C[i-1]+zc)%MOD;
        D[i]=(xd*D[i-2]+yd*D[i-1]+zd)%MOD;
    }
}

LL val(int l, int r, LL v, LL d) {
    LL num=r-l+1;
    LL x=(v+v+d*(num-1)), y=num;
    if(x%2==0) x/=2; else y/=2;
    return (x%MOD)*(y%MOD)%MOD;
}

struct Node {
    LL sum, so1, so2, bv, bd, bc;
} tr[N*4];

void update(int x, int s, int t) {
    int mid=(s+t)/2;
    tr[x].sum=(tr[x*2].sum+tr[x*2+1].sum)%MOD;
    if((mid-s+1)%2==0) {
        tr[x].so1=(tr[x*2].so1+tr[x*2+1].so1)%MOD;
        tr[x].so2=(tr[x*2].so2+tr[x*2+1].so2)%MOD;
    } else {
        tr[x].so1=(tr[x*2].so1+tr[x*2+1].so2)%MOD;
        tr[x].so2=(tr[x*2].so2+tr[x*2+1].so1)%MOD;
    }
}

void push1(int x, int s, int t, LL v, LL d) { // add v,v+d,...
    if(tr[x].bv<0) tr[x].bv=tr[x].bd=0;
    (tr[x].bv+=v)%=MOD, (tr[x].bd+=d)%=MOD;

    (tr[x].sum+=val(s, t, v, d))%=MOD;

    int n1=(t-s)/2+1, n2=(t-s+1)-n1;
    if(d%2==0) {
        if(v%2!=0) {
            tr[x].so1=n1-tr[x].so1;
            tr[x].so2=n2-tr[x].so2;
        }
    } else {
        if(v%2!=0) {
            tr[x].so1=n1-tr[x].so1;
        } else {
            tr[x].so2=n2-tr[x].so2;
        }
    }
}

void push2(int x, int s, int t, LL c) { // set to c
    tr[x].bc=c; tr[x].bv=tr[x].bd=-1;

    tr[x].sum=(t-s+1)*c%MOD;

    int n1=(t-s)/2+1, n2=(t-s+1)-n1;
    tr[x].so1=(c%2)*n1;
    tr[x].so2=(c%2)*n2;
}

void down(int x, int s, int t) {
    if(s==t) {
        tr[x].bv=tr[x].bd=tr[x].bc=-1;
        return;
    }
    int mid=(s+t)/2;
    if(tr[x].bc>=0) {
        push2(x*2, s, mid, tr[x].bc);
        push2(x*2+1, mid+1, t, tr[x].bc);
        tr[x].bc=-1;
    }
    if(tr[x].bv>=0) {
        push1(x*2, s, mid, tr[x].bv, tr[x].bd);
        push1(x*2+1, mid+1, t, (tr[x].bv+tr[x].bd*(mid-s+1))%MOD, tr[x].bd);
        tr[x].bv=tr[x].bd=-1;
    }
}

void init(int x, int s, int t) {
    tr[x].bv=tr[x].bd=tr[x].bc=-1;
    if(s==t) {
        tr[x].sum=S[s];
        tr[x].so1=S[s]%2, tr[x].so2=0;
        return;
    }
    int mid=(s+t)/2;
    init(x*2, s, mid);
    init(x*2+1, mid+1, t);
    update(x, s, t);
}

void add(int x, int s, int t, int st, int en, LL v, LL d) {
    down(x, s, t);
    if(st<=s && t<=en) {
        push1(x, s, t, (v+(s-st)*d)%MOD, d);
        return;
    }
    int mid=(s+t)/2;
    if(st<=mid) add(x*2, s, mid, st, en, v, d);
    if(mid<en) add(x*2+1, mid+1, t, st, en, v, d);
    update(x, s, t);
}

void reset(int x, int s, int t, int st, int en, LL c) {
    down(x, s, t);
    if(st<=s && t<=en) {
        push2(x, s, t, c);
        return;
    }
    int mid=(s+t)/2;
    if(st<=mid) reset(x*2, s, mid, st, en, c);
    if(mid<en) reset(x*2+1, mid+1, t, st, en, c);
    update(x, s, t);
}

LL sum(int x, int s, int t, int st, int en) {
    if(st<=s && t<=en) {
        return tr[x].sum;
    }
    down(x, s, t);
    int mid=(s+t)/2;
    LL ans=0;
    if(st<=mid) (ans+=sum(x*2, s, mid, st, en))%=MOD;
    if(mid<en) (ans+=sum(x*2+1, mid+1, t, st, en))%=MOD;
    return ans;
}

LL so(int x, int s, int t, int st, int en) {
    if(st<=s && t<=en) {
        return (tr[x].so1+tr[x].so2)%MOD;
    }
    down(x, s, t);
    int mid=(s+t)/2;
    LL ans=0;
    if(st<=mid) (ans+=so(x*2, s, mid, st, en))%=MOD;
    if(mid<en) (ans+=so(x*2+1, mid+1, t, st, en))%=MOD;
    return ans;
}

LL add_arthmetic(int l, int r, LL v, LL d) {
    //{rep(i, l, r) add(1, 1, n, i, i, v+d*(i-l)%MOD, 0); return val(l,r,v,d);}

    add(1, 1, n, l, r, v, d);
    return val(l, r, v, d);
}

LL reset(int l, int r, LL v) {
    //{LL ans=0; rep(i, l, r) { (ans+=sum(1,1,n,i,i)+v)%=MOD; reset(1,1,n,i,i,v); } return ans; }

    LL ans=(sum(1, 1, n, l, r)+(r-l+1)*v)%MOD;
    reset(1, 1, n, l, r, v);
    return ans;
}

LL getsum(int l, int r) {
    //{LL ans=0; rep(i, l, r) { (ans+=sum(1,1,n,i,i))%=MOD; } return ans; }

    LL ans=sum(1, 1, n, l, r);
    return ans;
}

LL getso(int l, int r) {
    //{LL ans=0; rep(i, l, r) { (ans+=so(1,1,n,i,i))%=MOD; } return ans; }

    LL ans=so(1, 1, n, l, r);
    return ans;
}

int solve() {
    init(1, 1, n);
    LL ans=0;
    rep(i, 1, m) {
        if(O[i]==1) {
            int l=int(A[i]), r=l+int(B[i])-1;
            LL v=C[i], d=D[i];
            if(r<=n) {
                (ans+=add_arthmetic(l, r, v, d))%=MOD;
            } else {
                (ans+=add_arthmetic(l, n, v, d))%=MOD;
                LL v2=(v+(n-l+1)*d)%MOD;
                (ans+=add_arthmetic(1, r-n, v2, d))%=MOD;
            }
        } else if(O[i]==2) {
            int l=int(A[i]), r=l+int(B[i])-1;
            LL v=C[i];
            if(r<=n) {
                (ans+=reset(l, r, v))%=MOD;
            } else {
                (ans+=reset(l, n, v))%=MOD;
                (ans+=reset(1, r-n, v))%=MOD;
            }
        } else if(O[i]==3) {
            int l=int(A[i]), r=l+int(B[i])-1;
            if(r<=n) {
                (ans+=getsum(l, r))%=MOD;
            } else {
                (ans+=getsum(l, n))%=MOD;
                (ans+=getsum(1, r-n))%=MOD;
            }
        } else if(O[i]==4) {
            int l=int(A[i]), r=l+int(B[i])-1;
            if(r<=n) {
                (ans+=getso(l, r))%=MOD;
            } else {
                (ans+=getso(l, n))%=MOD;
                (ans+=getso(1, r-n))%=MOD;
            }
        }
        /*
        function<void(int,int,int)> check=[&check](int x, int s, int t) {
            assert(tr[x].so1>=0);
            assert(tr[x].so2>=0);
            assert(tr[x].sum>=0);
            if(s==t) return;
            check(x*2, s, (s+t)/2);
            check(x*2+1, (s+t)/2+1,t);
        };
        check(1, 1, n);
        */
    }
    return (int)ans;
}

int main() {
    freopen("/Users/fqw/Downloads/fox_socks.txt", "r", stdin); freopen("out.txt", "w", stdout);
    int csn; scanf("%d", &csn);
    rep(cs, 1, csn) { fprintf(stderr, "\033[0;31m### [%d/%d]\033[0m\n",cs,csn);
        read_input();
        int ans=solve();
        printf("Case #%d: %d\n", cs, ans);
    }
    return 0;
}
