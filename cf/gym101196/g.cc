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

VI read_vec() {
    int n; scanf("%d", &n);
    VI a(n);
    repn(i, n) scanf("%d", &a[i]);
    reverse(all(a));
    return a;
}

LL go(VI a, VI b, VI c) {
    const int n=sz(a)+sz(b)+sz(c);
    //cout<<"go "<<a<<" "<<b<<" "<<c<<endl;
    if(n==0) return 0;
    if(sz(b)>0 && b.back()==n) return -1;
    if(sz(a)>0 && a.back()==n) {
        a.pop_back();
        LL tmp=go(a, c, b);
        if(tmp<0) return -1;
        return tmp+(1ll<<(n-1));
    } else {
        c.pop_back();
        return go(b, a, c);
    }
}

LL solve() {
    VI a=read_vec(); 
    VI b=read_vec(); 
    VI c=read_vec(); 
    int n=sz(a)+sz(b)+sz(c);
    vector<bool> used(n, false);
    const auto check=[&](VI x) {
        repn(i, sz(x)-1) if(x[i]>=x[i+1]) return false;
        for(int i: x) {
            if(i<1 || i>n || used[i-1]) return false;
            used[i-1]=true;
        }
        return true;
    };
    if(!check(a)) return -1;
    if(!check(b)) return -1;
    if(!check(c)) return -1;
    return go(a, b, c);
}

int main() {
    LL ans=solve();
    if(ans<0) {
        printf("No\n");
    } else {
        printf("%lld\n", ans);
    }

    return 0;
}
