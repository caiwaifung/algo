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
VI es[50];
int n, m, s, t;
bool g[50][50];

void init() {
    scanf("%d%d%d%d", &n,&m,&s,&t);
    fillchar(g, false);
    forn(i, n) es[i].clear();
    forn(i, m) {
        scanf("%d%d", &ex[i],&ey[i]);
        static char buf[999]; scanf("%s", buf);
        e[i]=string(buf);
        g[ex[i]][ey[i]]=true;
        es[ex[i]].PB(i);
    }
    forn(i, n) g[i][i]=true;
    forn(k, n) forn(i, n) forn(j, n)
        if(g[i][k] && g[k][j])
            g[i][j]=true;
}

char ans[310];
int anslen, maxlen;
set<int> d[310];

void upt(int i, string &s, int y) {
    int la=0;
    forn(k, s.size()) {
        la=i+k;
        if(la>maxlen)
            return;
        if(anslen<la) {
            anslen=la;
            ans[anslen]=s[k];
        }
        if(ans[la]<s[k])
            return;
        if(ans[la]>s[k]) {
            anslen=la;
            ans[anslen]=s[k];
            forint(j, la, 309) d[j].clear();
        }
    }
    d[la].insert(y);
}

void solve(int cs) {
    maxlen=n*6+1;
    int mlen=999;

    anslen=0;
    forint(i, 0, maxlen) d[i].clear();
    d[0].insert(s);

    forint(i, 0, maxlen-1) {
        VI vec(all(d[i]));
        forn(k, vec.size()) {
            int x=vec[k];
            if(x==t) {
                mlen=i; break;
            }

            forn(k2, es[x].size()) {
                int ei=es[x][k2], y=ey[ei];
                if(!g[y][t]) continue;
                upt(i+1, e[ei], y);
            }
        }
        if(mlen<=maxlen) break;
    }

    printf("Case #%d:\n", cs);

    if(mlen<=maxlen) {
        ans[mlen+1]='\0';
        printf("%s\n", ans+1);
    }
    else
        printf("Tough way!\n");
}

int main() {
    int csn; scanf("%d", &csn);
    forint(cs, 1, csn) {
        init();
        solve(cs);
    }
    return 0;
}
