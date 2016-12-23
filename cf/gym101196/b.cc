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
    VPI best;
    int best_score=-1;
    const auto update=[&](PII p, int s) {
        if(s>best_score) {
            best_score=s;
            best.clear();
        }
        if(s==best_score) {
            best.pb(p);
        }
    };

    int n; cin>>n;
    VS names(n);
    repn(i, n) cin>>names[i];

    int p[2][2], offense[2], score[2];
    offense[0]=offense[1]=0;
    score[0]=score[1]=0;
    p[0][0]=0, p[1][0]=1, p[0][1]=2, p[1][1]=3;
    queue<int> que;
    replr(i, 4, n) que.push(i);

    string sequence; cin>>sequence;
    for(char ch: sequence) {
        int cur=(ch=='W'?1:0), other=cur^1;
        update(mp(p[cur][0], p[cur][1]), score[cur]);
        ++score[other], score[cur]=0;

        offense[other]^=1;

        que.push(p[cur][offense[cur]^1]);
        p[cur][offense[cur]^1]=p[cur][offense[cur]];
        p[cur][offense[cur]]=que.front();
        que.pop();
        if(offense[cur]==0) {
            offense[cur]^=1;
            swap(p[cur][0], p[cur][1]);
        }
    }
    repn(cur, 2) {
        update(mp(p[cur][0], p[cur][1]), score[cur]);
    }
    //cout<<best_score<<endl;
    for(const auto& r: best) {
        cout<<names[r.fi]<<" "<<names[r.se]<<endl;
    }

    return 0;
}
