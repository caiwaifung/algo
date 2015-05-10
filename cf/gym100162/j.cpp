// 11:51
// 12:15 - fail sample
// 12:30 - pause
// 12:40 - redo
// 12:46 - pass sample - wa*2 - ac
#include <algorithm>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
using namespace std;

#define forint(i, a, b) for(int i=(int)(a); i<=(int)(b); ++i)
#define forintdown(i, a, b) for(int i=(int)(a); i>=(int)(b); --i)
#define forn(i, n) forint(i, 0, (n)-1)
#define forndown(i, n) forintdown(i, (n)-1, 0)
#define fillchar(a, x) memset(a, x, sizeof(a))
typedef long long LL;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef vector<LL> VL;
typedef vector<PII> VPI;
#define MP make_pair
#define PB push_back
#define fi first
#define se second

const int MAXN=255;
const int MAXK=12;

struct Point {
	int x, y;
	friend int mult(Point p0, Point p1, Point p2) {
		return (p1.x-p0.x)*(p2.y-p0.y) - (p1.y-p0.y)*(p2.x-p0.x);
	}
} a[MAXN];
int n, K;

int lc[MAXN][MAXN];
void precount() {
	forint(i, 1, n) forint(j, 1, n) {
		if(i==j) {
			lc[i][j]=0;
			continue;
		}
		Point p1=a[i], p2=a[j];
		if(p1.y>p2.y) swap(p1, p2);
		int c=0;
		forint(k, 1, n) if(k!=i && k!=j)
			if(p1.y<=a[k].y && a[k].y<p2.y)
				if(mult(p1, p2, a[k])>0)
					++c;
		lc[i][j]=c;
	}
}

int cnt(int i, int j, int k) {
	if(a[j].y<a[i].y) swap(i, j);
	if(a[k].y<a[i].y) swap(i, k);
	if(a[k].y>a[j].y) swap(j, k);
	int c=lc[i][j]-(lc[i][k]+lc[k][j]);
	if(mult(a[i], a[j], a[k])>0) {
		if(a[k].y<a[j].y) --c;
	} else c=-c;
	return c;
}

LL f[MAXN][MAXN][MAXK][2];
VI others[MAXN];

VI center(VI b, int k) {
	forn(i, b.size()) if(b[i]==k) {
		VI c;
		forint(j, i, b.size()-1) c.PB(b[j]);
		forint(j, 0, i-1) c.PB(b[j]);
		return c;
	}
	printf("error @ center!\n");
	return VI();
}

VI filter(VI b, int y_max) {
	VI c;
	forn(i, b.size()) if(a[b[i]].y<=y_max)
		c.PB(b[i]);
	return c;
}

void solve(int cs) {
	forint(i, 1, n) {
		vector<pair<double,int> > lst;
		forint(j, 1, n) if(j!=i) {
			double dx=a[j].x-a[i].x;
			double dy=a[j].y-a[i].y;
			lst.PB(MP(-atan2(dy, dx), j));
		}
		sort(lst.begin(), lst.end());
		others[i].clear();
		forn(j, lst.size()) others[i].PB(lst[j].se);
	}

	LL ans=0;
	forint(h, 1, n) {
		fillchar(f, 0);
		forint(i, 1, n) if(a[i].y<a[h].y)
			f[h][i][2][0]=1;
		forint(c, 3, K) {
			forint(j, 1, n) if(a[j].y<a[h].y) {
				VI vs=center(filter(others[j], a[h].y), h);
				int vsn=(int)vs.size();
				int i=0;
				int k=0;
				while(k<vsn && mult(a[vs[k]], a[j], a[h])<=0)
					++k;
				LL sum[2]={0};
				for(; k<vsn; ++k) {
					while(i<k && mult(a[vs[k]], a[j], a[vs[i]])>0) {
						sum[0]+=f[vs[i]][j][c-1][0];
						sum[1]+=f[vs[i]][j][c-1][1];
						++i;
					}
					int t=cnt(h, j, vs[k]);
					forn(p, 2) if(p+t<2)
						f[j][vs[k]][c][p+t]+=sum[p];
				}
			}
		}
		forint(i, 1, n) if(a[i].y<=a[h].y)
			forint(j, 1, n) if(a[j].y<=a[h].y)
				if(mult(a[i], a[j], a[h])<0)
					ans+=f[i][j][K][1];
	}
	cout<<"Case "<<cs<<": "<<ans<<endl;
}

int main() {
	int cs=0;
	while(cin>>n>>K) {
		forint(i, 1, n) cin>>a[i].x>>a[i].y;
		precount();
		solve(++cs);
	}
	return 0;
}
