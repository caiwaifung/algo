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

class Maxflow {
    typedef int T;
    struct Edge { int y; T w; Edge* oppo; };
    const int n_, super_s_, super_t_;
    T super_total_=0;
    vector<vector<unique_ptr<Edge>>> es_;

public:
    explicit Maxflow(int n)
        : n_(n+2), super_s_(n), super_t_(n+1), es_(n_) {}

    void* add_edge(int x, int y, T w) {
        Edge *e1, *e2;
        es_[x].emplace_back(e1=new Edge{y, w, nullptr});
        es_[y].emplace_back(e2=new Edge{x, 0, nullptr});
        e1->oppo=e2, e2->oppo=e1;
        return e1;
    }
    void* add_edge_with_lower_limit(int x, int y, T w, T lb) {
        if(lb>0) {
            add_edge(super_s_, y, lb);
            add_edge(x, super_t_, lb);
            super_total_+=lb;
        }
        return add_edge(x, y, w-lb);
    }

    // Returns -1 if no solution.
    T compute_maxflow(int s, int t) {
        if(super_total_>0) {
            add_edge(t, s, numeric_limits<T>::max());
            LL r=0, tmp;
            while((tmp=augment(super_s_, super_t_))>0) r+=tmp;
            if(r!=super_total_) return -1;
        }
        T ans=0, tmp;
        while((tmp=augment(s, t))>0) ans+=tmp;
        return ans;
    }

    T flow(void* e) const { return static_cast<Edge*>(e)->oppo->w; }

private:
    T augment(int s, int t) {
        VI dis(n_); dis[s]=1; 
        queue<int> que; que.push(s);
        while(!que.empty()) {
            int x=que.front(); que.pop();
            for(const auto& e: es_[x]) {
                if(e->w>0 && dis[e->y]==0) {
                    dis[e->y]=dis[x]+1;
                    que.push(e->y);
                }
            }
        }
        if(dis[t]==0) return 0;

        vector<size_t> ce(n_);
        const function<T(int,T)> dfs=[&](int x, T rest) {
            if(x==t) return rest;
            T r=0;
            for(size_t& i=ce[x]; i<es_[x].size(); ++i) {
                const auto& e=es_[x][i];
                if(e->w>0 && dis[e->y]>dis[x]) {
                    T cur=dfs(e->y, min(e->w, rest));
                    e->w-=cur, e->oppo->w+=cur;
                    r+=cur, rest-=cur;
                    if(rest==0) break;
                }
            }
            return r;
        };
        return dfs(s, numeric_limits<T>::max());
    }
};

int main() {
    int n, m, p; scanf("%d%d%d", &n,&m,&p);
    Maxflow net(n+m+p+2);
    int s=n+m+p, t=s+1;
    repn(i, n) {
        int k; scanf("%d", &k);
        while(k--) {
            int j; scanf("%d", &j);
            --j;
            net.add_edge(i, n+j, 1);
        }
    }
    vector<bool> used(m, false);
    repn(i, p) {
        int k; scanf("%d", &k);
        while(k--) {
            int j; scanf("%d", &j);
            --j;
            used[j]=true;
            net.add_edge(n+j, n+m+i, 1);
        }
        int w; scanf("%d", &w);
        net.add_edge(n+m+i, t, w);
    }
    repn(i, n) net.add_edge(s, i, 1);
    repn(j, m) if(!used[j]) net.add_edge(n+j, t, 1);
    int ans=net.compute_maxflow(s, t);
    printf("%d\n", ans);
    return 0;
}
