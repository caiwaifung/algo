#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <bitset>
using namespace std;

#define _ (int)
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

const int N=65, M=500010;

bitset<M> a[N];
int n, m;

int solve() {
    rep(i, 1, n) {
        bool found=false;
        rep(i0, i, n) rep(j0, i, m) if(a[i0].test(j0)) {
            found=true;
            swap(a[i], a[i0]);
            rep(i2, 1, n) {
                bool tmp=a[i2][i];
                a[i2][i]=a[i2][j0];
                a[i2][j0]=tmp;
            }
        }
        if(!found) {
            rep(i0, i, n) if(a[i0].any()) return -1;
            return i-1;
        }
        rep(i0, i+1, n) if(a[i0].test(i))
            a[i0]^=a[i];
    }
    return n;
}

int main() {
    cin>>m; n=64;
    static LL num[500010];
    num[0]=0;
    rep(i, 1, m) {
        LL x, y; cin>>x>>y;
        num[0]^=x, num[i]=x^y;
    }
    rep(i, 1, n) a[i].reset();
    rep(j, 0, m) {
        LL x=num[j];
        rep(i, 1, n) {
            if(x&1) a[i].set(j);
            x/=2;
        }
    }

    int r=solve();
    if(r<0) printf("1/1");
    else {
        cout<<(1<<r)-1<<"/"<<(1<<r)<<endl;
    }
    return 0;
}
