#include <cstring>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

typedef long long LL;
typedef vector<int> VI;
typedef vector<LL> VLL;
typedef pair<int,int> PII;
#define fi first
#define se second
#define PB push_back
#define MP make_pair
template<class T> bool setmin(T &a, T b) {
	if(b<a) {a=b; return true;} else return false;
}
template<class T> bool setmax(T &a, T b) {
	if(b>a) {a=b; return true;} else return false;
}
#define forint(i, a, b) for(int i=(int)(a); i<=(int)(b); ++i)
#define forintdown(i, a, b) for(int i=(int)(a); i>=(int)(b); --i)
#define forn(i, n) for(int i=0; i<(int)(n); ++i)
#define forndown(i, n) for(int i=(int)(n)-1; i>=0; --i)
#define fillchar(a, x) memset(a, x, sizeof(a))

const int MAXD=1000010;
const int MAXN=100010;

int a, b;
int x[MAXN], n;
int nxt[MAXD];
int far[MAXD];
int f[MAXD];

int getnext(int x) {
	return nxt[x]==x ? x : (nxt[x]=getnext(nxt[x]));
}

int tr[MAXD];
void add(int x, int v) {
	++x;
	for(; x<=a-b+1; x+=(x&-x)) setmin(tr[x],v);
}
int get(int x) {
	int ans=1<<30;
	++x;
	for(; x>=1; x-=(x&-x)) setmin(ans, tr[x]);
	return ans;
}

int main() {
	scanf("%d", &n); forint(i, 1, n) scanf("%d", x+i);
	scanf("%d%d",&a,&b);

	forint(i, 0, a-b) nxt[i]=i;
	fillchar(far, 0);
	sort(x+1, x+n+1);
	forintdown(i, n, 1) {
		int cur=b/x[i]*x[i];
		if(cur<b) cur+=x[i];
		while(cur<a) {
		//printf("x=%d cur=%d\n",x[i],cur);
			int p=getnext(cur-b)+b;
			if(p==cur) {
				far[cur-b]=x[i];
				nxt[cur-b]=cur-b+1;
			} else {
				cur=p/x[i]*x[i];
				if(cur<p) cur+=x[i];
			}
		}
	}
	//forint(i, b,a) printf("far[%d]=%d\n",i,far[i-b]);

	fillchar(tr, 50);
	int ans=0;
	add(a-b, 0);
	forintdown(i, a-1, b) {
		int p=min(a, i+max(far[i-b]-1,1));
		ans=get(p-b)+1;
		//printf("i=%d p=%d ans=%d\n",i,p,ans);
		add(i-b, ans);
	}
	printf("%d\n", ans);


	return 0;
}
