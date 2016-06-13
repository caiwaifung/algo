#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define sz(a) static_cast<int>(a.size())
#define all(a) a.begin(), a.end()
#define rep(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define irep(i, a, b) for(int i=int(a); i>=int(b); --i)
#define repn(i, n) rep(i, 0, (n)-1)
#define irepn(i, n) irep(i, (n)-1, 0)
#define fillchar(a, x) memset(a, x, sizeof(a))
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
template<class T> bool setmax(T &_a, T _b) { if(_b>_a) { _a=_b; return true; } return false; }
template<class T> bool setmin(T &_a, T _b) { if(_b<_a) { _a=_b; return true; } return false; }
template<class T> T gcd(T _a, T _b) { return _b==0?_a:gcd(_b,_a%_b); }

const int N=100010;

VPI es[N]; bool is[N];
int n, m, limit;

bool check(const VI& t) {
    repn(i, sz(t)) if(t[i]+t[sz(t)-i-1]>limit) return false;
    return true;
}

bool check(VI t, int i) {
    t.erase(t.begin()+i);
    return check(t);
}

pair<bool, int> ok(int x, int fa) {
    VI t; if(is[x]) t.pb(0);
    for(PII e: es[x]) if(e.fi!=fa) {
        auto cur=ok(e.fi, x);
        if(!cur.fi) return cur;
        if(cur.se>=0) t.pb(cur.se+e.se);
    }
    sort(all(t));
    if(sz(t)%2==0) {
        return mp(check(t), -1);
    } else {
        int le=0, ri=sz(t)-1;
        while(le<ri) {
            int mid=(le+ri)/2;
            if(check(t, mid)) ri=mid;
                else le=mid+1;
        }
        if(check(t, le)) return mp(true, t[le]);
        else return mp(false, -1);
    }
}

bool ok(int l) {
    limit=l;
    return ok(1, 0).fi;
}

int main() {
    scanf("%d%d", &n,&m);
    fillchar(is, false);
    repn(i, m) { int x; scanf("%d", &x); is[x]=true; }
    repn(i, n-1) {
        int a, b, c; scanf("%d%d%d", &a,&b,&c);
        es[a].pb(mp(b,c)), es[b].pb(mp(a,c));
    }
    int le=1, ri=int(1e9);
    while(le<ri) {
        int mid=(le+ri)/2;
        if(ok(mid)) ri=mid;
            else le=mid+1;
    }
    if(!ok(le)) le=-1;
    printf("%d\n", le);
    return 0;
}
