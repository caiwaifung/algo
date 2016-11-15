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

template<class T> class MincostMaxflow {
    struct Edge { int y; T w, c; Edge* oppo; };
    const int n_;
    vector<vector<unique_ptr<Edge>>> es_;
public:
    explicit MincostMaxflow(int n) : n_(n), es_(n) {}

    void add_edge(int x, int y, T w, T c) {
        Edge *e1, *e2;
        es_[x].emplace_back(e1=new Edge{y, w, c, nullptr});
        es_[y].emplace_back(e2=new Edge{x, 0, -c, nullptr});
        e1->oppo=e2, e2->oppo=e1;
    }

    // Returns (flow, cost).
    pair<T, T> compute(int s, int t) {
        pair<T, T> ans;
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
};

int main() {
    int n, k;
    scanf("%d%d", &n,&k);
    vector<VI> a(n+1, VI(n+1));
    repn(i, n+1) {
        replr(j, i+1, n+1) {
            scanf("%d", &a[i][j]);
        }
    }

    MincostMaxflow<int> net(n*2+3);
    int super=n*2, s=n*2+1, t=n*2+2;
    repn(i, n) net.add_edge(s, i, 1, 0);
    repn(i, n) replr(j, i+1, n) net.add_edge(i, n+j, 1, a[i+1][j+1]);
    net.add_edge(s, super, k, 0);
    repn(i, n) net.add_edge(super, n+i, 1, a[0][i+1]);
    repn(i, n) net.add_edge(n+i, t, 1, 0);
    const auto r=net.compute(s, t);
    assert(r.fi==n);
    printf("%d\n", r.se);

    return 0;
}
