#include <cassert>
#include <tuple>
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

string f[99][5];

tuple<string, int, int, int> get(char c1, char c2, char c3, int x) {
    if(x==0) return make_tuple<string, int, int, int>("", 0, 0, 0);
    if(x==1) return make_tuple<string, int, int, int>(string()+c1, 1, 0, 0);
    if(x==2) return make_tuple<string, int, int, int>(string()+c1+c1, 2, 0, 0);
    if(x==3) return make_tuple<string, int, int, int>(string()+c1+c1+c1, 3, 0, 0);
    if(x==4) return make_tuple<string, int, int, int>(string()+c1+c2, 1, 1, 0);
    if(x==5) return make_tuple<string, int, int, int>(string()+c2, 0, 1, 0);
    if(x==6) return make_tuple<string, int, int, int>(string()+c2+c1, 1, 1, 0);
    if(x==7) return make_tuple<string, int, int, int>(string()+c2+c1+c1, 2, 1, 0);
    if(x==8) return make_tuple<string, int, int, int>(string()+c2+c1+c1+c1, 3, 1, 0);
    if(x==9) return make_tuple<string, int, int, int>(string()+c1+c3, 1, 0, 1);
    return make_tuple<string, int,int,int>("",0,0,0);
}

void solve(string cx, VI x, string cy, VI y) {
    repn(i, sz(x)) repn(cur, 10) {
        string scur; int u1, u2, u3;
        tie(scur, u1, u2, u3)=get(cx[i], cy[i], i<sz(cx)?cx[i+1]:' ', cur);
        repn(u, 5) if(x[i]>=u1+u && y[i]>=u2) {
            string tmp=scur+f[i][u];
            if(sz(tmp)>=sz(f[i+1][u3])) f[i+1][u3]=tmp;
        }
    }
    string ans=f[sz(x)][0];
    cout<<ans<<endl;
}

int main() {
    string s, t; cin>>s>>t;
    VI a(sz(s));
    for(char ch: t) if(s.find(ch)!=string::npos) {
        a[int(s.find(ch))]++;
    }
    string cx, cy; VI x, y;
    repn(i, sz(a)) {
        if(i%2) cy.pb(s[i]), y.pb(a[i]);
            else cx.pb(s[i]), x.pb(a[i]);
    }
    if(sz(y)<sz(x)) {
        cy.pb(' '); y.pb(0);
    }
    solve(cx, x, cy, y);
    return 0;
}
