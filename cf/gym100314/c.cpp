#include <cstdlib>
#include <set>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <map>
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
typedef vector<int> VI;
typedef pair<double,double> PDD;

const int MAXN=220;
const int MAXR=12;
const int MAXT=510;

VI pass[MAXN]; double ep[MAXN];
double precision[MAXN];
int n, R, T;

double f[MAXT][MAXR][MAXR][MAXN];
double ans[MAXR][MAXR];

int main() {
	scanf("%d", &n);
	scanf("%d%d", &R,&T);
	forint(i, 1, n*2) {
		scanf("%lf", precision+i);
		int sf, se; scanf("%d%d", &sf, &se);
		pass[i].clear();
		forint(k, 1, sf) {
			int j; scanf("%d", &j);
			if(i>n) j+=n;
			pass[i].PB(j);
		}
		forint(k, 1, se) {
			int j; scanf("%d", &j);
			if(i<=n) j+=n;
			pass[i].PB(j);
		}
		ep[i]=1./double(pass[i].size()+1);
	}
	fillchar(ans, 0);
	fillchar(f, 0);
	f[0][0][0][1]=1.;
	forint(t, 0, T-1) forint(s1, 0, R-1) forint(s2, 0, R-1) forint(i, 1, n*2) {
		double cur=f[t][s1][s2][i]; if(cur<1e-12) continue;
		cur*=ep[i]; double tmp;
		// shoot
		tmp=cur*precision[i];
		if(i<=n) {
			// made
			if(s1+1==R) ans[R][s2]+=tmp;
				else f[t+1][s1+1][s2][n+1]+=tmp;
			// miss
			f[t+1][s1][s2][n+1]+=cur-tmp;
		} else {
			// made
			if(s2+1==R) ans[s1][R]+=tmp;
				else f[t+1][s1][s2+1][1]+=tmp;
			// miss
			f[t+1][s1][s2][1]+=cur-tmp;
		}
		// pass
		forn(k, pass[i].size()) {
			int j=pass[i][k];
			f[t+1][s1][s2][j]+=cur;
		}
	}
	forint(s1, 0, R-1) forint(s2, 0, R-1) forint(i, 1, n*2)
		ans[s1][s2]+=f[T][s1][s2][i];

	forint(i, 0, R) forint(j, 0, R) if(i<R || j<R) printf("%.9lf\n", ans[i][j]);
	return 0;
}
