#include <algorithm>
#include <unordered_map>
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
typedef vector<int> VI;
typedef vector<LL> VL;
typedef vector<bool> VB;
typedef vector<PII> VPI;
typedef vector<PDD> VPD;
typedef vector<string> VS;
template<class T, class S> ostream& operator<<(ostream& os, const pair<T, S>& v) { return os<<"("<<v.first<<", "<<v.second<<")"; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& v) { os<<"["; repn(i, sz(v)) { if(i) os<<", "; os<<v[i]; } return os<<"]"; }
template<class T> bool setmax(T &_a, T _b) { if(_b>_a) { _a=_b; return true; } return false; }
template<class T> bool setmin(T &_a, T _b) { if(_b<_a) { _a=_b; return true; } return false; }
template<class T> T gcd(T _a, T _b) { return _b==0?_a:gcd(_b,_a%_b); }

template<class T> struct CostNet {
    CostNet(int n, int s, int t) : n_(n), s_(s), t_(t), es_(n) {}
    void add_edge(int x, int y, T w, T c) { add_(x, y, w, c); }
    pair<T, T> compute() { return compute_(); }
private:  //{{{
    struct Edge { int y; T w, c; Edge* oppo; };
    const int n_, s_, t_;
    T w0_=0, c0_=0;
    vector<vector<unique_ptr<Edge>>> es_;

    void add_(int x, int y, T w, T c) {
        if(c>=0) {
            Edge *e1, *e2;
            es_[x].emplace_back(e1=new Edge{y, w, c, nullptr});
            es_[y].emplace_back(e2=new Edge{x, 0, -c, nullptr});
            e1->oppo=e2, e2->oppo=e1;
        } else {
            w0_+=w;
            c0_+=w*(-c);
            add_edge(s_, y, w, 0);
            add_edge(y, x, w, -c);
            add_edge(x, t_, w, 0);
        }
    }

    pair<T, T> compute_() {
        int s=s_, t=t_;
        pair<T, T> ans={-w0_, -c0_};
        while(1) {
            vector<T> dis(n_, numeric_limits<T>::max());
            vector<T> flow(n_);
            vector<Edge*> pre(n_);
            dis[s]=0;
            flow[s]=numeric_limits<T>::max();

            vector<bool> inside(n_, false);
            queue<int> que;
            inside[s]=true;
            que.push(s);
            while(!que.empty()) {
                const int x=que.front(); que.pop();
                for(const auto& e: es_[x]) {
                    if(e->w>0 && setmin(dis[e->y], dis[x]+e->c)) {
                        pre[e->y]=e.get();
                        flow[e->y]=min(flow[x], e->w);
                        if(!inside[e->y]) {
                            inside[e->y]=true;
                            que.push(e->y);
                        }
                    }
                }
                inside[x]=false;
            }
            if(dis[t]==numeric_limits<T>::max()) {
                return ans;
            }

            ans.fi+=flow[t], ans.se+=flow[t]*dis[t];
            for(int x=t; x!=s; x=pre[x]->oppo->y) {
                pre[x]->w-=flow[t];
                pre[x]->oppo->w+=flow[t];
            }
        }
        return ans;
    }
    // }}}
};

void solve(int cs) {
    int n, m; scanf("%d%d", &n,&m);
    vector<VI> sc(n, VI(m)), sr(n, VI(m));
    vector<VB> essential(n, VB(m));
    repn(i, n) repn(j, m-1) scanf("%d", &sc[i][j]);
    repn(i, n-1) repn(j, m) scanf("%d", &sr[i][j]);
    int en; scanf("%d", &en);
    repn(i, en) {
        int x, y; scanf("%d%d", &x,&y);
        --x, --y;
        essential[x][y]=true;
    }

    int s=n*m*2, t=s+1;
    CostNet<int> net(n*m*2+2, s, t);
    const auto id=[&](int i, int j, int k) {
        return (i*m+j)*2+k;
    };
    int need=0;
    repn(i, n) repn(j, m) {
        if((i+j)%2==0) {
            if(j+1<m) net.add_edge(id(i, j, 1), id(i, j+1, 0), 1, -sc[i][j]);
            if(i+1<n) net.add_edge(id(i+1, j, 1), id(i, j, 0), 1, -sr[i][j]);
        } else {
            if(j+1<m) net.add_edge(id(i, j+1, 1), id(i, j, 0), 1, -sc[i][j]);
            if(i+1<n) net.add_edge(id(i, j, 1), id(i+1, j, 0), 1, -sr[i][j]);
        }
        if(essential[i][j]) {
            net.add_edge(s, id(i, j, 1), 1, 0);
            net.add_edge(id(i, j, 0), t, 1, 0);
            ++need;
        } else {
            net.add_edge(id(i, j, 0), id(i, j, 1), 1, 0);
        }
    }
    const auto r=net.compute();
    printf("Case #%d: ", cs);
    if(r.fi!=need) {
        printf("Impossible\n");
    } else {
        printf("%d\n", -r.se);
    }
}

int main() {
    int cs; scanf("%d", &cs);
    repn(i, cs) {
        solve(i+1);
    }
    return 0;
}
