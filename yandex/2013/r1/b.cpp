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

const int MAXN=1010;

int a[MAXN][MAXN];
VI e[MAXN*MAXN];
int n, m, cnt;
char clr[MAXN*MAXN];

void go_next(int &i, int &j, int &dir) {
	if(j+dir>=1 && j+dir<=m) {
		j+=dir;
	} else {
		++i; dir=-dir;
	}
}

const int dx[4]={0, 1, 0, -1};
const int dy[4]={1, 0, -1, 0};

int main() {
	scanf("%d%d", &n,&m);
	int rest=n*m, x=1, y=1, dir=1;
	cnt=0;
	while(rest>=cnt+1) {
		++cnt; rest-=cnt;
		forint(i, 1, cnt) {
			a[x][y]=cnt; go_next(x, y, dir);
		}
	}
	while(rest>0) {
		a[x][y]=cnt; go_next(x, y, dir);
		--rest;
	}
	forint(i, 1, cnt) e[i].clear();
	forint(x, 1, n) forint(y, 1, m)
		forn(i, 4) {
			int x0=x+dx[i];
			int y0=y+dy[i];
			if(x0<1 || x0>n || y0<1 || y0>m) continue;
			if(a[x][y]!=a[x0][y0])
				e[a[x][y]].PB(a[x0][y0]);
		}
	forint(i, 1, cnt) clr[i]='*';
	forint(i, 1, cnt) {
		set<char> no;
		forn(k, e[i].size()) {
			int j=e[i][k];
			no.insert(clr[j]);
		}
		clr[i]='A';
		while(no.find(clr[i])!=no.end()) ++clr[i];
	}
	printf("%d\n", cnt);
	forint(i, 1, n) {
		forint(j, 1, m) putchar(clr[a[i][j]]);
		putchar('\n');
	}
	return 0;
}
