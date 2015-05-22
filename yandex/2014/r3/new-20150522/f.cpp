// accepted: 2015.05.22
// why this method correct?
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

bool ok[7070][7070];

void go(int len) {
    const int MAXV=8300;
    static int f[7070];
    static bool v[MAXV];
    fillchar(v, false);
    fillchar(f, 0);
    forint(n, len, 7000) {
        forint(i, 0, n-len) {
            assert((f[i]^f[n-len-i])<MAXV-10);
            v[f[i]^f[n-len-i]]=true;
        }
        f[n]=0; while(v[f[n]]) ++f[n];
        forint(i, 0, n-len) {
            v[f[i]^f[n-len-i]]=false;
        }
    }
    forint(n, 0, 7000) ok[n][len]=(f[n]>0);
}

VPI laws; // for all L: not ok iff N=aL+b, for some (a,b) in laws
    // made from L=1 and L=2

void make() {
    VI a1, a2;
    forint(n, 17, 7000) if(!ok[n][17]) a1.PB(n);
    forint(n, 18, 7000) if(!ok[n][18]) a2.PB(n);
    a1.resize(a2.size());
    forn(i, a1.size()) {
        int a=a2[i]-a1[i];
        int b=a1[i]-a*17;
        laws.PB(MP(a, b));
        //if(i<10) printf("%d %d\n",a,b); 
    }
}

/*
bool t(int N, int L) {
    if(N == L * 2 + L - 1) return true;
    if(N == L * 4 + L - 1) return true;
    if(N == L * 8 + L - 3) return true;
    if(N == L * 12 + L - 5) return true;
    if(N == L * 16 + L - 5) return true;
    if(N == L * 20 + L - 7) return true;
    if(N == L * 20 + L - 7) return true;
    if(N == L * 28 + L - 9) return true;
    if(N == L * 32 + L - 11) return true;
    if(N == L * 40 + L - 11) return true;
    if(N == L * 48 + L - 13) return true;
    if(N == L * 64 + L - 19) return true;
    if(N == L * 68 + L - 19) return true;
    return false;
}

void check(int len) {
    static bool v[7070];
    fillchar(v, true);
    for(auto x: laws) {
        int n=x.fi*len+x.se;
        if(n<=7000) v[n]=false;
    }

    bool flag=true;
    forint(n, len, 7000) if(v[n]!=ok[n][len]) {
        flag=false;
        //printf("n=%d t=%d v=%d\n",n,t(n,len),v[n]);
        printf("n=%d\n",n);
    }
    printf("%d: %s\n", len, flag?"ok":"err");
    if(!flag) for(;;);
}
*/

void compute() {
    forint(len, 1, 18) go(len);
    make();
    forint(len, 19, 7000) {
        forint(n, 0, len-1) ok[n][len]=false;
        forint(n, len, 7000) ok[n][len]=true;
        for(auto x: laws) {
            int n=x.fi*len+x.se;
            if(n<=7000) ok[n][len]=false;
        }
    }

    //forint(len, 18, 50) check(len);
}

int main() {
    compute();

    int n; scanf("%d", &n);
    forint(i, 1, n)
        printf("%s", ok[n][i]?"F":"S");
    printf("\n");
    return 0;
}
