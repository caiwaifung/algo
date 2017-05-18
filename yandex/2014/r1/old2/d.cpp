#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
using namespace std;

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
typedef pair<double,double> PDD;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
typedef vector<int> VI;
typedef vector<LL> VL;
typedef vector<PII> VPI;
typedef vector<PLL> VPL;

const int MAXN=10010;
const int MAXV=17010;
const int MOD=int(1e9)+7;

int mem[2][MAXV];
int a[MAXN];
int n;

int main() {
	scanf("%d", &n);
	forint(i, 1, n) scanf("%d", &a[i]);
	int v=16384;
	int *f=mem[0], *g=mem[1];
	memset(f, 0, sizeof(mem[0]));
	f[0]=1;
	forint(i, 1, n) {
		memmove(g, f, sizeof(mem[0]));
		forint(j, 0, v) if(f[j]>0) {
			int j2=j^a[i];
			int tmp=f[j]*2; if(tmp>=MOD) tmp-=MOD;
			g[j2]+=tmp; if(g[j2]>=MOD) g[j2]-=MOD;
		}
		swap(f, g);
	}
	printf("%d\n", f[0]);
	return 0;
}
