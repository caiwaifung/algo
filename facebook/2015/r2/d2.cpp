// 3:02 - 3:42 - wa sample
//      - 3:52 - pass sample - ac
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

const int MAXN=1000010;
const int MAXM=1000010;
const LL MOD=LL(1e9);

LL S[MAXN], O[MAXM], A[MAXM], B[MAXM], C[MAXM], D[MAXM];
int n, m;

void read_input() {
    auto get=[](LL a[], int num, LL p, LL q) {
        LL x, y, z;
        cin>>a[1]>>a[2]>>x>>y>>z;
        rep(i, 3, num) {
            a[i]=(a[i-2]*x+a[i-1]*y+z)%p+q;
        }
    };
    cin>>n>>m;
    get(S, n, MOD, 0);
    get(O, m, 4, 1);
    get(A, m, n, 1);
    get(B, m, n, 1);
    get(C, m, MOD, 0);
    get(D, m, MOD, 0);
}

void add(LL& x, LL y) { (x+=y)%=MOD; }
LL val(LL v, LL d, LL num) {
    LL x=v+v+d*(num-1), y=num;
    if(x%2==0) x/=2; else y/=2;
    x%=MOD, y%=MOD;
    return x*y%MOD;
}

struct Delta {
    bool a; LL av; // reset to av
    bool b; LL bv, bd; // add {bv, bv+bd, bv+bd*2, ...}
    Delta() { clear(); }
    void push(const Delta& d) {
        if(d.a) {
            clear_a(), clear_b();
            a=true, av=d.av;
        }
        if(d.b) {
            b=true, add(bv, d.bv), add(bd, d.bd);
        }
    }
    Delta right(int offset) {
        Delta copy=*this;
        add(copy.bv, bd*offset);
        return copy;
    }
    void clear_a() { a=false, av=0; }
    void clear_b() { b=false, bv=bd=0; }
    void clear() { clear_a(), clear_b(); }
};

struct Value {
    LL s, so1, so2, n;
    Value() { s=so1=so2=n=0; }
    void push(const Delta& d) {
        LL n1=(n+1)/2, n2=n-n1;
        if(d.a) {
            s=d.av*n%MOD;
            if(d.av%2!=0) so1=n1, so2=n2;
                else so1=so2=0;
        }
        if(d.b) {
            add(s, val(d.bv, d.bd, n));
            if(d.bd%2==0) {
                if(d.bv%2!=0) so1=n1-so1, so2=n2-so2;
            } else {
                if(d.bv%2!=0) so1=n1-so1;
                    else so2=n2-so2;
            }
        }
    }
    Value operator +(const Value& b) {
        Value r;
        r.s=(s+b.s)%MOD;
        r.n=(n+b.n)%MOD;
        if(n%2==0) {
            r.so1=(so1+b.so1)%MOD;
            r.so2=(so2+b.so2)%MOD;
        } else {
            r.so1=(so1+b.so2)%MOD;
            r.so2=(so2+b.so1)%MOD;
        }
        return r;
    }
};

struct Node {
    Delta d;
    Value v;
    void push(const Delta& delta) {
        v.push(delta);
        d.push(delta);
    }
} tr[MAXN*4];

void init(int x, int s, int t) {
    tr[x].d.clear();
    if(s==t) {
        tr[x].v.s=S[s];
        tr[x].v.so1=S[s]%2;
        tr[x].v.so2=0;
        tr[x].v.n=1;
    } else {
        int mid=(s+t)/2;
        init(x*2, s, mid);
        init(x*2+1, mid+1, t);
        tr[x].v=tr[x*2].v+tr[x*2+1].v;
    }
}

Value visit(int x, int s, int t, int st, int en, Delta d) {
    if(st<=s && t<=en) {
        tr[x].push(d.right(s-st));
        return tr[x].v;
    }
    int mid=(s+t)/2;
    tr[x*2].push(tr[x].d);
    tr[x*2+1].push(tr[x].d.right(mid-s+1));
    tr[x].d.clear();

    Value ans; 
    if(st<=mid) ans=ans+visit(x*2, s, mid, st, en, d);
    if(mid<en) ans=ans+visit(x*2+1, mid+1, t, st, en, d);
    tr[x].v=tr[x*2].v+tr[x*2+1].v;
    return ans;
}

int solve() {
    init(1, 1, n);

    auto _sum=[](int l, int r) -> LL {
        Value value=visit(1, 1, n, l, r, Delta());
        return value.s;
    };
    auto _so=[](int l, int r) -> LL {
        Value value=visit(1, 1, n, l, r, Delta());
        return value.so1+value.so2;
    };
    auto _add=[](int l, int r, LL v, LL d) -> LL {
        Delta delta; delta.b=true, add(delta.bv,v), add(delta.bd,d);
        visit(1, 1, n, l, r, delta);
        return val(v, d, r-l+1);
    };
    auto _reset=[_sum](int l, int r, LL v) -> LL {
        LL ans=_sum(l, r); add(ans, (r-l+1)*v);
        Delta delta; delta.a=true, delta.av=v;
        visit(1, 1, n, l, r, delta);
        return ans;
    };

    LL ans=0;
    rep(i, 1, m) {
        int l=int(A[i]), r=l+int(B[i])-1;
        if(O[i]==1) {
            if(r<=n) {
                add(ans, _add(l, r, C[i], D[i]));
            } else {
                add(ans, _add(l, n, C[i], D[i]));
                add(ans, _add(1, r-n, (C[i]+D[i]*(n-l+1))%MOD, D[i]));
            }
        } else if(O[i]==2) {
            if(r<=n) {
                add(ans, _reset(l, r, C[i]));
            } else {
                add(ans, _reset(l, n, C[i]));
                add(ans, _reset(1, r-n, C[i]));
            }
        } else if(O[i]==3) {
            if(r<=n) {
                add(ans, _sum(l, r));
            } else {
                add(ans, _sum(l, n));
                add(ans, _sum(1, r-n));
            }
        } else if(O[i]==4) {
            if(r<=n) {
                add(ans, _so(l, r));
            } else {
                add(ans, _so(l, n));
                add(ans, _so(1, r-n));
            }
        }
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
