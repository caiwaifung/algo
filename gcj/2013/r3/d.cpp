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

char st[55];
int n;

void init() {
    scanf("%s", st);
    n=(int)strlen(st);
}

double f[1<<20], p[1<<20];

void solve(int cs) {
    int full=(1<<n)-1;
    int cur=0;
    forn(i, n) if(st[i]=='X') cur|=(1<<i);
    
    double ans=0;
    fillchar(p, 0);
    p[cur]=1;
    forn(s, full) {
        if(p[s]==0) continue;
        forn(i, n) {
            int b=1<<i, c=n;
            while(s&b) {
                b<<=1; if(b>full) b=1;
                --c;
            }
            ans+=p[s]/double(n)*double(c);
            p[s|b]+=p[s]/double(n);
            //f[s|b]+=f[s]/double(n)+p[s]*double(c)/double(n);
        }
    }
    /*
    if(cs==1) {
        forint(s,1,full) printf("p[%d]=%.4lf\n",s,p[s]);
    }
    */


    printf("Case #%d: ", cs);
    //printf("%.15lf\n", f[full]);
    printf("%.15lf\n", ans);
}

int main() {
    freopen("d.out","w",stdout);
    int csn; scanf("%d", &csn);
    forint(cs, 1, csn) {
    fprintf(stderr,"%d/%d\n",cs,csn);
        init();
        solve(cs);
    }
    return 0;
}
