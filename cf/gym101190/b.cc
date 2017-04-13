// 8:57 - 9:14 - pass sample - ac
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
#include <unordered_map>
#include <vector>
using namespace std;

#define all(a) (a).begin(), (a).end()
#define sz(a) static_cast<int>((a).size())
#define fillchar(a, x) memset(a, x, sizeof(a))
#define rep(i, a, b) for(int i = int(a); i <= int(b); ++i)
#define irep(i, a, b) for(int i = int(a); i >= int(b); --i)
#define replr(i, a, b) rep(i, a, (b)-1)
#define reprl(i, a, b) irep(i, (b)-1, a)
#define repn(i, n) rep(i, 0, (n)-1)
#define irepn(i, n) irep(i, (n)-1, 0)
#define fi first
#define se second
#define pb push_back
#define mp make_pair
typedef long long LL;
typedef pair<LL, LL> PLL;
typedef pair<int, int> PII;
typedef pair<double, double> PDD;
typedef vector<LL> VL;
typedef vector<int> VI;
typedef vector<PII> VPI;
typedef vector<string> VS;
template <class T, class S>
ostream& operator<<(ostream& os, const pair<T, S>& v) {
    return os << "(" << v.first << ", " << v.second << ")";
}
template <class T> ostream& operator<<(ostream& os, const vector<T>& v) {
    os << "[";
    repn(i, sz(v)) {
        if(i) os << ", ";
        os << v[i];
    }
    return os << "]";
}
template <class T> bool setmax(T& _a, T _b) {
    if(_b > _a) {
        _a = _b;
        return true;
    }
    return false;
}
template <class T> bool setmin(T& _a, T _b) {
    if(_b < _a) {
        _a = _b;
        return true;
    }
    return false;
}
template <class T> T gcd(T _a, T _b) { return _b == 0 ? _a : gcd(_b, _a % _b); }

class TwoSat {
public:
    TwoSat(int _n) : n(_n), es(n * 2) {}

    void add_conflict(PII a, PII b) {
        es[a.fi + a.se * n].pb(b.fi + (1 - b.se) * n);
        es[b.fi + b.se * n].pb(a.fi + (1 - a.se) * n);
    }

    // returns r: r = {} if no solution
    //            r[i] = value of variable i otherwise
    VI solve() {
        VI belong(n * 2, -1), dfn(n * 2), low(n * 2), stack;
        int cur = 0, num = 0;
        const function<void(int)> dfs = [&](int x) {
            dfn[x] = low[x] = cur++;
            stack.pb(x);
            belong[x] = -2;
            for(int y : es[x]) {
                if(belong[y] == -1) {
                    dfs(y);
                    setmin(low[x], low[y]);
                } else if(belong[y] == -2) {
                    setmin(low[x], dfn[y]);
                }
            }
            if(low[x] == dfn[x]) {
                while(1) {
                    int y = stack.back();
                    stack.pop_back();
                    belong[y] = num;
                    if(y == x) break;
                }
                ++num;
            }
        };
        repn(i, n * 2) if(belong[i] == -1) dfs(i);

        VI r(n);
        repn(i, n) {
            if(belong[i] == belong[i + n]) {
                return VI();
            }
            r[i] = (belong[i] > belong[i + n]);
        }
        return r;
    }

private:
    const int n;
    vector<VI> es;
};

int main() {
    freopen("binary.in", "r", stdin);
    freopen("binary.out", "w", stdout);

    struct Node {
        Node* child[2] = {nullptr};
        VPI literals;
    } * root;
    root = new Node();

    int n;
    cin >> n;
    unordered_map<string, int> cnt;
    VS strings(n);
    repn(i, n) {
        string s;
        cin >> s;
        strings[i] = s;
        if(++cnt[s] >= 3) {
            printf("NO\n");
            return 0;
        }
        repn(val, 2) {
            Node* x = root;
            for(char ch : s) {
                int cur = (ch == '?' ? val : ch - '0');
                if(!x->child[cur]) {
                    x->child[cur] = new Node();
                }
                x = x->child[cur];
            }
            x->literals.pb(mp(i, val));
        }
    }

    TwoSat sat(n);
    VPI stack;
    const function<void(Node*)> dfs = [&](Node* x) {
        for(PII a : x->literals) {
            for(PII b : stack) {
                sat.add_conflict(a, b);
            }
            stack.pb(a);
        }
        repn(i, 2) if(x->child[i]) { dfs(x->child[i]); }
        repn(i, sz(x->literals)) { stack.pop_back(); }
    };
    dfs(root);

    VI r = sat.solve();
    if(r.empty()) {
        printf("NO\n");
    } else {
        printf("YES\n");
        repn(i, n) {
            auto j = strings[i].find('?');
            if(j != string::npos) {
                strings[i][j] = char('0' + r[i]);
            }
            cout << strings[i] << endl;
        }
    }
    return 0;
}
