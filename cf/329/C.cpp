#include <iostream>
#include <sstream>
#include <algorithm>
#include <set>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

typedef long long LL;
typedef pair<int,int> PII;
typedef vector<int> VI;
#define PB push_back
#define MP make_pair
#define forint(i, a, b) for(int i=(int)(a); i<=(int)(b); ++i)
#define forintdown(i, a, b) for(int i=(int)(a); i>=(int)(b); --i)
#define forn(i, n) for(int i=0; i<(int)(n); ++i)
#define forndown(i, n) for(int i=(int)(n)-1; i>=0; --i)
#define fillchar(a, x) memset(a, x, sizeof(a))
template<class T> void setmin(T &a, T b) { if(b<a) a=b; }
template<class T> void setmax(T &a, T b) { if(b>a) a=b; }
template<class T> T gcd(T a, T b) { return b==0 ? a : gcd(b,a%b); }

const int MAXN=100010;

int g[MAXN], g_nxt[MAXN*2], g_lnk[MAXN*2], deg[MAXN];
int n, m;

int cyc[MAXN], len;
bool vis[MAXN];

int c[MAXN], cl; bool is_cyc;
void pick(int x0) {
	if(deg[x0]==0) {
		c[cl=1]=x0; is_cyc=false;
		return;
	}
	is_cyc=false;
	cl=1; c[cl]=x0;
	int x;
	for(x=g_lnk[g[x0]], px=x0; deg[x]>1; ) {
		c[++cl]=x;
		int e=g[x];
		if(g_lnk[e]==px) e=g_nxt[e];
		if(g_lnk[e]==x0) {
			is_cyc=true; break;
		}
		px=x, x=g_lnk[e];
	}
	if(!is_cyc) {
		c[cl=1]=x;
		for(px=x, x=g_lnk[g[x]]; ; ) {
			c[++cl]=x;
			int e=g[x];
			if(g_lnk[e]==px) e=g_nxt[e];
			if(e==0) break;
			px=x, x=g_lnk[e];
		}
	}
}

int p[MAXN][5], pn[MAXN];
int num;

void add(int p[], int l) {
}

int main() {
	scanf("%d%d", &n,&m);
	memset(g, 0, sizeof(g)); fillchar(deg, 0);
	int e=0;
	forn(tt, m) {
		int a, b; scanf("%d%d", &a,&b);
		++deg[a], ++deg[b];
		g_lnk[++e]=b, g_nxt[e]=g[a], g[a]=e;
		g_lnk[++e]=a, g_nxt[e]=g[b], g[b]=e;
	}
	
	len=0; fillchar(vis, false);
	num=0;
	forint(x, 1, n) if(!vis[x]) {
		pick(x);
		if(cl==1 || cl>=5) {
			for(int i=1; i<=cl; i+=2) cyc[++len]=c[i];
			for(int i=2; i<=cl; i+=2) cyc[++len]=c[i];
			continue;
		}
		++num;
		pn[num]=cl;
		forint(i, 1, cl) p[num][i]=c[i];
	}
	if(num==1) {
		if(
	} else {
		int x=1, y=2;
		if(pn[x]==3) swap(x, y);
		if(pn[y]==4) cyc[++len]=p[y][1], cyc[++len]=p[y][3]; else cyc[++len]=p[y][1];
		if(pn[x]==4) cyc[++len]=p[x][1], cyc[++len]=p[x][3]; else cyc[++len]=p[x][1];
		if(pn[y]==4) cyc[++len]=p[y][2], cyc[++len]=p[y][4]; else cyc[++len]=p[y][2];
		if(pn[x]==4) cyc[++len]=p[x][2], cyc[++len]=p[x][4]; else cyc[++len]=p[x][2];
		if(pn[y]==3) cyc[++len]=p[y][3];
		if(pn[x]==3) cyc[++len]=p[x][3];
		forint(i, 3, num) add(p[i], pn[i]);
	}
	return 0;
}
