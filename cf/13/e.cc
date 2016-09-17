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

const int N=100000;
const int Q=300;

PII jump[N];
int ptr[N];
int n;

void calc_jump(int i) {
    if(ptr[i]<0) {
        jump[i]=mp(i, 0);
    } else if(ptr[i]/Q>i/Q) {
        jump[i]=mp(ptr[i], 1);
    } else {
        jump[i]=jump[ptr[i]];
        ++jump[i].se;
    }
}

PII answer(int i) {
    int cnt=0;
    while(1) {
        if(jump[i].fi==i) {
            return mp(i, cnt);
        }
        cnt+=jump[i].se;
        i=jump[i].fi;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int m; cin>>n>>m;
    repn(i, n) {
        int a; cin>>a;
        ptr[i]=i+a;
        if(ptr[i]>=n) ptr[i]=-1;
    }
    irepn(i, n) calc_jump(i);
    while(m--) {
        int op, i; cin>>op>>i;
        --i;
        if(op==0) {
            int a; cin>>a;
            ptr[i]=i+a;
            if(ptr[i]>=n) ptr[i]=-1;
            reprl(j, i/Q*Q, i+1) calc_jump(j);
        } else {
            PII r=answer(i);
            cout<<r.fi+1<<" "<<r.se+1<<endl;
        }
    }


    return 0;
}
