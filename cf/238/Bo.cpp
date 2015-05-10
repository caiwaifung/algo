#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
typedef pair<int,int> PII;
typedef vector<int> VI;
#define MP make_pair
#define PB push_back

const int MAXN=100010;

PII a[MAXN];
int n, h;
int ans;

int bel[MAXN];
void dfs(int cur) {
	if(cur>n) {
		int da=1<<30, db=-da;
		for(int i=1; i<=n; ++i)
			for(int j=i+1; j<=n; ++j) {
				int f=a[i].first+a[j].first+(bel[i]!=bel[j])*h;
				da=min(da, f);
				db=max(db, f);
			}
		if(db-da<ans) {
			printf("Error!  ans=%d cur=%d\n",ans,db-da);
			for(int i=1; i<=n; ++i) printf("%d ", bel[i]); printf("\n");
			for(;;);
		}
		return;
	}
	for(bel[cur]=1; bel[cur]<=2; ++bel[cur])
		dfs(cur+1);
}

int main() {
	/*
	   scanf("%d%d", &n,&h);
	   for(int i=1; i<=n; ++i) scanf("%d", &a[i].first), a[i].second=i;
	 */
	while(1){
		h=rand()%100000001;
		n=10; for(int i=1; i<=n; ++i) a[i].first=rand()%100000001, a[i].second=i;

		sort(a+1, a+n+1);
		int d1=(a[n].first+a[n-1].first)-(a[1].first+a[2].first);
		int d2a=a[1].first+a[n].first+h, d2b=d2a;
		if(n>2) {
			d2a=min(d2a, a[2].first+a[3].first);
			d2b=max(d2b, a[n].first+a[n-1].first);
		}
		int d2=d2b-d2a;
		ans=min(d1, d2);
		dfs(1);
		static int cs=1;
		printf("%d: ok! ans=%d\n",cs++,ans);
	}

/*
	printf("%d\n", min(d1,d2));
	for(int i=1; i<=n; ++i)
		printf("%d%c", (d1>d2&&i==a[1].second)?1:2, i<n?' ':'\n');
	*/
	return 0;
}
