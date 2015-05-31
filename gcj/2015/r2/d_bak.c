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

const LL MOD=LL(1e9)+7;
LL inv(LL x) {
    LL y=MOD-2, ans=1;
    for(; y>0; y>>=1, x=x*x%MOD)
        if(y&1) ans=ans*x%MOD;
    return ans;
}

LL go(int n, int m) {
    int b[10], p[10];
    forn(i, 10) {
        b[i]=1<<i;
        p[i]=1<<(i*2);
    }

    LL f[2][1<<7][1<<12];
    int o1=0, o2=1;
    fillchar(f, 0);
    f[o1][0][0]=1;
    forint(i, 1, n) {
        forint(j, 1, m) {
            fillchar(f[o2], 0);
            forn(s1, 1<<(m+1)) forn(s2, 1<<(m*2)) if(f[o1][s1][s2]) {
                LL fval=f[o1][s1][s2];
                int ok[4]; fillchar(ok, true);
                int t1=s1, t2=s2;
                int lnks=0;
                {
                    int x=(s2>>((j-2)*2))&3;
                    t2-=(x<<((j-2)*2));
                    if(s1|b[j-1]) {
                        t1-=b[j-1];
                        forint(k, 1, 3) if(k!=x) ok[k]=false;
                        ++lnks;
                    } else
                        ok[x]=false;
                }
                {
                    int x=(s2>>((j-1)*2))&3;
                    t2-=(x<<((j-1)*2));
                    if(s1|b[j]) {
                        t1-=b[j];
                        forint(k, 1, 3) if(k!=x) ok[k]=false;
                        ++lnks;
                    } else
                        ok[x]=false;
                }
                forint(cur, 1, 3) if(ok[cur]) {
                    int want=cur-lnks;
                    if(want<0 || want>2) continue;
                    int t2x=t2^(cur*p[j-1])^(cur*
                    if(want==0) {
                        f[o2][t1][t2^
                    }
                }
            }
            swap(o1, o2);
        }
        // TODO
    }

}

LL ans[111][111];
void pre() {
    LL x[111][111];
    forint(i, 1, 6) forint(j, 1, 6) 
        x[i][j]=go(i, j);
    forint(i, 1, 6) forint(j, 1, 6) {
        LL s=0;
        forint(k, 1, j) s+=x[i][gcd(k,j)];
        s=(s*inv(j))%MOD;
        ans[i][j]=s;
    }
}

void solve(int cs) {
    int n, m; scanf("%d%d", &n,&m);
    printf("Case #%d: ", cs);
    printf("%d\n", (int)ans[n][m]);
}

int main() {
    pre();
    int csn; scanf("%d", &csn);
    forint(cs, 1, csn) {
        solve(cs);
    }
    return 0;
}
