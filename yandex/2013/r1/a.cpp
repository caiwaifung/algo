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

const int MAXN=500010;

int p[MAXN], a[MAXN];
int n;
char ans_c[MAXN]; LL ans_t[MAXN];
int used[MAXN];

int nxt[MAXN];
int get_nxt(int x) {
	if(nxt[x]<0) return x;
	nxt[x]=get_nxt(nxt[x]);
	return nxt[x];
}

bool go(LL limit) {
	//printf("go %I64d\n",limit);
	VPI lst;
	forint(i, 1, n) lst.PB(MP(p[i], i));
	sort(lst.rbegin(), lst.rend());

	//printf("#1\n");

	fillchar(nxt, 0xff);
	fillchar(used, 0);
	forn(k, lst.size()) {
		int i=lst[k].se;
		//printf("i=%d\n", i);
		LL bound=min(limit-a[i], LL(n));
		ans_c[i]='B';
		if(bound>0) {
			int t=get_nxt(int(bound));
			//printf("  t=%d\n", t);
			if(t>0) {
				nxt[t]=t-1;
				ans_c[i]='A';
				used[t]=i;
			}
		}
	}
	//printf("#2\n");
	LL cur=1;
	forint(i, 1, n) if(used[i]>0)
		ans_t[used[i]]=cur++;
	//printf("#3\n");
	forint(i, 1, n) if(ans_c[i]=='B') {
		ans_t[i]=cur; cur+=p[i];
	}
	return cur<=limit+1;
}

int main() {
	scanf("%d", &n);
	forint(i, 1, n) scanf("%d%d", &p[i],&a[i]);
	//go(7); return 0;
	LL le=1, ri=1LL<<55;
	while(le<ri) {
		LL mid=(le+ri)/2;
		if(go(mid)) ri=mid;
			else le=mid+1;
	}
	go(le);
	cout<<le<<endl;
	forint(i, 1, n) cout<<ans_c[i]<<" "<<ans_t[i]<<endl;
	return 0;
}
