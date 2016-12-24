#include <algorithm>
#include <unordered_set>
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

const int H=5000;

unordered_set<int> removed[H];
int leftmost[H], rightmost[H];
int center_x[H], center_y[H], total[H];
int h, n;

bool check(int lev) {
    if(lev==h-1) {
        return true;
    }
    LL l=leftmost[lev]*2-n, r=(rightmost[lev]+1)*2-n;
    l*=total[lev+1], r*=total[lev+1];
    if(lev%2==0) {
        return center_x[lev+1]>l && center_x[lev+1]<r;
    } else {
        return center_y[lev+1]>l && center_y[lev+1]<r;
    }
}

bool remove(int lev, int i) {
    removed[lev].insert(i);
    if(sz(removed[lev])==n) {
        return false;
    }
    while(removed[lev].count(leftmost[lev])) {
        ++leftmost[lev];
    }
    while(removed[lev].count(rightmost[lev])) {
        --rightmost[lev];
    }

    int cx=0, cy=0;
    if(lev%2==0) {
        cx=i*2-n+1;
    } else {
        cy=i*2-n+1;
    }
    rep(l, 0, lev) {
        total[l]--;
        center_x[l]-=cx;
        center_y[l]-=cy;
    }

    rep(l, 0, lev) {
        if(!check(l)) {
            return false;
        }
    }
    return true;
}


int main() {
    freopen("jenga.in", "r", stdin);
    freopen("jenga.out", "w", stdout);
    int m;
    scanf("%d%*d%d%d", &n, &h, &m);
    irepn(lev, h) {
        leftmost[lev]=0, rightmost[lev]=n-1;
        center_x[lev]=center_y[lev]=0;
        total[lev]=n*(h-lev);
    }
    repn(op, m) {
        int lev, i;
        scanf("%d%d", &lev, &i);
        --lev, --i;
        if(!remove(lev, i)) {
            printf("yes\n%d\n", op+1);
            return 0;
        }
    }
    printf("no\n");
    return 0;
}
