#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

// {{{
// clang-format off
#define all(a) (a).begin(), (a).end()
#define sz(a) static_cast<int>((a).size())
#define fillchar(a, x) memset(a, x, sizeof(a))
#define rep(i, a, b) for (int i = int(a); i <= int(b); ++i)
#define irep(i, a, b) for (int i = int(a); i >= int(b); --i)
#define replr(i, a, b) rep(i, a, (b)-1)
#define reprl(i, a, b) irep(i, (b)-1, a)
#define repn(i, n) rep(i, 0, (n)-1)
#define irepn(i, n) irep(i, (n)-1, 0)
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define popcount __builtin_popcount
typedef long long LL;
typedef long double LD;
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
typedef pair<double, double> PDD;
typedef vector<int> VI;
typedef vector<LL> VL;
typedef vector<double> VD;
typedef vector<bool> VB;
typedef vector<string> VS;
typedef vector<PII> VPI;
typedef vector<PLL> VPL;
typedef vector<PDD> VPD;
typedef vector<VI> VVI;
typedef vector<VL> VVL;
typedef vector<VD> VVD;
typedef vector<VB> VVB;
typedef vector<VS> VVS;
typedef vector<VPI> VVPI;
typedef vector<VPL> VVPL;
template <class T, class S> ostream& operator<<(ostream& os, const pair<T, S>& v) { return os << "(" << v.first << ", " << v.second << ")"; }
template <class T> ostream& operator<<(ostream& os, const vector<T>& v) { os << "["; repn(i, sz(v)) { if(i) os << ", "; os << v[i]; } return os << "]"; }
template <class T> bool setmax(T& _a, T _b) { if(_a < _b) { _a = _b; return true; } return false; }
template <class T> bool setmin(T& _a, T _b) { if(_b < _a) { _a = _b; return true; } return false; }
template <class T> T gcd(T _a, T _b) { return _b == 0 ? _a : gcd(_b, _a % _b); }
VI read_vi(int n = -1) { if (n < 0) scanf("%d", &n); VI a(n); repn(i, n) scanf("%d", &a[i]); return a; }
VL read_vl(int n = -1) { if (n < 0) scanf("%d", &n); VL a(n); repn(i, n) scanf("%lld", &a[i]); return a; }
VD read_vd(int n = -1) { if (n < 0) scanf("%d", &n); VD a(n); repn(i, n) scanf("%lf", &a[i]); return a; }
VPI read_vpi(int n = -1) { if (n < 0) scanf("%d", &n); VPI a(n); repn(i, n) scanf("%d%d", &a[i].fi,&a[i].se); return a; }
VPL read_vpl(int n = -1) { if (n < 0) scanf("%d", &n); VPL a(n); repn(i, n) scanf("%lld%lld", &a[i].fi,&a[i].se); return a; }
VPD read_vpd(int n = -1) { if (n < 0) scanf("%d", &n); VPD a(n); repn(i, n) scanf("%lf%lf", &a[i].fi,&a[i].se); return a; }
inline LL powmod(LL a, LL b, LL m) { LL r = 1; for(; b > 0; b >>= 1, a = a * a % m) { if(b & 1) r = r * a % m; } return r; }
// clang-format on
// }}}

const LL P = 127;
const LL M = LL(1e9) + 7;

int main() {
    static char s[100010];
    scanf("%s", s);
    int n = (int)strlen(s);
    unordered_map<LL, VI> m;
    rep(len, 1, min(10, n)) {
        LL h = 0, p = 1;
        repn(i, len - 1) p = p * P % M;
        repn(i, n) {
            h = (h * P + int(s[i])) % M;
            if(i >= len - 1) {
                m[h].pb(i - len + 1);
                h = ((h - int(s[i - len + 1]) * p) % M + M) % M;
            }
        }
    }
    for(auto& kv : m) sort(all(kv.se));

    const auto match = [&](int l, int r, const string& p) {
        if(r - l != sz(p) || l < 0 || r > n) return false;
        repn(i, sz(p)) if(s[l + i] != p[i]) return false;
        return true;
    };

    const auto solve = [&](int l, int r, string p) {
        if(p.find('*') == string::npos) return match(l, r, p);
        if(p[0] != '*') {
            int i = (int)p.find('*');
            string cur = p.substr(0, i);
            p = p.substr(i);
            // cout << "query1 " << cur << " " << p << endl;
            if(!match(l, l + sz(cur), cur)) return false;
            l += sz(cur);
        }
        if(p.back() != '*') {
            int i = sz(p) - 1;
            while(p[i] != '*') --i;
            string cur = p.substr(i + 1);
            p = p.substr(0, i + 1);
            if(!match(r - sz(cur), r, cur)) return false;
            r -= sz(cur);
        }
        if(l > r) return false;
        while(!p.empty()) {
            int i = (int)p.find('*');
            string cur = p.substr(0, i);
            p = p.substr(i + 1);
            // cout << "query " << cur << " " << p << endl;
            if(!cur.empty()) {
                if(sz(cur) > r - l) return false;
                if(match(l, l + sz(cur), cur)) {
                    l += sz(cur);
                    continue;
                }
                LL h = 0;
                for(char c : cur) h = (h * P + int(c)) % M;
                auto it = m.find(h);
                if(it == m.end()) return false;
                auto vec = it->se;
                auto x = lower_bound(all(vec), l);

                // if(x == vec.end()) return false;
                // l = *x + sz(cur);
                while(1) {
                    if(x == vec.end()) return false;
                    if(*x + sz(cur) > r) return false;
                    if(match(*x, *x + sz(cur), cur)) {
                        l = *x + sz(cur);
                        break;
                    }
                    ++x;
                }
            }
        }
        return true;
    };

    int q;
    scanf("%d", &q);
    while(q--) {
        int l, r;
        char p[15];
        scanf("%d%d%s", &l, &r, p), --l;
        printf("%s\n", solve(l, r, string(p)) ? "Yes" : "No");
    }
    return 0;
}
