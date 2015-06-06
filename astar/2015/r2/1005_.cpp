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

char buf[100010];
int a[100010];
int n;

void init() {
    scanf("%s", buf+1);
    n=(int)strlen(buf+1);
    forint(i, 1, n) a[i]=int(buf[i]-'a');
    a[0]=0;
}

const int H1=1000000+7;
const int H2=1000000+9;
const int P1=37;
const int P2=41;

int h1[H1], h2[H2];
int rx1[100010], rx2[100010];

int cal(int len) {
    int z1=1, z2=1;
    forn(i, len) {
        (z1*=P1)%=H1;
        (z2*=P2)%=H2;
    }
    int x1=1, x2=1;
    forint(i, 1, len-1) {
        x1=(x1*P1+a[i])%H1;
        x2=(x2*P2+a[i])%H2;
    }
    int ans=0;
    forint(i, len, n) {
        x1=(x1*P1+a[i])%H1;
        x2=(x2*P2+a[i])%H2;
        x1=int((x1-LL(z1)*LL(a[i-len]))%H1);
        x2=int((x2-LL(z2)*LL(a[i-len]))%H2);
        if(x1<0) x1+=H1;
        if(x2<0) x2+=H2;
        rx1[i]=x1, rx2[i]=x2;

        if(h1[x1]!=x2 || h2[x2]!=x1)
            ++ans;
        h1[x1]=x2, h2[x2]=x1;
    }
    forint(i, len, n) {
        h1[rx1[i]]=0;
        h2[rx2[i]]=0;
    }
    return ans;
}

void solve(int cs) {
    fillchar(h1, 0);
    fillchar(h2, 0);
    int len=1, ans=0, tot=1;
    while(1) {
        tot*=26;
        int t=cal(len);
        if(t<tot) {
            ans=tot-t;
            break;
        }
        ++len;
    }
    printf("Case #%d:\n", cs);
    printf("%d %d\n", len,ans);
}

int main() {
    int csn; scanf("%d", &csn);
    forint(cs, 1, csn) {
        init();
        solve(cs);
    }
    return 0;
}
