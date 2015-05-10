// 12:42 - 12:51 - bug in algo
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <deque>
#include <set>
using namespace std;

#define fi first
#define se second
#define PB push_back
#define MP make_pair
#define forint(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define forintdown(i, a, b) for(int i=int(a); i>=int(b); --i)
#define forn(i, n) forint(i, 0, (n)-1)
#define fillchar(a, x) memset(a, x, sizeof(a))
typedef pair<int, int> PII;
typedef long long LL;
typedef vector<int> VI;
typedef pair<LL,LL> PLL;
typedef long double LD;

const int N=1000000;
const int K=6;

int f[N+10];
LL p[N+10];
PII pyramids[N]; int num;

int main() {
	num=0;
	for(int sum=5, cur=2; sum<=N; cur++, sum+=cur*cur)
		pyramids[++num]=MP(sum, cur);
	for(int sum=10, cur=3; sum<=N; cur+=2, sum+=cur*cur)
		pyramids[++num]=MP(sum, -cur);
	for(int sum=20, cur=4; sum<=N; cur+=2, sum+=cur*cur)
		pyramids[++num]=MP(sum, -cur);
	sort(pyramids+1, pyramids+num+1);

	fillchar(f, 50); int maxval=f[0];
	f[0]=0; p[0]=0;
	forint(i, 1, num) {
		int cur=pyramids[i].fi;
		forintdown(x, N, cur)
			if(f[x-cur]+1<=f[x]) {
				f[x]=f[x-cur]+1;
				p[x]=(p[x-cur]<<10)|i;
			}
	}

	int cs=0;
	while(1) {
		int n; scanf("%d", &n);
		if(n==0) break;
		printf("Case %d:", ++cs);
		if(f[n]==maxval) printf(" impossible\n");
		else {
			LL ans=p[n];
			while(ans>0) {
				int pre=(ans&((1<<10)-1)); ans>>=10;
				int id=pyramids[pre].se;
				if(id>0) printf(" %dH", id);
					else printf(" %dL", -id);
			}
			printf("\n");
		}
	}
	return 0;
}
