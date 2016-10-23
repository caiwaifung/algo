// 10:24 - 10:48 - wa
#include <algorithm>
#include <cassert>
#include <cmath>
#include <map>
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

const int N=100;
const int M=N*N*2;
const LL P=911;
const LL MOD=LL(1e9)+7;

VI es[N];
int n, m, rev[M];

void init() {
    static int e[N][N];
    fillchar(e, 0xff);
    scanf("%d", &n), m=0;
    repn(i, n) {
        int k; scanf("%d", &k);
        while(k--) {
            int j; scanf("%d", &j);
            --j;
            e[i][j]=m++;
            es[i].pb(e[i][j]);
        }
    }
    repn(i, n) repn(j, n) if(e[i][j]>=0) {
        rev[e[i][j]]=e[j][i];
    }
}

void cal_labels(const VI& old_labels, VI* labels) {
    repn(i, n) {
        LL cur=0, p=1;
        for(int e: es[i]) {
            cur=(cur*P+old_labels[e])%MOD;
            p=(p*P)%MOD;
        }
        for(int e: es[i]) {
            cur=(cur*P-old_labels[e]*p)%MOD;
            if(cur<0) cur+=MOD;
            (*labels)[rev[e]]=int(cur);
            cur=(cur+old_labels[e])%MOD;
        }
    }
}

void output(const VI& labels) {
    map<LL, VI> rooms_by_hash;
    repn(i, n) {
        LL r=1LL<<60;
        repn(k, sz(es[i])) {
            LL cur=0;
            repn(k2, sz(es[i])) cur=(cur*9871+labels[es[i][(k+k2)%sz(es[i])]])%(LL(1e9)+21);
            setmin(r, cur);
        }
        rooms_by_hash[r].pb(i);
    }
    vector<VI> groups;
    for(const auto& kv: rooms_by_hash) {
        groups.pb(kv.se);
    }
    sort(all(groups));
    bool any=false;
    for(const auto& group: groups) {
        if(sz(group)==1) continue;
        for(int i: group) printf("%d ", i+1);
        printf("\n");
        any=true;
    }
    if(!any) printf("none\n");
}

int main() {
    init();
    VI labels(m), tmp(m);
    repn(iter, m+1) {
        cal_labels(labels, &tmp);
        swap(labels, tmp);
        for(int& x: labels) x^=123456789;
    }
    output(labels);

    return 0;
}
