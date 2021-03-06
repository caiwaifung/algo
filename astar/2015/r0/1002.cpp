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

char s[100010], t[100010];
int n, rows, cols;

int main() {
    int cs; scanf("%d", &cs);
    forint(fcs, 1, cs) {
        gets(s);
        gets(s); n=(int)strlen(s);
        scanf("%d", &cols);
        rows=(n-1)/cols+1;
        forn(i, n) {
            int x=i/cols, y=i%cols;
            int j=0;
            int k=(n-1)%cols+1;
            if(y<=k) {
                j=y*rows+x;
            }
            else {
                j=k*rows+(y-k)*(rows-1)+x;
            }
            t[i]=s[j];
        }
        t[n]='\0';

        printf("Case #%d:\n%s\n",fcs,t);
    }
    return 0;
}
