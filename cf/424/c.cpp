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

int t[1000010];
int n;

int main() {
	int ans=0;
	scanf("%d", &n);
	forint(i, 1, n) {
		int x; scanf("%d", &x);
		ans^=x;
	}
	t[0]=0;
	forint(i, 1, n) t[i]=t[i-1]^i;
	forint(i, 1, n) {
		int u=n/i;
		if(u%2!=0) {
			ans^=t[i-1];
		}
		ans^=t[n%i];
	}
	printf("%d\n", ans);
	return 0;
}
