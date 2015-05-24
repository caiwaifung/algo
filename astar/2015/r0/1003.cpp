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

unsigned parse(string s) {
    s+='.';
    //printf("-->Parse %s:\n", s.c_str());
    unsigned ans=0;
    forn(i, 4) {
        size_t k=s.find('.');
        string t=s.substr(0, k);
        s=s.substr(k+1);
        int c=0;
        forn(i, t.size()) c=c*10+int(t[i]-'0');
        //printf("-->   %d\n",c);
        ans=(ans<<8)|c;
    }
    //printf("-->ret=%u\n",ans);
    return ans;
}

int main() {
    int ncs; scanf("%d", &ncs);
    forint(cs, 1, ncs) {
        int n, m; scanf("%d%d", &n,&m);
        unsigned ip[1010], mask[55];
        char buf[99];
        forint(i, 1, n) {
            scanf("%s", buf); ip[i]=parse(string(buf));
        }
        forint(i, 1, m) {
            scanf("%s", buf); mask[i]=parse(string(buf));
        }
        printf("Case #%d:\n", cs);
        forint(i, 1, m) {
            vector<unsigned> tmp;
            forint(j, 1, n) tmp.PB(ip[j]&mask[i]);
            sort(all(tmp));
            //for(auto t: tmp) printf("-->%d\n", t);
            tmp.erase(unique(all(tmp)), tmp.end());
            int ans=(int)tmp.size();
            printf("%d\n", ans);
        }
    }
    return 0;
}
