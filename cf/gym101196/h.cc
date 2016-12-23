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

typedef vector<vector<bool>> Board;
const int dx[4]={1, 0, -1, 0};
const int dy[4]={0, 1, 0, -1};
int n, m;

PII dir(PII p, int d) { return mp(p.fi+dx[d], p.se+dy[d]); }

pair<Board, PII> read() {
    int r, c; cin>>r>>c;
    Board b(r, vector<bool>(c));
    PII sample_a;
    repn(i, r) {
        string s; cin>>s;
        repn(j, c) {
            b[i][j]=(s[j]!='.');
            if(s[j]=='A') sample_a=mp(i, j);
        }
    }
    return mp(b, sample_a);
}

VPI extract(Board& b, PII p) {
    VPI r;
    while(1) {
        assert(b[p.fi][p.se]);
        b[p.fi][p.se]=false;
        r.pb(p);
        bool found=false;
        repn(i, 4) {
            PII q=dir(p, i);
            if(q.fi<0 || q.fi>=n || q.se<0 || q.se>=m) continue;
            if(b[q.fi][q.se]) {
                p=q; found=true; break;
            }
        }
        if(!found) break;
    }
    return r;
}

VPI make_loop(VPI a, VPI b, PII start, PII end) {
    VPI r=a; reverse(all(r));
    r.pb(start);
    r.insert(r.end(), all(b));
    r.pb(end);
    return r;
}

Board cover(VPI loop) {
    Board b(n, vector<bool>(m, true));
    for(const auto& p: loop) b[p.fi][p.se]=false;
    queue<PII> que;
    repn(i, n) repn(j, m) if(i==0 || i==n-1 || j==0 || j==m-1) {
        if(b[i][j]) {
            b[i][j]=false; que.push(mp(i, j));
        }
    }
    while(!que.empty()) {
        const PII p=que.front();
        que.pop();
        repn(i, 4) {
            PII q=dir(p, i);
            if(q.fi<0 || q.fi>=n || q.se<0 || q.se>=m) continue;
            if(b[q.fi][q.se]) {
                b[q.fi][q.se]=false;
                que.push(q);
            }
        }
    }
    return b;
}

bool inside(PII p, VPI loop) {
    Board c=cover(loop);
    return c[p.fi][p.se];
}

bool onside(PII p, VPI loop) {
    for(const auto& q: loop) if(p==q) return true;
    return false;
}

int area(VPI loop) {
    Board c=cover(loop);
    int ans=0;
    for(const auto& r: c) for(bool x: r) if(x) ++ans;
    return ans;
}

int main() {
    Board g; PII sample_a;
    tie(g, sample_a)=read();
    n=sz(g), m=sz(g[0]);

    VPI crosses;
    replr(i, 1, n-1) replr(j, 1, m-1) {
        if(g[i][j] && g[i+1][j] && g[i][j+1] && g[i-1][j] && g[i][j-1]) {
            crosses.pb(mp(i, j));
        }
    }
    assert(sz(crosses)==2);
    PII s=crosses[0], t=crosses[1];

    g[s.fi][s.se]=g[t.fi][t.se]=false;
    VPI links[4];
    repn(i, 4) {
        links[i]=extract(g, dir(s, i));
    }
    VPI big[2];
    repn(i, 2) {
        big[i]=make_loop(links[i], links[i+2], s, t);
    }
    int inner_i[2];
    repn(i, 2) {
        inner_i[i]=(inside(links[i][0], big[i^1]) ? i : i+2);
    }

    VPI inner_loop=make_loop(links[inner_i[0]], links[inner_i[1]], s, t);
    VPI loops[2];
    repn(i, 2) {
        loops[i]=make_loop(links[inner_i[i]^2], links[inner_i[i^1]], s, t);
    }
    if(!onside(sample_a, big[0])) {
        swap(loops[0], loops[1]);
        assert(onside(sample_a, big[1]));
    }

    cout<<area(loops[0])<<" "<<area(loops[1])<<" "<<area(inner_loop)<<endl;

    return 0;
}
