// 10:06 - 10:34
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
typedef unsigned long long ULL;
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

class HashValue {
private:
    static constexpr LL M1=LL(1e9)+7;
    LL h1;
    ULL h2;
    HashValue(LL v1, ULL v2) : h1(v1), h2(v2) {}

public:
    HashValue() : HashValue(0, 0) {}
    HashValue(char c) : HashValue(LL(c), ULL(c)) {}
    static HashValue unit() { return HashValue(1, 1); }
    static HashValue multipler() { return HashValue(911, 977); }

    bool operator ==(const HashValue& b) const {
        return h1==b.h1 && h2==b.h2;
    }
    HashValue operator +(const HashValue& b) const {
        return HashValue((h1+b.h1)%M1, h2+b.h2);
    }
    HashValue operator -(const HashValue& b) const {
        return HashValue((h1-b.h1+M1)%M1, h2-b.h2);
    }
    HashValue operator *(const HashValue& b) const {
        return HashValue(h1*b.h1%M1, h2*b.h2);
    }
    HashValue power(int b) const {
        HashValue a=*this, r=unit();
        for(; b>0; b>>=1, a=a*a) {
            if(b&1) r=r*a;
        }
        return r;
    }
};

bool is_substr(string a, string b) {
    HashValue ra;
    for(char c: a) {
        ra=ra*HashValue::multipler()+HashValue(c);
    }
    HashValue rb;
    repn(i, sz(a)) {
        rb=rb*HashValue::multipler()+HashValue(b[i]);
    }
    if(rb==ra) return true;
    HashValue pa=HashValue::multipler().power(sz(a));
    replr(i, sz(a), sz(b)) {
        rb=rb*HashValue::multipler()+HashValue(b[i])-HashValue(b[i-sz(a)])*pa;
        if(rb==ra) return true;
    }
    return false;
}

int solve_in_order(string a, string b) {
    vector<HashValue> ra(sz(a));
    {
        HashValue cur, tmp=HashValue::unit();
        irepn(i, sz(a)) {
            cur=cur+HashValue(a[i])*tmp;
            tmp=tmp*HashValue::multipler();
            ra[sz(a)-i-1]=cur;
        }
    }
    vector<HashValue> rb(sz(b));
    {
        HashValue cur;
        repn(i, sz(b)) {
            cur=cur*HashValue::multipler()+HashValue(b[i]);
            rb[i]=cur;
        }
    }
    irepn(i, min(sz(a), sz(b))) {
        if(ra[i]==rb[i]) {
            return sz(a)+sz(b)-i-1;
        }
    }
    return sz(a)+sz(b);
}

int solve(string a, string b) {
    if(sz(a)>sz(b)) swap(a, b);
    if(is_substr(a, b)) return sz(b);
    return min(solve_in_order(a, b), solve_in_order(b, a));
}

int solve(string a, string b, string c) {
    if(sz(a)>sz(b)) swap(a, b);
    if(sz(a)>sz(c)) swap(a, c);
    if(sz(b)>sz(c)) swap(b, c);
    if(is_substr(a, b) || is_substr(a, c)) return solve(b, c);
    if(is_substr(b, c)) return solve(a, c);
    int ans=1<<30;
    repn(t, 3) {
        setmin(ans, solve_in_order(b, a)+solve_in_order(a, c)-sz(a));
        setmin(ans, solve_in_order(c, a)+solve_in_order(a, b)-sz(a));
        string tmp=a; a=b, b=c, c=tmp;
    }
    return ans;
}

int main() {
    string a, b, c;
    cin>>a>>b>>c;
    cout<<solve(a, b, c)<<endl;
    return 0;
}
