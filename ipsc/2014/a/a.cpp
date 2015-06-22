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
#ifdef DEBUG
    #define _debug(args...) { fprintf(stderr, args); fflush(stderr); }
#else
    #define _debug(args...) {}
#endif
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

int main() {
    int csn;
    scanf("%d", &csn);
    repn(cs, csn) {
        char buf[55];
        scanf("%s", buf); string a(buf);
        scanf("%s", buf); string b(buf);

        string ans="";
        size_t k=0;
        while(k<a.size() && k<b.size() && a[k]==b[k])
            ++k;
        string t=b;
        while(t.size()>k) {
            ans+='<'; t.pop_back();
        }
        while(t.size()<a.size()) {
            ans+=a[t.size()]; t+=a[t.size()];
        }
        ans+='*';

        string ans2="*"+a+"*";
        if(ans2.size()<ans.size()) ans=ans2;

        printf("%s\n", ans.c_str());
    }
    return 0;
}
