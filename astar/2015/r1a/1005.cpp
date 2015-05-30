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

VS a;

void init() {
    char s[555]; size_t len;
    while(1) {
        char buf[555]; fgets(buf, 500, stdin);
        string t(buf);
        len=0;
        forn(i, t.size()) if(t[i]!=' ' && t[i]!='\n' && t[i]!='\n') s[len++]=t[i];
        if(len>0) {
            break;
        }
    }
    //scanf("%s", s); size_t len=strlen(s);
    size_t i=0; a.clear();
    while(i<len) {
        size_t j=i+1;
        while(j<len && !(s[j]<='Z'&&s[j]>='A')) ++j;
        string cur(s+i, s+j); a.PB(cur);
        i=j;
    }
}

const int lnk[6][4]={
    {3,4,5,2},
    {3,2,5,4},
    {3,0,5,1},
    {0,2,1,4},
    {1,5,0,3},
    {0,4,1,2}
};

int cub[6][3][3];

void rot2(int i, int j, int tmp[]) {
    if(lnk[j][0]==i) {
        swap(cub[j][0][2], tmp[0]);
        swap(cub[j][0][1], tmp[1]);
        swap(cub[j][0][0], tmp[2]);
    }
    if(lnk[j][2]==i) {
        swap(cub[j][2][0], tmp[0]);
        swap(cub[j][2][1], tmp[1]);
        swap(cub[j][2][2], tmp[2]);
    }
    if(lnk[j][1]==i) {
        swap(cub[j][2][2], tmp[0]);
        swap(cub[j][1][2], tmp[1]);
        swap(cub[j][0][2], tmp[2]);
    }
    if(lnk[j][3]==i) {
        swap(cub[j][0][0], tmp[0]);
        swap(cub[j][1][0], tmp[1]);
        swap(cub[j][2][0], tmp[2]);
    }
}

void rot(int i) {
    int t[3][3];
    forn(x, 3) forn(y, 3) 
        t[y][2-x]=cub[i][x][y];
    forn(x, 3) forn(y, 3) 
        cub[i][x][y]=t[x][y];
    int tmp[3]; fillchar(tmp, 0);
    forn(k, 4) rot2(i, lnk[i][k], tmp);
    rot2(i, lnk[i][0], tmp);
}

void rot(int i, int times) {
    while(times--) rot(i);
}

void go(string c) {
    int x=1, y=2, z=3;
    if(c=="U" ) rot(3, x);
    if(c=="U2") rot(3, y);
    if(c=="U'") rot(3, z);

    if(c=="D" ) rot(5, x);
    if(c=="D2") rot(5, y);
    if(c=="D'") rot(5, z);

    if(c=="R" ) rot(4, x);
    if(c=="R2") rot(4, y);
    if(c=="R'") rot(4, z);

    if(c=="L" ) rot(2, x);
    if(c=="L2") rot(2, y);
    if(c=="L'") rot(2, z);

    if(c=="F" ) rot(0, x);
    if(c=="F2") rot(0, y);
    if(c=="F'") rot(0, z);

    if(c=="B" ) rot(1, x);
    if(c=="B2") rot(1, y);
    if(c=="B'") rot(1, z);
}

int gcd(int a, int b) {
    return b==0 ? a : gcd(b,a%b);
}

bool ok() {
    forn(i, 6) {
        int c=cub[i][1][1];
        forn(x, 3) forn(y, 3) if(cub[i][x][y]!=c) return false;
    }
    return true;
}

void solve() {
    /*
    forn(i, 6) forn(x, 3) forn(y, 3)
        cub[i][x][y]=i;
    int ans=0;
    while(1) {
        ++ans;
        forn(k, a.size()) go(a[k]);
        if(ok()) break;
    }
    */
    static int u[54];
    forn(i, 6) forn(x, 3) forn(y, 3)
        cub[i][x][y]=i*3*3+x*3+y;
    forn(k, a.size()) go(a[k]);
    forn(i, 6) forn(x, 3) forn(y, 3)
        u[cub[i][x][y]]=i*3*3+x*3+y;

    int ans=0; int a[54];
    forn(i, 54) a[i]=i;
    while(1) {
        ++ans; int b[54];
        forn(i, 54) b[u[i]]=a[i];
        forn(i, 54) a[i]=b[i];
        int flag=true;
        forn(i, 54) if(a[i]!=i) flag=false;
        if(flag) break;
    }

    /*
    int ans=1;
    forn(i, 54) {
        int len=1;
        for(int j=u[i]; j!=i; j=u[j])
            ++len;
        ans=ans*len/gcd(ans, len);
    }
    */

    printf("%d\n", ans);
}

int main() {
    /*
    forn(i, 6) forn(x, 3) forn(y, 3) cub[i][x][y]=i;
    rot(0);
    forn(i, 6) {
        printf("face %d:\n", i);
        forn(x, 3) forn(y, 3) printf("%d%c",cub[i][x][y],y<2?' ':'\n');
    }
    */
    //forn(i, 3) forn(j, 4) cub[0][i][j]=rand()%10; rot(0);
    int cs=0, csn; scanf("%d", &csn); 
    while(csn--) {
        init();
        printf("Case #%d:\n", ++cs);
        solve();
    }
    return 0;
}
