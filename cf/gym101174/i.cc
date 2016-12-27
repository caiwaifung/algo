#include <algorithm>
#include <map>
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
typedef vector<LL> VL;
typedef vector<int> VI;
typedef vector<PII> VPI;
typedef vector<string> VS;
template<class T, class S> ostream& operator<<(ostream& os, const pair<T, S>& v) { return os<<"("<<v.first<<", "<<v.second<<")"; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& v) { os<<"["; repn(i, sz(v)) { if(i) os<<", "; os<<v[i]; } return os<<"]"; }
template<class T> bool setmax(T &_a, T _b) { if(_b>_a) { _a=_b; return true; } return false; }
template<class T> bool setmin(T &_a, T _b) { if(_b<_a) { _a=_b; return true; } return false; }
template<class T> T gcd(T _a, T _b) { return _b==0?_a:gcd(_b,_a%_b); }

vector<pair<int, PII>> solve(vector<pair<int, VI>> records) {
    map<PII, int> ids;
    const auto id=[&](PII p) {
        if(p.fi>p.se) swap(p.fi, p.se);
        if(ids.count(p)) return ids[p];
        int i=sz(ids);
        return ids[p]=i;
    };
    vector<VI> includes(sz(records));
    repn(i, sz(records)) {
        int last=-1;
        for(int x: records[i].se) {
            if(last>=0) includes[i].pb(id(mp(last, x)));
            last=x;
        }
    }
    const int n=sz(ids);

    vector<VI> a(sz(records), VI(n+1));
    repn(i, sz(records)) {
        for(int j: includes[i]) {
            (a[i][j]+=1)%=13;
        }
        a[i][n]=(records[i].fi%13);
    }
    VI inv(13);
    inv[0]=0;
    rep(i, 1, 12) rep(j, 1, 12) if(i*j%13==1) inv[i]=j;
    //cout<<inv<<endl;

    //for(const auto& kv: ids) cout<<kv<<endl;
    //cout<<a<<endl;

    VI repre(sz(records), -1);
    repn(i, sz(records)) {
        int i0=(i==0 ? 0 : repre[i-1]+1);
        while(i0<n) {
            bool found=false;
            replr(k, i, sz(records)) {
                if(a[k][i0]!=0) {
                    swap(a[i], a[k]);
                    found=true;
                    break;
                }
            }
            if(found) {
                break;
            }
            ++i0;
        }
        if(i0>=n) {
            break;
        }
        repre[i]=i0;

        int coeff=inv[a[i][i0]];
        rep(j, 0, n) (a[i][j]*=coeff)%=13;

        replr(k, i+1, sz(records)) {
            if(a[k][i0]!=0) {
                int c=a[k][i0];
                rep(j, 0, n) a[k][j]=((a[k][j]-a[i][j]*c)%13+13)%13;
            }
        }
    }

    //cout<<a<<endl;

    VI solution(n, 1);
    irepn(i, sz(records)) {
        int i0=repre[i];
        if(i0<0) continue;
        repn(j, n) {
            if(j!=i0) {
                (a[i][n]-=a[i][j]*solution[j])%=13;
            }
        }
        a[i][n]=(a[i][n]%13+13)%13;
        //cout<<a[i]<<endl;
        rep(x, 1, 12) {
            if(x*a[i][i0]%13==a[i][n]) {
                solution[i0]=x;
                break;
            }
        }
    }
    vector<pair<int, PII>> r;
    for(const auto& kv: ids) {
        r.pb(mp(solution[kv.se], kv.fi));
    }
    return r;
}

int main() {
    int n, s, t, nr;
    cin>>n>>s>>t>>nr;
    --s, --t;
    vector<pair<int, VI>> records;
    repn(i, nr) {
        int u, k; cin>>u>>k;
        VI trip(k);
        repn(j, k) { cin>>trip[j]; --trip[j]; }
        records.pb(mp(u, trip));
    }

    vector<pair<int, PII>> edges=solve(records);
    //cout<<edges<<endl;
    vector<VI> g(n, VI(n, 1<<29));
    repn(i, n) g[i][i]=0;
    for(const auto& kv: edges) {
        setmin(g[kv.se.fi][kv.se.se], kv.fi);
        setmin(g[kv.se.se][kv.se.fi], kv.fi);
    }
    repn(k, n) repn(i, n) repn(j, n) {
        setmin(g[i][j], g[i][k]+g[k][j]);
    }
    cout<<g[s][t]<<endl;

    return 0;
}
