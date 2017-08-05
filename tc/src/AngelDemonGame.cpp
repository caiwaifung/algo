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

template <class T> class CostNet {
public:
    explicit CostNet(int n0) : n(n0 + 2), src(n0), dst(n0 + 1), es(n) {}

    int s() const { return src; }
    int t() const { return dst; }

    void* add(int x, int y, T w, T c) {
        assert(c >= 0);
        Edge *e1, *e2;
        es[x].emplace_back(e1 = new Edge{y, w, c, nullptr});
        es[y].emplace_back(e2 = new Edge{x, 0, -c, nullptr});
        e1->oppo = e2, e2->oppo = e1;
        return static_cast<void*>(e1);
    }

    // Returns (flow, cost).
    pair<T, T> compute(T cost_limit, T len_limit) {
        pair<T, T> ans = {0, 0};
        while(1) {
            vector<T> dis(n, numeric_limits<T>::max());
            vector<T> flow(n);
            vector<Edge*> pre(n);
            dis[src] = 0;
            flow[src] = numeric_limits<T>::max();

            vector<bool> inside(n, false);
            queue<int> que;
            inside[src] = true;
            que.push(src);
            while(!que.empty()) {
                const int x = que.front();
                que.pop();
                for(const auto& e : es[x]) {
                    if(e->w > 0 && setmin(dis[e->y], dis[x] + e->c)) {
                        pre[e->y] = e.get();
                        flow[e->y] = min(flow[x], e->w);
                        if(!inside[e->y]) {
                            inside[e->y] = true;
                            que.push(e->y);
                        }
                    }
                }
                inside[x] = false;
            }
            if(dis[dst] == numeric_limits<T>::max()) {
                return ans;
            }

            if(dis[dst] > len_limit) break;
            T f = flow[dst];
            if(dis[dst] > 0) setmin(f, cost_limit / dis[dst]);
            if(f == 0) break;
            cost_limit -= f * dis[dst];

            ans.fi += f, ans.se += f * dis[dst];
            for(int x = dst; x != src; x = pre[x]->oppo->y) {
                pre[x]->w -= f;
                pre[x]->oppo->w += f;
            }
        }
        return ans;
    }

    T flow(void* e) { return static_cast<Edge*>(e)->oppo->w; }

private:
    struct Edge {
        int y;
        T w, c;
        Edge* oppo;
    };

    const int n, src, dst;
    vector<vector<unique_ptr<Edge>>> es;
};

class AngelDemonGame {
public:
    int max_min_cut(VS G, int add, int len) {
        const int n = sz(G);
        CostNet<int> net(n);
        net.add(net.s(), 0, 1 << 20, 0);
        net.add(n - 1, net.t(), 1 << 20, 0);
        repn(i, n) replr(j, i + 1, n) {
            net.add(i, j, 1, G[i][j] == 'N');
            net.add(j, i, 1, G[i][j] == 'N');
        }
        return net.compute(add, len).fi;
    }

    string winner(vector<string> G, int A, int D) {
        const string sA = "Angel";
        const string sD = "Demon";
        const string sU = "Unknown";
        const int n = sz(G);

        int p = max_min_cut(G, A, 1 << 30);
        int q = max_min_cut(G, 1 << 30, A);
        if(p > D) return sA;
        if(D >= q) return sD;
        return sU;
    }
    // {{{

    // BEGIN CUT HERE
public:
    void run_test(int Case) {
        if((Case == -1) || (Case == 0)) test_case_0();
        if((Case == -1) || (Case == 1)) test_case_1();
        if((Case == -1) || (Case == 2)) test_case_2();
        if((Case == -1) || (Case == 3)) test_case_3();
        if((Case == -1) || (Case == 4)) test_case_4();
        if((Case == -1) || (Case == 5)) test_case_5();
    }

private:
    template <typename T> string print_array(const vector<T>& V) {
        ostringstream os;
        os << "{ ";
        for(typename vector<T>::const_iterator iter = V.begin();
            iter != V.end(); ++iter)
            os << '\"' << *iter << "\",";
        os << " }";
        return os.str();
    }
    void verify_case(int Case, const string& Expected, const string& Received) {
        cerr << "Test Case #" << Case << "...";
        if(Expected == Received)
            cerr << "PASSED" << endl;
        else {
            cerr << "FAILED" << endl;
            cerr << "\tExpected: \"" << Expected << '\"' << endl;
            cerr << "\tReceived: \"" << Received << '\"' << endl;
        }
    }
    void test_case_0() {
        string Arr0[] = {"NYNY", "YNYY", "NYNN", "YYNN"};
        vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arg1 = 2;
        int Arg2 = 2;
        string Arg3 = "Angel";
        verify_case(0, Arg3, winner(Arg0, Arg1, Arg2));
    }
    void test_case_1() {
        string Arr0[] = {"NYNY", "YNYY", "NYNN", "YYNN"};
        vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arg1 = 6;
        int Arg2 = 6;
        string Arg3 = "Demon";
        verify_case(1, Arg3, winner(Arg0, Arg1, Arg2));
    }
    void test_case_2() {
        string Arr0[] = {"NNNN", "NNNN", "NNNN", "NNNN"};
        vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arg1 = 2;
        int Arg2 = 2;
        string Arg3 = "Unknown";
        verify_case(2, Arg3, winner(Arg0, Arg1, Arg2));
    }
    void test_case_3() {
        string Arr0[] = {"NYNNNY", "YNNYNN", "NNNNYN",
                         "NYNNNN", "NNYNNN", "YNNNNN"};
        vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arg1 = 4;
        int Arg2 = 4;
        string Arg3 = "Unknown";
        verify_case(3, Arg3, winner(Arg0, Arg1, Arg2));
    }
    void test_case_4() {
        string Arr0[] = {"NYNNNY", "YNNYNN", "NNNNYN",
                         "NYNNNN", "NNYNNN", "YNNNNN"};
        vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arg1 = 8;
        int Arg2 = 4;
        string Arg3 = "Angel";
        verify_case(4, Arg3, winner(Arg0, Arg1, Arg2));
    }
    void test_case_5() {
        string Arr0[] = {"NYNNNY", "YNNYNN", "NNNNYN",
                         "NYNNNN", "NNYNNN", "YNNNNN"};
        vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arg1 = 4;
        int Arg2 = 8;
        string Arg3 = "Demon";
        verify_case(5, Arg3, winner(Arg0, Arg1, Arg2));
    }

    // END CUT HERE

    // }}}
};

// BEGIN CUT HERE
int main() {
    AngelDemonGame ___test;
    cout << ___test.winner({"NYNN", "YNYY", "NYNN", "NYNN"}, 1, 2) << endl;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
