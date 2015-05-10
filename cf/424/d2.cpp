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

const int MAXN=333;

int height[MAXN][MAXN];
int a[MAXN], b[MAXN], c[MAXN], d[MAXN];
int n, m, t, tp, tu, td;

int cst(int h1, int h2) {
	if(h1==h2) return tp;
	if(h1<h2) return tu;
	else return td;
}

int ans, ansx1, ansy1, ansx2, ansy2;
void upt(int tmp, int x1, int y1, int x2, int y2) {
	if(tmp<ans) {
		ans=tmp;
		ansx1=x1, ansy1=y1;
		ansx2=x2, ansy2=y2;
	}
}

int main() {
	scanf("%d%d%d", &n,&m,&t);
	scanf("%d%d%d", &tp,&tu,&td);
	forint(i, 1, n) forint(j, 1, m) scanf("%d", &height[i][j]);
	ans=1<<30;
	ansx1=1, ansy1=1;
	ansx2=2, ansy2=2;
	forint(x1, 1, n) {
		fillchar(a, 0); fillchar(b, 0);
		forint(x2, x1+1, n) {
			fillchar(c, 0); fillchar(d, 0);
			forint(j, 1, m) { //
				a[j]+=cst(height[x2][j], height[x2-1][j]);
				b[j]+=cst(height[x2-1][j], height[x2][j]);
			}
			forint(j, 2, m) {
				c[j]=c[j-1]+cst(height[x1][j-1], height[x1][j]);
				d[j]=d[j-1]+cst(height[x2][j], height[x2][j-1]);
			}
			if(x2<=x1+1) continue;
			set<PII> z;
			forint(j, 1, m) {
				if(j>=3) z.insert(MP(a[j-2]-c[j-2]-d[j-2], j-2));
				int want=t-(c[j]+d[j]+b[j]);
				set<PII>::iterator it=z.lower_bound(MP(want, 0));
				if(it!=z.end()) {
					upt(abs(want-it->fi), x1, it->se, x2, j);
				}
				if(it!=z.begin() && z.size()>0) {
					--it;
					upt(abs(want-it->fi), x1, it->se, x2, j);
				}
			}
		}
	}
	printf("%d %d %d %d\n", ansx1, ansy1, ansx2, ansy2);
	//printf("ans=%d\n",ans);
	return 0;
}
