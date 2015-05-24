#include <cstdio>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <map>
#include <vector>
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
typedef pair<int,int> PII;
typedef vector<PII> VPI;
typedef pair<double,double> PDD;

int n, m, goal, maxt;
int f[2][1010][4010];

void clf(int o) {
	fillchar(f[o], 200);
}
void upt(int &x, int y) {
	x=max(x, y);
}

void solve() {
	scanf("%d%d%d",&n,&m,&goal);
	maxt=n*2+m*2;
	int ans=n*2+m*2;
	if(goal<=m) ans=min(ans, goal);

	int o1=0, o2=1;
	clf(o1);
	forint(w, 1, m) f[o1][w][w]=w;
	forint(i, 2, n) {
		clf(o2);
		// trans 1
		forint(w, 1, m) forint(c, 1, maxt)
			forint(w2, max(1, w-2), min(m, w+2))
				upt(f[o2][w2][c+(w2==1?1:2)], f[o1][w][c]+w2);
		// trans 2
		int tmp[4010]; fillchar(tmp, 200);
		forint(w, 1, m) {
			if(w>=3) {
				forint(c, 3, maxt)
					upt(tmp[c], f[o1][w-2][c-2]);
			}
			forint(c, 1, maxt)
				upt(f[o2][w][c], tmp[c]+w);
			forintdown(c, maxt, 2) tmp[c]=tmp[c-1];
		}
		// trans 3
		fillchar(tmp, 200);
		forintdown(w, m, 2) {
			if(w+2<=m) {
				forint(c, 3, maxt)
					upt(tmp[c], f[o1][w+2][c-2]);
			}
			forint(c, 1, maxt)
				upt(f[o2][w][c], tmp[c]+w);
			forintdown(c, maxt, 2) tmp[c]=tmp[c-1];
		}
		// update
		forint(w, 1, m) forint(c, 1, maxt)
			if(f[o2][w][c]>=goal) {
				//if(c+max(0,w-2)<ans) printf("f[%d,%d,%d]=%d\n",i,w,c,f[o2][w][c]);
				ans=min(ans, c+max(0, w-2));
			}
		swap(o1, o2);
	}
	printf("%d\n",ans);
}

int main() {
	freopen("C-large.in", "r", stdin);
	freopen("C.out", "w", stdout);
	int csn; scanf("%d", &csn);
	forint(cs, 1, csn) {
		cerr<<"cur: "<<cs<<endl;
		printf("Case #%d: ", cs);
		solve();
	}
	return 0;
}
