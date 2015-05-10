#include <algorithm>
#include <iostream>
#include <sstream>
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
const int MAXN=100010;

int g[MAXN], g_lnk[MAXN*2], g_nxt[MAXN*2], g_ei[MAXN*2];
int ew[MAXN], ex[MAXN];
int n;

int sz[MAXN];
LL sp[MAXN], ss[MAXN];

void dfs(int x, int fa) {
	sz[x]=1; sp[x]=1;
	ss[x]=0;
	for(int i=g[x], y; i; i=g_nxt[i])
		if((y=g_lnk[i])!=fa) {
			int ei=g_ei[i];
			ex[ei]=y;
			dfs(y, x);
			sp[x]+=2*LL(sz[x])*LL(sz[y]);
			sz[x]+=sz[y];
			ss[x]+=ss[y];
		}
	ss[x]+=2*n-2*sp[x];
	//printf("sp[%d]=%d\n",x,(int)sp[x]);
	//printf("ss[%d]=%d\n",x,(int)ss[x]);
}

double eval(int i) {
	double ans=double(ew[i])*double(ss[ex[i]]);
	ans/=n;
	ans/=n-1;
	ans/=n-2;
	ans*=3*n-6;
	return ans;
}

double eval() {
	double ans=0;
	forint(i, 1, n-1)
		ans+=eval(i);
	return ans;
}

int main() {
	scanf("%d", &n);
	forint(i, 1, n-1) {
		int a, b, c; scanf("%d%d%d", &a,&b,&c);
		ew[i]=c;
		static int e=0;
		g_lnk[++e]=b, g_ei[e]=i, g_nxt[e]=g[a], g[a]=e;
		g_lnk[++e]=a, g_ei[e]=i, g_nxt[e]=g[b], g[b]=e;
	}
	dfs(1, 0);
	
	double ans=eval();
	int m; scanf("%d", &m);
	forn(_, m) {
		int i, w;
		scanf("%d%d", &i,&w);
		ans-=eval(i);
		ew[i]=w;
		ans+=eval(i);
		printf("%.15lf\n", ans);
	}

	return 0;
}
