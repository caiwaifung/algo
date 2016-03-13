#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <functional>
#include <set>
#include <map>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

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
#ifdef DEBUG
    #define _debug(args...) { fprintf(stderr, args); fflush(stderr); }
#else
    #define _debug(args...) {}
#endif
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

struct Cell {
    int v, g;
    int ans;
    Cell() : v(0), g(0) {}
};
struct Group {
    int v;
    unordered_set<int> is, js;
    int cnt; // unfinished rows & cols
    int ans;
};
struct Row {
    unordered_map<int, unordered_set<int>> v2js;
    unordered_map<int, int> v2g;
    set<int> vs;
    unordered_set<int> visited_vs;
};
struct Col {
    unordered_map<int, unordered_set<int>> v2is;
    unordered_map<int, int> v2g;
    set<int> vs;
    unordered_set<int> visited_vs;
};
vector<vector<Cell>> a;
vector<Group> g;
vector<Row> rows;
vector<Col> cols;
int n, m, num;

void init() {
    scanf("%d%d", &n,&m);
    a.resize(n+1, vector<Cell>(m+1));
    rows.resize(n+1);
    cols.resize(m+1);
    
    rep(i, 1, n) rep(j, 1, m) {
        int v; scanf("%d", &v);
        a[i][j].v=v;
        rows[i].v2js[v].insert(j);
        cols[j].v2is[v].insert(i);
    }
    num=0;
    function<void(int, int)> dfs = [&](int i, int j) {
        if(a[i][j].g>0) return;
        a[i][j].g=num;
        int v=a[i][j].v;
        if(rows[i].visited_vs.count(v)==0) {
            rows[i].visited_vs.insert(v);
            for(int y: rows[i].v2js[v]) dfs(i, y);
        }
        if(cols[j].visited_vs.count(v)==0) {
            cols[j].visited_vs.insert(v);
            for(int x: cols[j].v2is[v]) dfs(x, j);
        }
    };
    rep(i, 1, n) rep(j, 1, m) if(a[i][j].g==0) {
        ++num; dfs(i, j); 
    }
    rep(i, 1, n) rep(j, 1, m) {
        rows[i].v2g[a[i][j].v]=a[i][j].g;
        cols[j].v2g[a[i][j].v]=a[i][j].g;
    }

    g.resize(num+1);
    rep(i, 1, n) rep(j, 1, m) {
        int k=a[i][j].g;
        g[k].v=a[i][j].v;
        g[k].is.insert(i);
        g[k].js.insert(j);
    }
}

vector<int> que;
int ss, tt, ans;

void decrease_cnt(int k) {
    assert(--g[k].cnt>=0);
    if(g[k].cnt==0) {
        g[k].ans=ans; que[++tt]=k;
    }
}

void finish_row(int i, int val) {
    assert(*rows[i].vs.begin()==val);
    rows[i].vs.erase(val);
    if(!rows[i].vs.empty()) {
        int v=*rows[i].vs.begin();
        int k=rows[i].v2g[v];
        decrease_cnt(k);
    }
}
void finish_col(int j, int val) {
    assert(*cols[j].vs.begin()==val);
    cols[j].vs.erase(val);
    if(!cols[j].vs.empty()) {
        int v=*cols[j].vs.begin();
        int k=cols[j].v2g[v];
        decrease_cnt(k);
    }
}

void finish(int k) {
    for(int i: g[k].is) finish_row(i, g[k].v);
    for(int j: g[k].js) finish_col(j, g[k].v);
}

void solve() {
    rep(i, 1, n) rep(j, 1, m) {
        rows[i].vs.insert(a[i][j].v);
        cols[j].vs.insert(a[i][j].v);
    }
    rep(k, 1, num) {
        g[k].cnt=0;
        for(int i: g[k].is) if(*rows[i].vs.begin()<g[k].v) ++g[k].cnt;
        for(int j: g[k].js) if(*cols[j].vs.begin()<g[k].v) ++g[k].cnt;
        g[k].ans=-1;
    }

    que.resize(num+1);
    ss=0, tt=0; ans=1;
    rep(k, 1, num) if(g[k].cnt==0) que[++tt]=k, g[k].ans=ans;
    while(ss<tt) {
        ++ans;
        int tt_holder=tt;
        while(ss<tt_holder) {
            int k=que[++ss];
            finish(k);
        }
    }

    rep(i, 1, n) {
        rep(j, 1, m) {
            a[i][j].ans=g[a[i][j].g].ans;
            printf("%d ", a[i][j].ans);
        }
        printf("\n");
    }
}

int main() {
    init();
    solve();
    return 0;
}
