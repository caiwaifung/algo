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

char a[111][111];
int n, m;

void init() {
    scanf("%d%d",&n,&m);
    fillchar(a, '.');
    forint(i, 1, n) scanf("%s", a[i]+1);
}

const int dx[4]={-1, 0, 1, 0};
const int dy[4]={0, 1, 0, -1};
int b[111][111];

void solve(int cs) {
    printf("Case #%d: ", cs);
    forint(i, 1, n) forint(j, 1, m) {
        b[i][j]=-1;
        if(a[i][j]=='^') b[i][j]=0;
        if(a[i][j]=='>') b[i][j]=1;
        if(a[i][j]=='v') b[i][j]=2;
        if(a[i][j]=='<') b[i][j]=3;
    }
    int ans=0;
    forint(i, 1, n) forint(j, 1, m) if(b[i][j]>=0) {
        bool ok[4]; fillchar(ok, true);
        forn(k, 4) {
            bool out=false;
            for(int x=i, y=j; ; ) {
                x+=dx[k], y+=dy[k];
                if(x<1 || x>n || y<1 || y>m) {
                    out=true; break;
                }
                if(b[x][y]>=0) break;
            }
            if(out) ok[k]=false;
        }
        bool t=false; forn(k, 4) if(ok[k]) t=true;
        if(!t) {
            printf("IMPOSSIBLE\n"); return;
        }
        if(!ok[b[i][j]]) ++ans;
    }
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
