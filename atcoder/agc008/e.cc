#include <algorithm>
#include <unordered_map>
#include <numeric>
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

const LL MOD=LL(1e9)+7;

int vio(VI a) {
    VI p(sz(a));
    iota(all(p), 0);
    int ans=0;
    do {
        bool ok=true;
        repn(i, sz(p)) if(!(p[i]==a[i] || p[p[i]]==a[i])) { ok=false; break; }
        if(ok) { ++ans; //cout<<p<<endl; 
        }
    } while(next_permutation(all(p)));
    return ans;
}

LL solve(VI arms) {
    //cout<<arms<<endl;
    const int n=sz(arms);
    VI c(n*2);
    repn(i, n) c[i]=c[i+n]=(arms[i]>0);
    replr(i, 1, n*2) c[i]+=c[i-1];
    LL ans=1;
    repn(i, n) if(arms[i]>0) {
        if(arms[i]>n) return 0;
        if(c[i+arms[i]-1]>c[i]) return 0;
        if(c[i+arms[i]]==c[i]) (ans*=2)%=MOD;
    }
    return ans;
}

LL solve_cycles(int size, int num) {
    //cout<<size<<" "<<num<<endl;
    VL f(num+1);
    f[0]=1;
    rep(i, 1, num) {
        (f[i]+=f[i-1])%=MOD;
        if(size%2==1 && size>1) {
            (f[i]+=f[i-1])%=MOD;
        }
        if(i>=2) {
            (f[i]+=f[i-2]*size%MOD*(i-1))%=MOD;
        }
    }
    return f[num];
}

LL go(VI a) {
    const int n=sz(a);
    VI deg(n); repn(i, n) if(++deg[a[i]]>2) return 0;

    vector<VI> es(n); repn(i, n) { es[i].pb(a[i]); es[a[i]].pb(i); }
    vector<bool> vis(n, false);
    const auto extract=[&](int start) {
        VI r; r.pb(start);
        queue<int> que;
        que.push(start), vis[start]=true;
        while(!que.empty()) {
            int x=que.front(); que.pop();
            for(int y: es[x]) if(!vis[y]) {
                vis[y]=true, que.push(y);
                r.pb(y);
            }
        }
        return r;
    };
    VI f=a;
    const function<int(int)> get=[&](int x) { return f[x]==x ? x : f[x]=get(f[x]); };

    unordered_map<int, int> cycles;
    VI cnt(n);
    LL ans=1;
    repn(start, n) if(!vis[start]) {
        VI xs=extract(start);
        VI c;
        {
            int x=xs[0]; repn(i, sz(xs)) x=a[x];
            for(int y=x; ; ) { c.pb(y); f[y]=y; y=a[y]; if(y==x) break; }
        }
        for(int x: xs) if(f[x]!=x) {
            ++cnt[get(x)];
            if(deg[x]>1) return 0;
        }

        VI arms; bool found=false;
        for(int x: c) { arms.pb(cnt[x]); if(cnt[x]>0) found=true; }
        reverse(all(arms));

        if(!found) {
            cycles[sz(xs)]++;
        } else {
            (ans*=solve(arms))%=MOD;
        }
    }
    for(const auto& kv: cycles) {
        (ans*=solve_cycles(kv.fi, kv.se))%=MOD;
    }
    return ans;
}

int main() {
    //cout<<vio({2,0,1,1,3,4})<<endl;

    //cout<<vio({7,0,1,2,3,4,5,6, 1,5})<<endl;
    //cout<<go({7,0,1,2,3,4,5,6, 1,5})<<endl;
    //
    //
    int n; scanf("%d", &n);
    VI a(n); repn(i, n) { scanf("%d", &a[i]); --a[i]; }
    LL ans=go(a);
    printf("%d\n", (int)ans);

    return 0;
}
