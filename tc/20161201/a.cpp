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

class VampireTree {
public:
    int maxDistance(VI num) {
        int n=(int)num.size();
        int ans=-1;
        repn(s, 1<<n) {
            int ones=0, len=-1;
            repn(i, n) if(s&(1<<i)) { ++len; if(num[i]==1) ++ones; }
            if(ones!=2) continue;
            int stubs=0;
            VI rs;
            repn(i, n) if(s&(1<<i)) {
                int x=max(0, num[i]-2);
                stubs+=x;
            } else {
                rs.pb(num[i]);
            }
            sort(all(rs));
            bool ok=true;
            irepn(i, rs.size()) {
                if(stubs==0) { ok=false; break; }
                --stubs;
                stubs+=rs[i]-1;
            }
            if(stubs!=0) ok=false;

            if(ok) setmax(ans, len);
        }
        return ans;
    }
};

