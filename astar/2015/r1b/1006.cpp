#include <algorithm>
#include <bitset>
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

typedef bitset<266> Var;
//typedef bitset<11> Var;

Var a[266][266];
int badx[266], bady[266];
int n, m, k;

void init() {
    scanf("%d%d%d", &n,&m,&k);

    forint(i, 1, n) {
        static char buf[266];
        scanf("%s", buf+1);
        forint(j, 1, m) {
            a[i][j].reset();
            if(buf[j]=='B')
                a[i][j].set(0);
        }
    }
    forint(i, 1, k)
        scanf("%d%d", &badx[i], &bady[i]);
}

Var x[266][266], y[266][266];

struct Gauss {
    Var a[999];
    int n, m;
    void init(int _m) {
        m=_m; n=0;
    }
    void add(Var x) {
        a[++n]=x;
    }
    bool ok() {
        //forint(i, 1, n) cout<<a[i]<<endl; cout<<endl;
        forint(i, 1, n) {
            bool found=false;
            forint(j2, i, m) {
                int i2=i; while(i2<=n && !a[i2][j2]) ++i2;
                if(i2>n) continue;
                if(i2!=i) {
                    swap(a[i2], a[i]);
                }
                if(j2!=i) {
                    forint(k, 1, n) {
                        int t=a[k][i];
                        a[k][i]=a[k][j2];
                        a[k][j2]=t;
                    }
                }
                found=true;
                break;
            }
            if(!found) {
                forint(i2, i, n)
                    if(a[i2][0]) 
                        return false;
                return true;
            }
            assert(a[i][i]);
            forint(i2, i+1, n) if(a[i2][i])
                a[i2]^=a[i];
        }
        //forint(i, 1, n) cout<<a[i]<<endl; cout<<endl;
        //assert(false);
        return true;
    }
};

void solve(int cs) {
    x[1][0].reset(), x[1][m+1].reset();
    forint(j, 1, m) {
        x[1][j].reset(), x[1][j].set(j);
    }
    forint(j, 1, m) y[1][j]=x[1][j]^x[1][j-1]^x[1][j+1];

    forint(i, 2, n) {
        x[i][0].reset(), x[i][m+1].reset();
        forint(j, 1, m)
            x[i][j]=y[i-1][j]^a[i-1][j];
        forint(j, 1, m)
            y[i][j]=x[i][j]^x[i-1][j]^x[i][j-1]^x[i][j+1];
    }

    static Gauss gauss;
    gauss.init(m);
    forint(i, 1, k)
        gauss.add(x[badx[i]][bady[i]]);
    forint(j, 1, m)
        gauss.add(y[n][j]^a[n][j]);
    bool ok=gauss.ok();

    printf("Case #%d:\n", cs);
    printf("%s\n", ok?"YES":"NO");
}

int main() {
    int csn; scanf("%d", &csn);
    forint(cs, 1, csn) {
        init();
        solve(cs);
    }
    return 0;
}
