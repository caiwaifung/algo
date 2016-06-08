#include <cassert>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define sz(a) static_cast<int>(a.size())
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

const int points[31]={0,
    100, 75, 60, 50, 45, 40, 36, 32, 29, 26, 24, 22, 20, 18, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

bool used[31];
int a[10];

int go() {
    VI x, y;
    repn(i, 10) x.pb(a[i]);
    rep(i, 1, 11) if(!used[i]) y.pb(points[i]);
    y.resize(10);
    sort(all(x));
    sort(all(y)); reverse(all(y));
    int ans=1<<30;
    repn(i, 10) setmin(ans, x[i]+y[i]);
    return ans;
}

int main() {
    repn(i, 10) scanf("%d", &a[i]);
    fillchar(used, false);
    int ans=0;
    repn(i, 31) {
        used[i]=true;
        int tmp=go();
        used[i]=false;
        //printf("i=%d tmp=%d p=%d\n",i,tmp,points[i]);
        if(tmp>=points[i]) continue;
        setmax(ans, i==0?1000:i);
    }
    printf("%d\n", ans);

    return 0;
}
