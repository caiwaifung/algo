#include <cstring>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

typedef long long LL;
typedef vector<int> VI;
typedef vector<LL> VLL;
typedef pair<int,int> PII;
#define fi first
#define se second
#define PB push_back
#define MP make_pair
template<class T> bool setmin(T &a, T b) {
	if(b<a) {a=b; return true;} else return false;
}
template<class T> bool setmax(T &a, T b) {
	if(b>a) {a=b; return true;} else return false;
}
#define forint(i, a, b) for(int i=(int)(a); i<=(int)(b); ++i)
#define forintdown(i, a, b) for(int i=(int)(a); i>=(int)(b); --i)
#define forn(i, n) for(int i=0; i<(int)(n); ++i)
#define forndown(i, n) for(int i=(int)(n)-1; i>=0; --i)
#define fillchar(a, x) memset(a, x, sizeof(a))
int gcd(int a, int b) {
	return b==0 ? a : gcd(b,a%b);
}

const int MAXN=1000010;
int g[MAXN], g_lnk[MAXN*2], g_nxt[MAXN*2];
int lst[MAXN], ss, tt;
int f[MAXN];
int n, m, s, t;

int main() {
	scanf("%d%d", &n,&m);
	int e=0; fillchar(g, 0);
	forint(i, 1, m) {
		int a, b; scanf("%d%d", &a,&b);
		g_lnk[++e]=b, g_nxt[e]=g[a], g[a]=e;
		//g_lnk[++e]=a, g_nxt[e]=g[b], g[b]=e;
	}
	scanf("%d%d", &s,&t);
	ss=tt=0; lst[++tt]=s;
	fillchar(f, 0); f[s]=1;
	while(ss<tt) {
		int x=lst[++ss];
		for(int e=g[x]; e; e=g_nxt[e]) {
			int y=g_lnk[e];
			if(f[y]==0) {
				lst[++tt]=y; f[y]=1;
			}
		}
	}
	if(f[t]==0) printf("-1\n");
	else {
		fillchar(f, 50);
		f[t]=0;
		forintdown(i, tt, 1) {
			int x=lst[i];
			if(g[x]==0) continue;
			int mx=0;
			for(int e=g[x]; e; e=g_nxt[e]) {
				int y=g_lnk[e];
				setmax(mx, f[y]);
				setmin(f[x], f[y]+1);
			}
			setmin(f[x], mx);
		}
		printf("%d\n", f[s]);
	}

	return 0;
}
