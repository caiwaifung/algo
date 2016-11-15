// 7:10 - 7:29
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

const int N=10000;
const double W=100;
const double PI=acos(-1);

double pos[N], radius[N], volume[N];
int n, s;

double partial(double x0) {
    const auto f=[](double x) {
        return 3./4.*(x-x*x*x/3);
    };
    return f(x0)-f(-1);
}

double calc(double p) {
    double ans=W*W*p;
    repn(i, n) {
        if(pos[i]+radius[i]<p) {
            ans-=volume[i];
            continue;
        }
        if(p<pos[i]-radius[i]) {
            continue;
        }
        ans-=volume[i]*partial((p-pos[i])/radius[i]);
    }
    return ans;
}

int main() {
    scanf("%d%d", &n,&s);
    repn(i, n) {
        int r, x, y, z;
        scanf("%d%d%d%d", &r,&x,&y,&z);
        pos[i]=double(z)/1000;
        radius[i]=double(r)/1000;
        volume[i]=4./3.*PI*radius[i]*radius[i]*radius[i];
    }
    double tot=calc(W);
    vector<double> ans;
    rep(i, 1, s) {
        double goal=tot/s*i;
        double le=0, ri=W;
        repn(tt, 70) {
            double mid=(le+ri)/2;
            if(calc(mid)<goal) {
                le=mid;
            } else {
                ri=mid;
            }
        }
        ans.pb(le);
    }
    repn(i, s) {
        double thickness=ans[i]-(i>0?ans[i-1]:0);
        printf("%.9lf\n", thickness);
    }

    return 0;
}
