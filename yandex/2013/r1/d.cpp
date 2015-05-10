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

const int MAXN=1000010;

int h[MAXN], c[MAXN][2];
int ch[MAXN];
int n, cnt, maxh;

int main() {
	scanf("%d", &n);
	fillchar(c, 0); cnt=maxh=0;
	forint(i, 1, n) {
		static char s[MAXN];
		scanf("%s", s+1); int len=strlen(s+1);
		h[i]=len; maxh=max(maxh, len);
		cnt+=len;
		forint(j, 1, len) {
			int cur=(s[j]=='G'?0:1);
			c[j][cur]++;
		}
	}

	fillchar(ch, 0);
	forint(i, 1, n) ch[h[i]]++;
	forint(i, 1, maxh+1) ch[i]+=ch[i-1];
	int ans=0;
	int d[2]; d[0]=d[1]=1<<30;
	forint(i, 1, maxh+1) {
		int e[2];
		forn(k, 2) {
			e[k]=min(d[k], c[i][k]);
			if(d[k]>e[k]) {
				int tmp=min(d[k]-e[k], ch[i-1]-ans);
				ans+=tmp;
			}
			d[k]=e[k];
		}
	}
	printf("%d\n", ans);
	return 0;
}
