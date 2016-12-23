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

bool reinforce(string& s, VI rules) {
    const int n=sz(s), m=sz(rules);
    if(m==0) {
        string old=s;
        s=string(n, '.');
        return s!=old;
    }
    VI bcnt(n+1), wcnt(n+1);
    repn(i, n) {
        bcnt[i+1]=bcnt[i]+(s[i]=='X');
        wcnt[i+1]=wcnt[i]+(s[i]=='.');
    }
    const auto can_b=[&](int l, int r) {
        return wcnt[r]-wcnt[l]==0;
    };
    const auto can_w=[&](int l, int r) {
        return bcnt[r]-bcnt[l]==0;
    };

    vector<vector<bool>> f(m, vector<bool>(n, false));
    vector<vector<bool>> f2(m, vector<bool>(n, false));
    const auto go_f2=[&](int i) {
        replr(j, 1, n) {
            if(s[j]=='X') {
                f2[i][j]=false;
            } else {
                f2[i][j]=(f2[i][j-1] || f[i][j-1]);
            }
        }
    };
    repn(j, n-rules[0]+1) {
        if(can_w(0, j) && can_b(j, j+rules[0])) {
            f[0][j+rules[0]-1]=true;
        }
    }
    go_f2(0);
    replr(i, 1, m) {
        replr(j, 1, n-rules[i]+1) {
            if(f2[i-1][j-1] && can_b(j, j+rules[i])) {
                f[i][j+rules[i]-1]=true;
            }
        }
        go_f2(i);
    }

    vector<vector<bool>> g(m, vector<bool>(n, false));
    vector<vector<bool>> g2(m, vector<bool>(n, false));
    const auto go_g2=[&](int i) {
        irepn(j, n-1) {
            if(s[j]=='X') {
                g2[i][j]=false;
            } else {
                g2[i][j]=(g2[i][j+1] || g[i][j+1]);
            }
        }
    };
    irepn(j, n-rules[m-1]+1) {
        if(can_b(j, j+rules[m-1]) && can_w(j+rules[m-1], n)) {
            g[m-1][j]=true;
        }
    }
    go_g2(m-1);
    irepn(i, m-1) {
        irepn(j, n-rules[i]+1) {
            if(g2[i+1][j+rules[i]] && can_b(j, j+rules[i])) {
                g[i][j]=true;
            }
        }
        go_g2(i);
    }

    vector<bool> label_w(n);
    repn(j, n) {
        if(f2[m-1][j] && can_w(j, n)) label_w[j]=true;
        if(can_w(0, j+1) && g2[0][j]) label_w[j]=true;
        repn(i, m-1) if(f2[i][j] && g2[i+1][j]) label_w[j]=true;
    }
    vector<bool> label_b(n);
    vector<int> colorings(n+1);
    repn(i, m) {
        repn(j, n-rules[i]+1) if(can_b(j, j+rules[i])) {
            if(i==0) {
                if(!can_w(0, j)) continue;
            } else {
                if(j==0 || !f2[i-1][j-1]) continue;
            }
            if(i==m-1) {
                if(!can_w(j+rules[i], n)) continue;
            } else {
                if(j+rules[i]==n || !g2[i+1][j+rules[i]]) continue;
            }
            colorings[j]++;
            colorings[j+rules[i]]--;
        }
    }
    int cur=0;
    repn(j, n) {
        cur+=colorings[j];
        if(cur>0) label_b[j]=true;
    }

    string old=s;
    repn(j, n) {
        assert(label_w[j] || label_b[j]);
        if(!label_w[j]) {
            assert(s[j]!='.');
            s[j]='X';
        }
        if(!label_b[j]) {
            assert(s[j]!='X');
            s[j]='.';
        }
    }
    return s!=old;
}

int main() {
    /*
    string x(7,'?');
    reinforce(x, {2, 1, 1});
    cout<<x<<endl; return 0;
    */


    const auto read_vec=[] {
        int n; scanf("%d", &n);
        VI a(n); repn(i, n) scanf("%d", &a[i]);
        return a;
    };
    int n, m; scanf("%d%d", &n,&m);
    vector<VI> r_rules, c_rules;
    repn(i, n) r_rules.pb(read_vec());
    repn(i, m) c_rules.pb(read_vec());

    VS g(n, string(m, '?'));
    bool cont=true;
    while(cont) {
        cont=false;
        repn(i, n) {
            if(reinforce(g[i], r_rules[i])) {
                cont=true;
            }
        }
        repn(j, m) {
            string s;
            repn(i, n) s+=g[i][j];
            if(reinforce(s, c_rules[j])) {
                repn(i, n) g[i][j]=s[i];
                cont=true;
            }
        }
    }
    repn(i, n) printf("%s\n", g[i].c_str());
    return 0;
}
