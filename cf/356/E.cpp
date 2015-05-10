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

const int MAXN=100010;
const int MAXC=27;
const int MAXP=22;

int a[MAXN];
int cnt[MAXN][MAXC];
int modi_i, modi_c;
char buf[MAXN];
int n;

int plen[MAXP];
LL val[MAXP];
int pn;

int h[MAXN];

int occurs(int l, int r, int c) {
	int ans=cnt[r][c]-cnt[l-1][c];
	if(l<=modi_i && modi_i<=r) {
		if(a[modi_i]==c) --ans;
		if(modi_c==c) ++ans;
	}
	return ans;
}
bool same(int l1, int r1, int l2, int r2) {
	forn(c, MAXC)
		if(occurs(l1,r1,c) != occurs(l2,r2,c))
			return false;
	return true;
}

LL cur;
void update(int i) {
	int h0=h[i];
	while(1) { // ++h0
		if(i-plen[h0]<1 || i+plen[h0]>n) break;
		if(h[i-plen[h0-1]]<h0 || h[i+plen[h0-1]]<h0) break;
		if(occurs(i-plen[h0], i-1, a[i])>0) break;
		if(occurs(i+1, i+plen[h0], a[i])>0) break;
		++h0;
	}
	while(h0>0) { // --h0
		--h0;
		if(i-plen[h0]<1 || i+plen[h0]>n) continue;
		if(h[i-plen[h0-1]]<h0 || h[i+plen[h0-1]]<h0) continue;
		if(occurs(i-plen[h0], i-1, a[i])>0) continue;
		if(occurs(i+1, i+plen[h0], a[i])>0) continue;
		++h0;
		break;
	}
	if(h0!=h[i]) {
		cur-=val[h[i]];
		cur+=val[h0];
		swap(h[i], h0);
		if(h0>=2) {
			update(i-plen[h0-2]-1);
			update(i+plen[h0-2]+1);
		}
	}
}

int modi_old;
void modi(int i, int c) {
	modi_old=a[i]; a[i]=c;
	modi_i=i;
	modi_c=c;
	if(i>1) update(i-1);
	if(i<n) update(i+1);
	update(i);
}

void undo_modi() {
	int i=modi_i;
	modi_i=0;
	a[i]=modi_old;
	if(i>1) update(i-1);
	if(i<n) update(i+1);
	update(i);
}

int main() {
	scanf("%s", buf+1); n=strlen(buf+1);
	forint(i, 1, n) a[i]=buf[i]-'a';
	fillchar(cnt[0], 0);
	forint(i, 1, n) {
		memmove(cnt[i], cnt[i-1], sizeof(cnt[i]));
		++cnt[i][a[i]];
	}

	plen[pn=0]=0;
	while((plen[pn+1]=plen[pn]*2+1)<=n) ++pn;
	val[0]=0;
	forint(i, 1, pn) {
		val[i]=val[i-1];
		val[i]+=(LL)plen[i]*(LL)plen[i];
	}

	modi_i=0;
	forint(i, 1, n) h[i]=1;
	forint(k, 2, pn)
		forint(i, plen[k-1]+1, n-plen[k-1]) {
			int lc=i-plen[k-2]-1;
			int rc=i+plen[k-2]+1;
			if(h[lc]<k-1 || h[rc]<k-1) continue;
			if(occurs(i-plen[k-1], i-1, a[i])>0) continue;
			if(occurs(i+1, i+plen[k-1], a[i])>0) continue;
			if(!same(i-plen[k-1], i-1, i+1, i+plen[k-1])) continue;
			h[i]=k;
		}
	
	//modi(2, 0); return 0;

	LL ans=0;
	cur=0;
	forint(i, 1, n) cur+=val[h[i]];
	ans=cur;
	forint(i, 1, n) {
		modi(i, MAXC-1);
		ans=max(ans, cur);
	//cout<<"#1 cur="<<cur<<endl;
		undo_modi();
		if(i>=3) {
			modi(i, a[i-2]);
			ans=max(ans, cur);
			undo_modi();
		}
		if(i<=n-2) {
			modi(i, a[i+2]);
			ans=max(ans, cur);
			undo_modi();
		}
	}
	cout<<ans<<endl;
	return 0;
}
