#include <algorithm>
#include <map>
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

struct Point {
    int x, y, z;
    void read() { scanf("%d%d%d", &x,&y,&z); }
    bool operator<(const Point& p) const {
        if(x!=p.x) return x<p.x;
        if(y!=p.y) return y<p.y;
        if(z!=p.z) return z<p.z;
        return false;
    }
};

bool solve(vector<pair<Point, Point>> as) {
    vector<VI> es;
    map<Point, int> ids;
    const auto id=[&](Point p) {
        if(ids.count(p)) {
            return ids[p];
        } else {
            int i=sz(es);
            es.pb(VI());
            return ids[p]=i;
        }
    };
    for(const auto& p: as) {
        int a=id(p.fi), b=id(p.se);
        if(a!=b) {
            //printf("%d %d\n",a,b);
            es[a].pb(b), es[b].pb(a);
        }
    }

    VI vis(sz(es), 0);
    bool found=false;
    const function<void(int, int)> dfs=[&](int x, int pre) {
        //printf("dfs %d\n",x);
        vis[x]=-1;
        for(int y: es[x]) if(y!=pre) {
            //printf("meet %d %d\n", x,y);
            if(vis[y]<0) found=true;
            if(vis[y]==0) dfs(y, x);
        }
        vis[x]=1;
    };
    repn(i, sz(es)) if(vis[i]==0) dfs(i, -1);
    return found;
}

int main() {
    int n; scanf("%d", &n);
    vector<pair<Point, Point>> as(n);
    repn(i, n) {
        as[i].fi.read(), as[i].se.read();
    }

    if(solve(as)) {
        printf("True closed chains\n");
    } else {
        printf("No true closed chains\n");
    }
    for(auto& a: as) {
        a.fi.z=a.se.z=0;
    }
    if(solve(as)) {
        printf("Floor closed chains\n");
    } else {
        printf("No floor closed chains\n");
    }
    return 0;
}
