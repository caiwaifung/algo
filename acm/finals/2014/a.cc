// 3210123456
// ....BABABA  
// ..ABB..ABA  2,-1
// ..ABBBAA..  5,2
// AAABBB....  3,-3
// 
// 1012345678
// ..BABABABA
// ABBABAB..A  6,-1
// ABBA..BBAA  3,6
// A..ABBBBAA  0,3
// AAAABBBB..  7,0
// 
// 101234567890
// ..BABABABABA
// ABBABABAB..A  8,-1
// ABBA..BABBAA  3,8
// ABBAABB..BAA  6,3
// A..AABBBBBAA  0,6
// AAAAABBBBB..  9,0
// 
// 10123456789012
// ..BABABABABABA
// ABBABABABAB..A  10,-1
// ABBABABA..BBAA  7,10
// ABB..ABAABBBAA  2,7
// ABBAAAB..BBBAA  6,2
// A..AAABBBBBBAA  0,6
// AAAAAABBBBBB..  11,0
// 
// 1012345678901234
// ..BABABABABABABA
// ABBABABABABAB..A  12,-1
// ABBABA..BABABBAA  5,12
// ABBABAABB..ABBAA  8,5
// ABBA..ABBBAABBAA  3,8
// ABBAAAABBB..BBAA  9,3
// A..AAAABBBBBBBAA  0,9
// AAAAAAABBBBBBB..  13,0
// 
// 
// ..BABA*****BABA
// ABBAAA***..BBAA

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

VPI solve(int n) {
    if(n==3) return {{2,-1}, {5,2}, {3,-3}};
    if(n==4) return {{6,-1},{3,6},{0,3},{7,0}};
    if(n==5) return {{8,-1},{3,8},{6,3},{0,6},{9,0}};
    if(n==6) return {{10,-1},{7,10},{2,7},{6,2},{0,6},{11,0}};
    if(n==7) return {{12,-1},{5,12},{8,5},{3,8},{9,3},{0,9},{13,0}};
    VPI r;
    r.pb(mp(n*2-2, -1));
    r.pb(mp(3, n*2-2));
    for(const auto& p: solve(n-4)) {
        r.pb(mp(p.fi+4, p.se+4));
    }
    r.pb(mp(0, n*2-5));
    r.pb(mp(n*2-1, 0));
    return r;
}

int main() {
    int n; scanf("%d", &n);
    for(const auto& p: solve(n)) {
        printf("%d to %d\n", p.fi, p.se);
    }
    return 0;
}
