/*
 * 22:38 - 22:50 - tle
 */
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

const LL MOD=LL(1e9)+7;
const int V=100000;

LL inv(LL x) {
    LL y=MOD-2, ans=1;
    for(; y>0; y>>=1, x=x*x%MOD)
        if(y&1) ans=ans*x%MOD;
    return ans;
}

int mu[V+9];
bool prime[V+9];
int a[100010], n;

int ivr[999], iv[999];
int ivn;
void cal_ival(int a) {
    // all values \floor(a/k)/a for 1<=k<=V
    ivn=0;
    int i=1, j=a;
    while(i*i<=a) {
        ivr[++ivn]=i, iv[ivn]=j;
        ++i; j=a/i;
    }
    while(i<=a) {
        int i2=a/j;
        ivr[++ivn]=i2, iv[ivn]=j;
        i=i2+1;
        --j;
    }
}

LL vh[V+9];
int cnt1=0, cnt2=0;
LL z[V+9], z2[V+9];
void pre_h() {
    fillchar(z, 0); fillchar(z2, 0);
    forint(i, 1, n) {
        cal_ival(a[i]);
        //printf("i=%d... sz=%d\n",i,(int)iv.size());fflush(stdout);
        //printf("%d\n", tot+=ivn);
        LL a_inv=inv(a[i]);
        int l=0, r=0;
        forint(k, 1, ivn) {
            LL v=iv[k]*a_inv%MOD;
            l=r+1, r=ivr[k];

            z[l]+=v;
            z[r+1]-=v;
            v=v*v%MOD;
            z2[l]+=v;
            z2[r+1]-=v;
        }
    }
    forint(i, 1, V) {
        (z[i]+=z[i-1])%=MOD;
        (z2[i]+=z2[i-1])%=MOD;
    }
    LL inv2=inv(2);
    forint(i, 1, V) vh[i]=(z[i]*z[i]-z2[i])%MOD*inv2%MOD;
}

int main() {
    fillchar(mu, 0);
    mu[1]=1;
    forint(i, 1, V)
        for(int j=i*2; j<=V; j+=i)
            mu[j]-=mu[i];
    fillchar(prime, true);
    forint(i, 2, V) if(prime[i]) {
        for(int j=i*2; j<=V; j+=i)
            prime[j]=false;
    }
    forintdown(i, V, 2) if(prime[i]) {
        for(LL j=LL(i)*LL(i); j<=(LL)V; j*=(LL)i)
            prime[(int)j]=true;
    }

    while(scanf("%d",&n)==1) {
        forint(i, 1, n) scanf("%d", &a[i]);
        //printf("pre...\n");fflush(stdout);
        pre_h();
        LL ans=0;
        forint(p, 1, V) if(prime[p]) {
        //printf("p=%d...\n",p);fflush(stdout);
            int rbound=V/p+2;
            forint(k, 1, rbound) {
                if(k*p>V) break;
                (ans+=mu[k]*vh[k*p])%=MOD;
            }
        }
        forint(i, 1, n) (ans*=a[i])%=MOD;
        ans=(ans%MOD+MOD)%MOD;
        printf("%d\n", (int)ans);
    }
    return 0;
}
