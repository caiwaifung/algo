#include <cassert>
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

const int N=200010;

LL branches[N], tot[N];
int next_fork[N];
int n;

int query_dep(int i, LL x) {
    if(x==1) return 0;
    if(branches[i]>1) {
        --x;
        x=(x-1)%tot[i-1]+1;
        return query_dep(i-1, x)+1;
    } else {
        int to_skip=(int)min(x-1, LL(i-next_fork[i]));
        return query_dep(i-to_skip, x-to_skip)+to_skip;
    }
}

int query_dis(int i, LL x, LL y) {
    if(x==1) return query_dep(i, y);
    if(branches[i]>1) {
        x--, y--;
        LL bx=(x-1)/tot[i-1]; x-=bx*tot[i-1];
        LL by=(y-1)/tot[i-1]; y-=by*tot[i-1];
        if(bx==by) {
            return query_dis(i-1, x, y);
        } else {
            return query_dep(i-1, x)+query_dep(i-1, y)+2;
        }
    } else {
        int to_skip=(int)min(x-1, LL(i-next_fork[i]));
        return query_dis(i-to_skip, x-to_skip, y-to_skip);
    }
}

int main() {
    n=1;
    branches[1]=0;
    tot[1]=1;
    next_fork[1]=0;

    int m; scanf("%d", &m);
    while(m--) {
        char op[3]; scanf("%s", op);
        if(op[0]=='+') {
            int k; scanf("%d", &k);
            branches[n+1]=k;
            tot[n+1]=1+tot[n]*k;
            next_fork[n+1]=(k>1?n+1:next_fork[n]);
            ++n;
        } else {
            LL x, y; cin>>x>>y;
            if(x>y) swap(x, y);
            int d=query_dis(n, x, y);
            printf("%d\n", d);
        }
    }
    return 0;
}
