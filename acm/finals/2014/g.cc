// 11:10 - 11:34 - wa
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

VI find_candidates(int n, const vector<VI>& d) {
    VPI f(n, mp(-1, 0));
    const function<PII(int)> get=[&](int i) {
        if(f[i].fi<0) return mp(i, 0);
        auto r=get(f[i].fi);
        r.se^=f[i].se;
        return f[i]=r;
    };
    vector<pair<int, PII>> es;
    repn(i, n) replr(j, i+1, n) es.pb(mp(d[i][j], mp(i, j)));
    sort(all(es));
    reverse(all(es));
    VI ans;
    for(const auto& e: es) {
        int x=e.se.fi, y=e.se.se;
        PII fx=get(x), fy=get(y);
        if(fx.fi!=fy.fi) {
            f[fx.fi]=mp(fy.fi, fx.se^fy.se^1);
            ans.pb(e.fi);
        }
    }
    int tmp=0;
    repn(i, n) repn(j, n) {
        if(get(i).se==get(j).se) {
            setmax(tmp, d[i][j]);
        }
    }
    ans.pb(tmp);
    return ans;
}

bool check(int n, const vector<VI>& d, int vx, int vy) {
    vector<VI> es(n*2);
    repn(i, n) replr(j, i+1, n) {
        if(d[i][j]>vx) {
            es[i].pb(j+n);
            es[j].pb(i+n);
        }
        if(d[i][j]>vy) {
            es[i+n].pb(j);
            es[j+n].pb(i);
        }
    }
    VI belong(n*2, -1), dfn(n*2), low(n*2), stack;
    int num=0, cur=0;
    const function<void(int)> dfs=[&](int x) {
        dfn[x]=low[x]=cur++;
        stack.pb(x);
        belong[x]=-2;
        for(int y: es[x]) {
            if(belong[y]==-1) {
                dfs(y);
                setmin(low[x], low[y]);
            } else if(belong[y]==-2) {
                setmin(low[x], dfn[y]);
            }
        }
        if(dfn[x]==low[x]) {
            int last=-1;
            while(last!=x) {
                last=stack.back();
                stack.pop_back();
                belong[last]=num;
            }
            ++num;
        }
    };
    repn(i, n*2) if(belong[i]==-1) dfs(i);
    repn(i, n) if(belong[i]==belong[i+n]) return false;
    return true;
}

int main() {
    int n;
    scanf("%d", &n);
    vector<VI> d(n, VI(n, 0));
    repn(i, n) replr(j, i+1, n) {
        scanf("%d", &d[i][j]);
        d[j][i]=d[i][j];
    }
    VI candidates=find_candidates(n, d);
    int ans=int(2e9);
    for(int x: candidates) {
        int le=0, ri=int(1e9);
        while(le<ri) {
            int mid=(le+ri)/2;
            if(check(n, d, x, mid)) {
                ri=mid;
            } else {
                le=mid+1;
            }
        }
        setmin(ans, x+le);
    }
    printf("%d\n", ans);
    return 0;
}
