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

const int MAXN=300010;

typedef map<int,int> St;

int a[MAXN], sum[MAXN]; PII ca[MAXN];
int n, k;

St *s[MAXN];
bool vis[MAXN]; int le[MAXN], ri[MAXN];
LL ans;

void tot(St *x, St *y, int mid) {
    if(x->size()>y->size()) return tot(y, x, mid);
    for(auto &u: *x) {
        int want=(u.fi-mid)%k;
        if(want<0) want+=k;
        ans+=(u.se)*((*y)[want]);
        //printf("u.fi=%d %d %d want=%d\n",u.fi,u.se,(*y)[want],want);
    }
}

St *unite(St *x, St *y) {
    if(x==nullptr) return y;
    if(y==nullptr) return x;
    if(x->size()>y->size()) return unite(y, x);
    for(auto &u: *x)
        (*y)[u.fi]+=u.se;
    x->clear();
    return y;
}

void put(int i) {
    vis[i]=true;
    St *x=(vis[i-1]?s[le[i-1]]:nullptr);
    St *y=(vis[i+1]?s[i+1]:nullptr);
    St *z=new St; (*z)[sum[i]]++;

    //printf("i=%d\n",i);

    if(x) {
        ans+=(*x)[sum[i-1]]-1;
        if(sum[le[i-1]-1]==sum[i-1]) ++ans;
    }
    //cout<<ans<<endl;
    if(y) {
        ans+=(*y)[sum[i]];
    }
    //cout<<ans<<endl;
    if(x && y) {
        (*x)[sum[i-1]]--;
        (*x)[sum[le[i-1]-1]]++;
        tot(x, y, a[i]);
        (*x)[sum[i-1]]++;
        (*x)[sum[le[i-1]-1]]--;
    }
    //cout<<ans<<endl;

    z=unite(z, x);
    z=unite(z, y);
    int l=(vis[i-1]?le[i-1]:i);
    int r=(vis[i+1]?ri[i+1]:i);
    le[r]=l, ri[l]=r;
    s[l]=z;
    
}

int main() {
    scanf("%d%d", &n,&k); 
    sum[0]=a[0]=0;
    forint(i, 1, n) {
        scanf("%d", &ca[i].fi), ca[i].se=i;
        a[i]=ca[i].fi; sum[i]=(sum[i-1]+a[i])%k;
    }
    sort(ca+1, ca+n+1);

    ans=0;
    fillchar(vis, false);
    forint(cur, 1, n) {
        int i=ca[cur].se;
        put(i);
    }
    cout<<ans<<endl;

    return 0;
}
