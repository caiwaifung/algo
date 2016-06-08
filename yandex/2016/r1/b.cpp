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

int b[3][3];

bool dfs(int x, int y, int cur) {
    if(cur>9) {
        repn(i, 3) {
            repn(j, 3) printf("%d", b[i][j]);
            printf("\n");
        }
        return true;
    }
    if(b[x][y]>0 && b[x][y]!=cur) return false;
    int old=b[x][y]; b[x][y]=cur;
    for(PII dir: vector<PII>{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}) {
        int x0=x+dir.fi, y0=y+dir.se;
        if(x0>=0 && x0<3 && y0>=0 && y0<3) {
            if(dfs(x0, y0, cur+1)) return true;
        }
    }
    b[x][y]=old; return false;
}

int main() {
    repn(i, 3) {
        char s[99]; scanf("%s", s);
        repn(j, 3) {
            if(s[j]=='?') b[i][j]=-1;
            else b[i][j]=int(s[j]-'0');
        }
    }
    dfs(1, 1, 1);
    return 0;
}
