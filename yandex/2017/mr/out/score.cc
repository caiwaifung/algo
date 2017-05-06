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
typedef vector<string> VS;
typedef vector<PII> VPI;
typedef vector<PLL> VPL;
template <class T, class S> ostream& operator<<(ostream& os, const pair<T, S>& v) { return os << "(" << v.first << ", " << v.second << ")"; }
template <class T> ostream& operator<<(ostream& os, const vector<T>& v) { os << "["; repn(i, sz(v)) { if(i) os << ", "; os << v[i]; } return os << "]"; }
template <class T> bool setmax(T& _a, T _b) { if(_a < _b) { _a = _b; return true; } return false; }
template <class T> bool setmin(T& _a, T _b) { if(_b < _a) { _a = _b; return true; } return false; }
template <class T> T gcd(T _a, T _b) { return _b == 0 ? _a : gcd(_b, _a % _b); }
inline LL powmod(LL a, LL b, LL m) { LL r = 1; for(; b > 0; b >>= 1, a = a * a % m) { if(b & 1) r = r * a % m; } return r; }
// clang-format on
// }}}

int sqr(int x) { return x * x; }

double score(string case_name) {
    FILE* f = fopen(("in/" + case_name + ".in").c_str(), "r");
    int n, m, k;
    fscanf(f, "%d%d%d", &n, &m, &k);
    static int occupied[99][99];
    fillchar(occupied, -1);
    repn(i, k * 2) {
        int x, y;
        fscanf(f, "%d%d", &x, &y);
        occupied[x][y] = (i < k ? 1 : 2);
    }
    fclose(f);

    static char s[99][99];
    f = fopen(("out/" + case_name + ".out").c_str(), "r");
    repn(i, n) fscanf(f, "%s", s[i]);
    fclose(f);

    f = fopen(("out/" + case_name + "_demo.ppm").c_str(), "w");
    const int W = 20, R = 7;
    static int color_r[999], color_g[999], color_b[999];
    repn(c, 333) {
        color_r[c] = rand() % 256;
        color_g[c] = rand() % 256;
        color_b[c] = rand() % 256;
    }
    fprintf(f, "P3\n%d %d\n255\n", m * W, n * W);
    repn(x, n * W) {
        repn(y, m * W) {
            int i = x / W, j = y / W;
            int r = color_r[(int)s[i][j]], g = color_g[(int)s[i][j]],
                b = color_b[(int)s[i][j]];
            if(occupied[i][j] > 0 &&
               sqr(abs(x % W - W / 2)) + sqr(abs(y % W - W / 2)) < R * R) {
                if(occupied[i][j] == 1) {
                    r = 255, g = 0, b = 0;
                } else {
                    r = 0, g = 0, b = 255;
                }
            }
            if(x % W == 0 || y % W == 0) r = g = b = 150;
            fprintf(f, "%d %d %d ", r, g, b);
        }
        fprintf(f, "\n");
    }
    fclose(f);

    bool error = false;
    static bool vis[99][99];
    static bool vis_color[333];
    fillchar(vis, false);
    fillchar(vis_color, false);
    double sum = 0, sumc = 0;
    repn(sx, n) repn(sy, m) if(!vis[sx][sy]) {
        int cnt = 0, edges = 0;
        queue<PII> que;
        int color = s[sx][sy], o1 = 0, o2 = 0;
        if(vis_color[color]) {
            printf("%s: error: color %c not connected\n", case_name.c_str(),
                   char(color));
            printf("  start: %d,%d\n", sx, sy);
            error = true;
        } else {
            vis_color[color] = true;
        }
        vis[sx][sy] = true, que.push({sx, sy});
        while(!que.empty()) {
            const auto p = que.front();
            if(occupied[p.fi][p.se] == 1) ++o1;
            if(occupied[p.fi][p.se] == 2) ++o2;
            que.pop();
            ++cnt;
            static const int dx[4] = {0, 1, 0, -1};
            static const int dy[4] = {1, 0, -1, 0};
            repn(i, 4) {
                int x = p.fi + dx[i], y = p.se + dy[i];
                if(x < 0 || x >= n || y < 0 || y >= m ||
                   int(s[x][y]) != color) {
                    ++edges;
                } else {
                    if(!vis[x][y]) {
                        vis[x][y] = true, que.push({x, y});
                    }
                }
            }
        }
        if(o1 != 1 || o2 != 1) {
            printf("%s: error: color %c has !=1 life/magic (%d %d)\n",
                   case_name.c_str(), char(color), o1, o2);
            printf("  start: %d,%d\n", sx, sy);
            rep(o, 1, 2) repn(i, n) repn(j, m) {
                if(s[i][j] == color && occupied[i][j] == o) {
                    printf("  o%d: %d,%d\n", o, i, j);
                }
            }
            error = true;
        }
        if(edges == 0) {
            printf("bad: cnt=%d color=%c\n", cnt, color);
            exit(0);
        }
        sum += double(cnt) / double(edges) / double(edges);
        sumc += 1;
    }
    double ans = sum / sumc * 160000;
    printf("%s: %.1lf  | n=%d m=%d k=%d\n", case_name.c_str(), ans, n, m, k);
    if(error) {
        printf("  config: %d %d k=%d\n", n, m, k);
        printf("STOP\n");
        exit(0);
    }
    return ans;
}

int main(int argc, char* argv[]) {
    VS cases;
    if(argc > 1) {
        replr(i, 1, argc) cases.pb(argv[i]);
    } else {
        repn(i, 20) cases.pb(to_string(i));
    }

    double ans = 0, ansc = 0;
    for(const auto& s : cases) {
        double cur = score(s);
        if(cur < 0) {
            printf("ERROR!\n");
            return 0;
        }
        ans += cur;
        ansc += 1;
    }
    printf("Overall: %.2lf\n", ans / ansc);
    return 0;
}
