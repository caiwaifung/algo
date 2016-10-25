// 7:28 - 8:08 - wa
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

struct BipartiteGraph {
    const int n, m;
    vector<VI> es;

    BipartiteGraph(int _n, int _m) : n(_n), m(_m), es(n) { }

    void add_edge(int i, int j) { es[i].pb(j); }

    pair<VI, VI> independent_set() {
        VI mx(n, -1), my(m, -1);
        while(1) {
            vector<bool> vis(m, false);
            VI pre(n), src(n);
            queue<int> que;
            repn(i, n) if(mx[i]<0) {
                pre[i]=-1, src[i]=i;
                que.push(i);
            }
            bool found=false;
            while(!que.empty()) {
                const int i=que.front(); que.pop();
                if(mx[src[i]]>=0) continue;
                for(int j: es[i]) if(!vis[j]) {
                    vis[j]=true;
                    if(my[j]<0) {
                        found=true;
                        for(int x=i, y=j; x>=0; ) {
                            int x0=pre[x], y0=mx[x];
                            mx[x]=y, my[y]=x;
                            x=x0, y=y0;
                        }
                        break;
                    }
                    pre[my[j]]=i, src[my[j]]=src[i];
                    que.push(my[j]);
                }
            }
            if(!found) {
                VI l, r;
                repn(i, n) if(mx[i]<0 || vis[mx[i]]) {
                    l.pb(i);
                }
                repn(j, m) if(my[j]<0 || !vis[j]) {
                    r.pb(j);
                }
                return mp(l, r);
            }
        }
    }
};

int main() {
    int n, d; scanf("%d%d", &n,&d);
    VPI a(n);
    repn(i, n) scanf("%d%d", &a[i].fi,&a[i].se);
    d=d*d;
    vector<VI> dis(n, VI(n));
    vector<vector<VI>> det(n, vector<VI>(n, VI(n)));
    {
        const auto sqr_dis=[](const PII& p, const PII& q) {
            return (p.fi-q.fi)*(p.fi-q.fi) + (p.se-q.se)*(p.se-q.se);
        };
        const auto mult=[](const PII& p0, const PII& p1, const PII& p2) {
            return (p1.fi-p0.fi)*(p2.se-p0.se) - (p1.se-p0.se)*(p2.fi-p0.fi);
        };
        repn(i, n) repn(j, n) {
            dis[i][j]=sqr_dis(a[i], a[j]);
            repn(k, n) {
                det[i][j][k]=mult(a[i], a[j], a[k]);
            }
        }
    }


    VI ans={0};
    repn(i, n) replr(j, i+1, n) {
        const int d0=dis[i][j];
        if(d0>d) continue;
        vector<int> l, r;
        VI res={i, j};
        repn(k, n) if(k!=i && k!=j) {
            if(dis[i][k]<=d0 && dis[j][k]<=d0) {
                if(det[i][j][k]==0) {
                    res.pb(k);
                } else {
                    (det[i][j][k]<0?l:r).pb(k);
                }
            }
        }
        if(sz(l)>0 && sz(r)>0) {
            BipartiteGraph g(sz(l), sz(r));
            repn(u, sz(l)) repn(v, sz(r)) {
                if(dis[l[u]][r[v]]>d0) {
                    g.add_edge(u, v);
                }
            }
            const auto& is=g.independent_set();
            for(int k: is.fi) res.pb(l[k]);
            for(int k: is.se) res.pb(r[k]);
        } else {
            for(int k: l) res.pb(k);
            for(int k: r) res.pb(k);
        }
        //printf("%d %d: %d %d %d\n",i,j,res,sz(l),sz(r));
        if(sz(res)>sz(ans)) ans=res;
    }
    printf("%d\n", sz(ans));
    for(int i: ans) printf("%d ", i+1);
    printf("\n");

    return 0;
}
