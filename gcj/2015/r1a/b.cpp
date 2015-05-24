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

int main() {
    int ncs; scanf("%d", &ncs);
    forint(cs, 1, ncs) {
        int n, k; scanf("%d%d", &n,&k);
        int t[1010]; forint(i, 1, n) scanf("%d", t+i);
        LL le=0, ri=1LL<<50;
        while(le<ri) {
            LL mid=(le+ri)/2;
            LL cnt=0;
            forint(i, 1, n) cnt+=mid/t[i];
            if(cnt+n<k) le=mid+1;
                else ri=mid;
        }
        //printf("!\n"); fflush(stdout);
        //cout<<le<<endl;
        LL cnt=0; forint(i, 1, n) cnt+=le/t[i];
        int rank=(int)(k-cnt);
        forint(i, 1, n) if(le%t[i]!=0) --rank;
        int i=1;
        //cout<<le<<" "<<rank<<" "<<cnt<<endl;
        while(rank>0) {
            if(le%t[i]==0) {
                --rank; if(rank==0) break;
            }
            ++i;
        }
        printf("Case #%d: %d\n", cs, i);
    }
    return 0;
}
