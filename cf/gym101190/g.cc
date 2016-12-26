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

int main() {
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);

    int n, m; scanf("%d%d", &n,&m);
    vector<VI> es(n), res(n);
    VI da(n), db(n);
    repn(i, m) {
        int a, b; scanf("%d%d", &a,&b);
        --a, --b;
        es[a].pb(b), res[b].pb(a);
        ++da[a], ++db[a];
    }
    const auto determine=[&](int x, const string& r) {
        for(int y: es[x]) {
            if(r[y]=='L') return 'W';
        }
        return 'L';
    };

    string ra(n, 'D'), rb(n, 'D');
    queue<PII> que;
    vector<bool> va(n, false), vb(n, false);
    repn(x, n) if(da[x]==0) {
        que.push(mp(x, 0)); va[x]=true;
        que.push(mp(x, 1)); vb[x]=true;
    }
    while(!que.empty()) {
        const int x=que.front().fi;
        const int player=que.front().se;
        que.pop();
        if(player==0) {
            ra[x]=determine(x, rb);
            for(int y: res[x]) if(!vb[y]) {
                if(--da[y]==0 || ra[x]=='L') {
                    vb[y]=true;
                    que.push(mp(y, 1));
                }
            }
        } else {
            rb[x]=determine(x, ra);
            for(int y: res[x]) if(!va[y]) {
                if(--db[y]==0) {
                    va[y]=true;
                    que.push(mp(y, 0));
                }
            }
        }
    }

    repn(x, n) if(ra[x]=='W') {
        que.push(mp(x, 0));
    }
    while(!que.empty()) {
        const int x=que.front().fi;
        const int player=que.front().se;
        que.pop();
        if(player==0) {
            for(int y: res[x]) if(!vb[y]) {
                rb[y]='L';
                vb[y]=true;
                que.push(mp(y, 1));
            }
        } else {
            for(int y: res[x]) if(!va[y]) {
                if(--db[y]==0) {
                    ra[y]='W';
                    va[y]=true;
                    que.push(mp(y, 0));
                }
            }
        }
    }
    cout<<ra<<endl<<rb<<endl;
    return 0;
}
