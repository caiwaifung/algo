#include <algorithm>
#include <cassert>
#include <fstream>
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

bool isalpha(char c) { return isupper(c) || islower(c); }

VS split(const string& s) {
    VS r;
    string cur="";
    repn(i, sz(s)) {
        cur+=s[i];
        if(i==sz(s)-1 || isalpha(s[i])!=isalpha(s[i+1])) {
            r.pb(cur);
            cur="";
        }
    }
    return r;
}

bool iscap(const string& s) {
    if(sz(s)<=1) {
        return false;
    }
    if(!isupper(s[0])) {
        return false;
    }
    replr(i, 1, sz(s)) {
        if(!islower(s[i])) {
            return false;
        }
    }
    return true;
}

void solve(string line) {
    VS tokens=split(line);
    for(int i=0; i<sz(tokens); ++i) {
        if(iscap(tokens[i])) {
            int j=i;
            while(j+2<sz(tokens) && tokens[j+1]==" " && iscap(tokens[j+2])) {
                j+=2;
            }
            if(i<j) {
                string abbr;
                for(int k=i; k<=j; k+=2) {
                    abbr+=tokens[k][0];
                }
                printf("%s (", abbr.c_str());
                rep(k, i, j) printf("%s", tokens[k].c_str());
                printf(")");
                i=j;
                continue;
            }
        }
        printf("%s", tokens[i].c_str());
    }
    printf("\n");
}

int main() {
    freopen("abbreviation.in", "rt", stdin);
    freopen("abbreviation.out", "wt", stdout);
    while(1) {
        static char buf[999];
        if(!gets(buf)) break;
        solve(string(buf));
    }
    return 0;
}
