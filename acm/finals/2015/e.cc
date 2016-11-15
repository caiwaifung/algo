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

string read_str() {
    static char buf[4040];
    scanf("%s", buf);
    return string(buf);
}

bool le(const string& x, const string& y) {
    if(x=="") return true;
    int i=0;
    for(char c: y) {
        if(c==x[i]) {
            if(++i==sz(x)) return true;
        }
    }
    return false;
}

bool solve() {
    int n; scanf("%d", &n);
    string current=read_str();
    VS a;
    repn(i, n) a.pb(read_str());
    a.pb("");
    sort(all(a), [](const string& x, const string& y) { return sz(x)<sz(y); });
    for(const auto& s: a) {
        if(!le(s, current)) return false;
    }

    struct State {
        int i, j;
        State* pre;
        State(int _i, int _j, State* p=nullptr) : i(_i), j(_j), pre(p) {}
    };
    State *p=new State(1, 0), *q=nullptr;
    replr(i, 2, sz(a)) {
        State *np=nullptr, *nq=nullptr;
        if(q==nullptr) {
            if(le(a[p->i], a[i])) np=new State(i, p->j, p);
            if(le(a[p->j], a[i])) nq=new State(i, p->i, p);
        } else {
            if(le(a[p->i], a[i])) {
                np=new State(i, p->j, p);
                nq=new State(i, q->j, q);
            } else {
                if(le(a[p->j], a[i])) np=new State(i, p->i, p);
                else if(le(a[q->j], a[i])) np=new State(i, p->i, q);
            }
        }
        if(nq && !np) swap(np, nq);
        if(!np) return false;
        p=np, q=nq;
    }
    vector<int> ans(sz(a), -1);
    ans[sz(a)-1]=0;
    while(p!=nullptr) {
        if(ans[p->j]<0) {
            ans[p->j]=ans[p->i]^1;
        } else {
            ans[p->i]=ans[p->j]^1;
        }
        p=p->pre;
    }
    VS u, v;
    replr(i, 1, sz(a)) (ans[i]?u:v).pb(a[i]);
    printf("%d %d\n", sz(u), sz(v));
    for(const auto& s: u) printf("%s\n", s.c_str());
    for(const auto& s: v) printf("%s\n", s.c_str());
    return true;
}

int main() {
    if(!solve()) {
        printf("impossible\n");
    }
    return 0;
}
