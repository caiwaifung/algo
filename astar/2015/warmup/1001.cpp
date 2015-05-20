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


// ------------------------ template ends here ------------------------ //

int main() {
    int n, m;
    while(scanf("%d%d", &n,&m)==2) {
        static bool g[111][111];
        fillchar(g, false);
        while(m--) { int a, b; scanf("%d%d", &a,&b); g[a][b]=true;}
        forint(k, 1, n) forint(i, 1, n) forint(j, 1, n) g[i][j]|=(g[i][k]&&g[k][j]);
        bool flag=true;
        forint(i, 1, n) forint(j, 1, n) if(g[i][j]&&g[j][i]) flag=false;
        printf("%s\n", flag?"YES":"NO");
    }
    return 0;
}
