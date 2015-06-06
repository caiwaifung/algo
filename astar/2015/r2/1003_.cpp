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

string e[500]; int ex[500], ey[500];
int n, m, s, t;

bool g[50][50];

void init() {
    scanf("%d%d%d%d", &n,&m,&s,&t);
    fillchar(g, false);
    forn(i, m) {
        scanf("%d%d", &ex[i],&ey[i]);
        static char buf[999]; scanf("%s", buf);
        e[i]=string(buf);
        g[ex[i]][ey[i]]=true;
    }
    forn(i, n) g[i][i]=true;
    forn(k, n) forn(i, n) forn(j, n)
        if(g[i][k] && g[k][j])
            g[i][j]=true;
}

string d[50][310];

void solve(int cs) {
    int maxlen=6*n;

    forn(i, n) forint(j, 0, maxlen) d[i][j]="#";
    d[s][0]="";
    forint(j, 0, maxlen) {
        forn(k, m) {
            int i=ex[k], i2=ey[k]; if(d[i][j]=="#") continue;
            int j2=j+(int)e[k].size();
            if(j2<=maxlen) {
                string u=d[i][j]+e[k];
                if(d[i2][j2]=="#" || u<d[i2][j2])
                    d[i2][j2]=u;
            }
        }
    }

    string ans="#";
    forint(j, 0, maxlen) if(d[t][j]!="#") {
        if(ans=="#" || d[t][j]<ans)
            ans=d[t][j];
    }

    bool ok=true;
    forint(j, 0, maxlen) {
        forn(k, m) {
            int i=ex[k], i2=ey[k]; if(d[i][j]=="#") continue;
            if(!g[i2][t]) continue;
            string u=d[i][j]+e[k];
            
            size_t len=min(u.size(), ans.size());
            forn(z, len) {
                if(u[z]<ans[z]) ok=false;
                if(u[z]>ans[z]) break;
            }
        }
    }

    printf("Case #%d:\n", cs);
    //cout<<ans<<endl;

    if(ans=="#" || !ok)
        printf("Tough way!\n");
    else printf("%s\n", ans.c_str());
}

int main() {
    int csn; scanf("%d", &csn);
    forint(cs, 1, csn) {
        init();
        solve(cs);
    }
    return 0;
}
