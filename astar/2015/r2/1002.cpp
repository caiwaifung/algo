#include <algorithm>
#include <iostream>
#include <sstream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <set>
#include <map>
using namespace std;

#define _ (size_t)
#define all(a) a.begin(), a.end()
#define forint(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define forintdown(i, a, b) for(int i=int(a); i>=int(b); --i)
#define forn(i, n) forint(i, 0, (n)-1)
#define forndown(i, n) forintdown(i, (n)-1, 0)
#define fillchar(a, x) memset(a, x, sizeof(a))
#define fi first
#define se second
#define PB push_back
#define MP make_pair
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef pair<int,int> PII;
typedef pair<double,double> PDD;
typedef vector<LL> VL;
typedef vector<int> VI;
typedef vector<PII> VPI;
typedef vector<string> VS;
template<class T> void setmax(T &a, T b) { if(b>a) a=b; }
template<class T> void setmin(T &a, T b) { if(b<a) a=b; }
template<class T> T gcd(T a, T b) { return b==0?a:gcd(b,a%b); }

int a[5555][4], b[5555][4];
int n;

void init() {
    scanf("%d", &n);
    forn(j, 4) {
        a[0][j]=0;
        b[0][j]=j+1;
    }
    forint(i, 1, n) {
        forn(j, 4) scanf("%d%d", &a[i][j],&b[i][j]);
    }
}

int f[5555][266];

int enc(int p[]) {
    int x=0; forn(i, 4) x=x*4+p[i];
    return x;
}
void dec(int x, int p[]) {
    forndown(i, 4) p[i]=x%4, x/=4;
}

int absv(int x) { return x<0?-x:x; }

void solve(int cs) {
    fillchar(f, 50); int maxval=f[0][0];

    int p[4]; forn(i, 4) p[i]=i;
    f[0][enc(p)]=0;

    forint(i, 1, n) forn(x, 256) {
        if(f[i-1][x]==maxval) continue;
        int q[4]; dec(x, q);
        //printf("i=%d x=%d: ",i,x);
        //forn(j, 4) printf("%d ", q[j]); printf("\n");

        forn(j, 4) p[j]=j;
        do {
            bool ok=true;
            forn(j, 3) if(b[i][p[j]]>b[i][p[j+1]])
                ok=false;
            if(!ok) continue;

            int cst=0;
            forn(j, 4) {
                cst+=absv(a[i][p[j]]-a[i-1][q[j]]);
                cst+=absv(b[i][p[j]]-b[i-1][q[j]]);
            }
            /*
            if(cst<20) {
                printf("cst=%d: ",cst);
        forn(j, 4) printf("%d ", p[j]); printf("\n");
            }
            */
            setmin(f[i][enc(p)], f[i-1][x]+cst);
        } while(next_permutation(p, p+4));
    }
    int ans=maxval;
    forn(x, 256) setmin(ans, f[n][x]);

    printf("Case #%d:\n", cs);
    printf("%d\n", ans);
}

int main() {
    int csn; scanf("%d", &csn);
    forint(cs, 1, csn) {
        init();
        solve(cs);
    }
    return 0;
}
