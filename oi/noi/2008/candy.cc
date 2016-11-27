// 9:21 - 9:43 - wa sample
//      - 9:53 - tle
//      - 10:19 - ac
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

struct Board {
    const int n, m, sx, sy;
    vector<VI> tr;

    Board(int _n, int _m) : n(_n), m(_m), sx(n+m-1), sy(n+m-1), tr(sx+1, VI(sy+1)) {}

    void add(int i, int j, int val) {
        const int x=max(0, j-i+n-1), y=max(0, i+j);
        if(x>=sx || y>=sy) return;
        for(int u=x+1; u<=sx; u+=u&-u) {
            for(int v=y+1; v<=sy; v+=v&-v) {
                tr[u][v]+=val;
            }
        }
    }

    int get(int i, int j) {
        const int x=min(sx-1, j-i+n-1), y=min(sy-1, i+j);
        if(x<0 || y<0) return 0;
        int ans=0;
        for(int u=x+1; u>=1; u-=u&-u) {
            for(int v=y+1; v>=1; v-=v&-v) {
                ans+=tr[u][v];
            }
        }
        return ans;
    }
};

struct Cloud {
    int t, l, r, d;
};

int main() {
    int num, len;
    scanf("%d%d", &num,&len);
    Board bl(2*len, len+1), br(2*len, len+1);

    const auto add=[&](Cloud cloud, int v) {
        cloud.t%=len*2;
        int x;
        if(cloud.d<0) {
            x=cloud.t+cloud.l;
        } else {
            x=cloud.t-cloud.l;
        }
        x=(x+len*2)%(len*2);
        const int w=cloud.r-cloud.l;
        bl.add(x, 0, v), br.add(x, w, v);
        if(x<len) {
            bl.add(x+len, len, -v);
            bl.add(x+len*2, 0, v), br.add(x+len*2, w, v);
        } else {
            bl.add(x-len, len, -v);
            bl.add(x-len*2, 0, v), br.add(x-len*2, w, v);
        }
    };
    const auto query=[&](int t, int l, int r) {
        t%=len*2;
        int ans=bl.get(t, r);
        if(l>0) ans-=br.get(t, l-1);
        printf("%d\n", ans);
    };

    vector<Cloud> cloud_by_color(1000010);
    while(num--) {
        int type, t;
        scanf("%d%d", &type,&t);
        if(type==1) {
            int c; Cloud cloud; 
            cloud.t=t;
            scanf("%d%d%d%d", &c,&cloud.l,&cloud.r,&cloud.d);
            cloud_by_color[c]=cloud;
            add(cloud, 1);
        } else if(type==2) {
            int l, r; scanf("%d%d", &l,&r);
            query(t, l, r);
        } else if(type==3) {
            int c; scanf("%d", &c);
            add(cloud_by_color[c], -1);
        }
    }
    return 0;
}
