#include <iostream>
#include <algorithm>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
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

const int MAXN=100010;
const int MAXLog=20;

VPI es[MAXN]; int val[MAXN];
LL d[MAXN]; int dep[MAXN];
int n;

int seq[MAXN*2], pos[MAXN], num;
PII rmq[MAXN*2][MAXLog];
int rlog[MAXN*2];

void dfs(int x, int fa) {
    seq[++num]=x, pos[x]=num;
    for(PII e: es[x]) if(e.fi!=fa) {
        d[e.fi]=d[x]+e.se;
        dep[e.fi]=dep[x]+1;
        dfs(e.fi, x);
        seq[++num]=x;
    }
}

void pre() {
    fillchar(dep, 0); 
    fillchar(d, 0); 
    num=0;
    dfs(1, 0);

    rep(i, 1, num) rmq[i][0]=mp(dep[seq[i]], seq[i]);
    repn(j, MAXLog-1)
        rep(i, 1, num-(1<<j))
            rmq[i][j+1]=min(rmq[i][j], rmq[i+(1<<j)][j]);

    fillchar(rlog, 0xff);
    int la=0;
    repn(j, MAXLog) if((1<<j)<=num) rlog[1<<j]=j;
    repn(i, num) if(rlog[i]<0) rlog[i]=la; else la=rlog[i];
}

LL dis(int x, int y) {
    int i=pos[x], j=pos[y];
    if(i>j) swap(i, j);
    int l=rlog[j-i+1];
    PII r=min(rmq[i][l], rmq[j-(1<<l)+1][l]);
    int z=r.se;
    return d[x]+d[y]-d[z]*2;
}

int rt[MAXN]; 
PII fp[MAXN];
int get_rt(int x) {
    VI st;
    while(rt[x]!=0) 
        st.pb(x), x=rt[x];
    for(int y: st) rt[y]=x;
    return x;
}

void upt(PII &a, PII b) {
    LL da=dis(a.fi, a.se);
    LL db=dis(b.fi, b.se);
    if(db>da) a=b;
}

const LL BIT=1000000;
struct Num {
    LL a[10]; int n;

    void adjust() {
        repn(i, n) {
            a[i+1]+=a[i]/BIT;
            a[i]%=BIT;
        }
        while(a[n]>0) {
            a[n+1]+=a[n]/BIT;
            a[n]%=BIT;
            ++n;
        }
    }

    Num(LL x) {
        fillchar(a, 0);
        a[0]=x, n=1;
        adjust();
    }

    bool cmp(const Num &b) {
        if(n!=b.n) return n<b.n;
        irepn(i, n) if(a[i]!=b.a[i]) return a[i]<b.a[i];
        return false;
    }

    void add(const Num &b) {
        setmax(n, b.n);
        repn(i, b.n) a[i]+=b.a[i];
        adjust();
    }

    void mul(const Num &b) {
        Num c=*this;
        n=b.n+c.n-1;
        fillchar(a, 0);
        repn(i, b.n) repn(j, c.n)
            a[i+j]+=b.a[i]*c.a[j];
        adjust();
    }

    string print() {
        bool fi=true;
        string r="";
        irepn(i, n) {
            if(!fi) {
                for(LL b=BIT/10; a[i]<b; b/=10) r+="0";
            }
            if(a[i]>0) {
                char buf[99]; sprintf(buf, "%lld", a[i]);
                r+=string(buf);
            }
            fi=false;
        }
        return r;
    }
};

struct Num2 {
    LL x;
    Num2(LL n) : x(n) {}
    void add(Num2 n) { x+=n.x; }
    void mul(Num2 n) { x*=n.x; }
    string print() {
        char buf[99]; sprintf(buf, "%lld", x);
        return string(buf);
    }
    bool cmp(Num2 n) const { return x<n.x; }
};

#define Val Num

string solve() {
    fillchar(rt, 0);
    rep(i, 1, n) fp[i]=mp(i, i);
    VPI lst;
    rep(i, 1, n) lst.pb(mp(-val[i], i));
    sort(all(lst));

    Val ans(0);
    static bool vis[MAXN];
    fillchar(vis, false);
    for(PII cur: lst) {
        int x=cur.se; vis[x]=true;
        LL len=0;
        for(PII e: es[x]) {
            int y=e.fi; if(!vis[y]) continue;
            PII p=fp[get_rt(y)];
            LL curlen=max(dis(x, p.fi), dis(x, p.se));
            Val tmp(len);
            tmp.add(Val(curlen));
            tmp.mul(Val(val[x]));
            if(ans.cmp(tmp)) ans=tmp;
            setmax(len, curlen);

            PII q=fp[get_rt(x)], target=q;
            upt(target, p);
            upt(target, mp(p.fi, q.fi));
            upt(target, mp(p.fi, q.se));
            upt(target, mp(p.se, q.fi));
            upt(target, mp(p.se, q.se));

            rt[get_rt(y)]=get_rt(x);
            fp[get_rt(x)]=target;
        }
    }
    return ans.print();
}

int dfs2(int x, int fa, int v, int w) {
    setmin(v, val[x]);
    int ans=v*w;
    for(PII e: es[x]) if(e.fi!=fa) setmax(ans, dfs2(e.fi, x, v, w+e.se));
    return ans;
}

string solve2() {
    int ans=0;
    rep(i, 1, n) setmax(ans, dfs2(i, 0, 1<<30, 0));
    char b[99]; sprintf(b, "%d", ans);
    return string(b);
}

void check() {
    while(1) {
        n=5; rep(i, 1, n) val[i]=rand()%10+1;
        rep(i, 1, n) es[i].clear();
        rep(i, 2, n) {
            int j=rand()%(i-1)+1;
            int v=rand()%10+1;
            es[i].pb(mp(j, v));
            es[j].pb(mp(i, v));
            string ans1=solve2();
            pre();
            string ans2=solve();
            if(ans1==ans2) printf("ok. ans=%s\n", ans2.c_str());
            else {
                printf("error! %s %s\n",ans1.c_str(),ans2.c_str());
                rep(i, 1, n) printf("v[%d]=%d\n",i,val[i]);
                rep(i, 1, n) for(PII e: es[i]) printf("%d - %d : %d\n",i,e.fi,e.se);
                for(;;); 
            }
        }
    }
}

int main() {
    //check();
    int cs; scanf("%d", &cs);
    while(cs--) {
        scanf("%d", &n);
        rep(i, 1, n) scanf("%d", &val[i]);
        rep(i, 1, n) es[i].clear();
        rep(i, 1, n-1) {
            int u, v, w; scanf("%d%d%d", &u,&v,&w);
            es[u].pb(mp(v, w));
            es[v].pb(mp(u, w));
        }
        pre();
        cout<<solve()<<endl;
    }
    return 0;
}
