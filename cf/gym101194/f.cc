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

struct State {
    const int len;
    State* succ[26];
    State* f;

    State(int l, State* copy=nullptr) : len(l) {
        if(copy) {
            memcpy(succ, copy->succ, sizeof(succ));
            f=copy->f;
        } else {
            fillchar(succ, 0);
            f=nullptr;
        }
    }

    bool good=false, bad=false;
    bool has_wanted=false;
};
vector<State*> states;
State* root;

State* extend(State* p, int ch) {
    State* np=new State(p->len+1);
    for(; p && !p->succ[ch]; p=p->f) {
        p->succ[ch]=np;
    }
    if(!p) {
        np->f=root;
    } else {
        State* q=p->succ[ch];
        if(q->len==p->len+1) {
            np->f=q;
        } else {
            State* nq=new State(p->len+1, q);
            states.pb(nq);
            np->f=q->f=nq;
            for(; p && p->succ[ch]==q; p=p->f) {
                p->succ[ch]=nq;
            }
        }
    }

    if(np->len>np->f->len) {
        states.pb(np);
    } else {
        np=np->f;
    }
    return np;
}

void solve() {
    for(State* x: states) delete x;
    states.clear();
    
    root=new State(0);

    int n; scanf("%d", &n);
    repn(i, n) {
        static char s[250010];
        scanf("%s", s);
        int len=(int)strlen(s);
        State* last=root;
        repn(j, len) {
            last=extend(last, s[j]-'a');
            if(i==0) {
                last->good=true;
            } else {
                last->bad=true;
            }
        }
    }

    sort(all(states), [](State* p, State* q) { return p->len>q->len; });
    int min_len=1<<30;
    for(State* p: states) {
        if(p->good && !p->bad) {
            setmin(min_len, p->f->len+1);
        }
        p->f->good|=p->good;
        p->f->bad|=p->bad;
    }
    if(min_len==(1<<30)) {
        printf("Impossible\n");
        return;
    }
    //printf("[min_len=%d] ",min_len); 
    for(State* p: states) {
        if(p->f->len+1==min_len && p->good && !p->bad) {
            p->has_wanted=true;
        }
        repn(i, 26) {
            if(p->succ[i] && p->succ[i]!=p->f->succ[i] && p->succ[i]->has_wanted) {
                p->has_wanted=true;
            }
        }
    }
    
    string s;
    State* p=root;
    while(!(p->good && !p->bad)) {
        repn(i, 26) {
            if(p->succ[i] && p->succ[i]->has_wanted) {
                s+=char('a'+i);
                p=p->succ[i];
                break;
            }
        }
    }
    printf("%s\n", s.c_str());
}

int main() {
    int cs; scanf("%d", &cs);
    rep(i, 1, cs) {
        printf("Case #%d: ", i);
        solve();
    }
    return 0;
}
