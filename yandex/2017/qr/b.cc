#include <algorithm>
#include <cassert>
#include <cmath>
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
typedef vector<string> VS;
typedef vector<PII> VPI;
typedef vector<PLL> VPL;
template <class T, class S> ostream& operator<<(ostream& os, const pair<T, S>& v) { return os << "(" << v.first << ", " << v.second << ")"; }
template <class T> ostream& operator<<(ostream& os, const vector<T>& v) { os << "["; repn(i, sz(v)) { if(i) os << ", "; os << v[i]; } return os << "]"; }
template <class T> bool setmax(T& _a, T _b) { if(_a < _b) { _a = _b; return true; } return false; }
template <class T> bool setmin(T& _a, T _b) { if(_b < _a) { _a = _b; return true; } return false; }
template <class T> T gcd(T _a, T _b) { return _b == 0 ? _a : gcd(_b, _a % _b); }
// clang-format on
// }}}

int main() {
    struct City {
        string name;
        vector<pair<string, int>> rooms;
    };
    int n;
    cin >> n;
    vector<City> cs(n);
    repn(i, n) {
        int m;
        cin >> cs[i].name >> m;
        cs[i].rooms.resize(m);
        repn(j, m) {
            string tmp;
            cin >> tmp >> cs[i].rooms[j].fi;
            repn(k, 24) if(tmp[k] == '.') cs[i].rooms[j].se ^= 1 << k;
        }
    }
    const auto query = [&](VS q) {
        repn(t, 24) {
            VS ans;
            bool ok = true;
            for(const auto& c : q) {
                int i = 0;
                while(cs[i].name != c) ++i;
                bool found = false;
                repn(j, sz(cs[i].rooms)) {
                    if(cs[i].rooms[j].se & (1 << t)) {
                        ans.pb(cs[i].rooms[j].fi);
                        found=true;
                        break;
                    }
                }
                if(!found) {
                    ok = false;
                    break;
                }
            }
            if(ok) return ans;
        }
        return VS();
    };
    int qn;
    cin >> qn;
    while(qn--) {
        int num;
        cin >> num;
        VS q(num);
        repn(i, num) cin >> q[i];
        VS ans = query(q);
        if(ans.empty()) {
            cout << "No" << endl;
        } else {
            cout << "Yes";
            for(const auto& s : ans) cout << " " << s;
            cout << endl;
        }
    }
    return 0;
}
