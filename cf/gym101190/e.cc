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
typedef vector<PLL> VPL;
typedef vector<string> VS;
template<class T, class S> ostream& operator<<(ostream& os, const pair<T, S>& v) { return os<<"("<<v.first<<", "<<v.second<<")"; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& v) { os<<"["; repn(i, sz(v)) { if(i) os<<", "; os<<v[i]; } return os<<"]"; }
template<class T> bool setmax(T &_a, T _b) { if(_b>_a) { _a=_b; return true; } return false; }
template<class T> bool setmin(T &_a, T _b) { if(_b<_a) { _a=_b; return true; } return false; }
template<class T> T gcd(T _a, T _b) { return _b==0?_a:gcd(_b,_a%_b); }

int main() {
    freopen("expect.in", "r", stdin);
    freopen("expect.out", "w", stdout);
    int n, qn; scanf("%d%d", &n,&qn);

    VPL events;
    repn(i, n) {
        char op[9]; int t, k;
        scanf("%s%d%d", op, &t,&k);
        if(op[0]=='-') k=-k;
        events.pb(mp(t, k));
    }
    sort(all(events));
    VPL blocks;
    LL end_height=0, tot=0, tot_w=0;
    repn(i, sz(events)) {
        end_height+=events[i].se;
        if(end_height<0 && i+1<sz(events)) {
            LL w=events[i+1].fi-events[i].fi;
            blocks.pb(mp(end_height, w));
            tot+=(-end_height)*w;
            tot_w+=w;
        }
    }

    VPI queries(qn);
    repn(i, qn) {
        scanf("%d", &queries[i].fi);
        queries[i].se=i;
    }
    sort(all(queries));
    vector<LL> ans(qn);

    //cout<<end_height<<endl;

    sort(all(blocks));
    LL cur_height=0;
    for(const auto& q: queries) {
        LL target_height=-q.fi;
        while(cur_height>target_height) {
            if(!blocks.empty() && blocks.back().fi>target_height) {
                const auto b=blocks.back();
                blocks.pop_back();
                tot-=tot_w*(cur_height-b.fi);
                tot_w-=b.se;
                cur_height=b.fi;
        //cout<<"pop "<<b<<" "<<cur_height<<" "<<tot_w<<" "<<tot<<endl;
            } else {
                tot-=tot_w*(cur_height-target_height);
                cur_height=target_height;
            }
        }
        //cout<<cur_height<<" "<<tot_w<<" "<<tot<<endl;
        if(cur_height>end_height) {
            ans[q.se]=-1;
        } else {
            ans[q.se]=tot;
        }
    }
    repn(i, qn) {
        if(ans[i]<0) {
            printf("INFINITY\n");
        } else {
            printf("%lld\n", ans[i]);
        }
    }
    return 0;
}
