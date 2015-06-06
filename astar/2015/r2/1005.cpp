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

const LL MOD=int(1e9)+7;

char buf[100010];
int a[100010], p[100010][26];
int n;

void init() {
    scanf("%s", buf+1);
    n=(int)strlen(buf+1);
    forint(i, 1, n) a[i]=int(buf[i]-'a');
    a[0]=0;

    fillchar(p[0], 0);
    forint(i, 1, n) {
        memmove(p[i], p[i-1], sizeof(p[i]));
        p[i][a[i]]=i;
    }
}

typedef pair<int,LL> St;

St f[100010];

void add(St &a, St b) {
    if(b.fi+1<a.fi)
        a=MP(b.fi+1, 0);
    if(b.fi+1==a.fi)
        (a.se+=b.se)%=MOD;
}

void solve(int cs) {
    LL pow[21];
    pow[0]=1;
    forint(i, 1, 20) pow[i]=pow[i-1]*26%MOD;

    f[0]=MP(1,26);
    forint(i, 1, n) {
        f[i]=MP(9999, 0);
        forn(c, 26) {
            int pp=p[i][c];
            if(pp==0) add(f[i], MP(0, 1));
            else add(f[i], f[pp-1]);
        }
    }

    /*
    fillchar(f, 0);
    forint(i, 1, 20) f[0][i]=pow[i];
    forint(i, 1, n) {
        forint(j, 1, 21) {
            forn(c, 26) {
                int pp=p[i][c];
                if(pp==0)
                    (f[i][j]+=pow[j-1])%=MOD;
                else
                    (f[i][j]+=f[pp-1][j-1])%=MOD;
            }
        }
    }
    */
    int len=f[n].fi, ans=(int)f[n].se;


    printf("Case #%d:\n", cs);
    printf("%d %d\n", len,ans);
}

int main() {
    int csn; scanf("%d", &csn);
    forint(cs, 1, csn) {
        init();
        solve(cs);
    }
    return 0;
}
