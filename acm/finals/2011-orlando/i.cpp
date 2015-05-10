// 0:14 - 0:30 - re sample
// 0:30 - 0:40 - pass sample but slow - re
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
typedef vector<PII> VPI;
typedef pair<LL,LL> PLL;
typedef long double LD;

const int MAXN=100010;
const int MAXV=1000010;

struct Segment {
	VI next;
	VI val;
	int s, t;
	int get_next(int i) {
		VI stack;
		while(next[i]!=i) {
			stack.PB(i);
			i=next[i];
		}
		forn(k, stack.size())
			next[stack[k]]=i;
		return i;
	}
	Segment(int s, int t, int w) : s(s), t(t) {
		next.resize(t-s+2);
		forn(i, next.size()) next[i]=i;
		val.resize(t-s+1);
		forn(i, val.size()) val[i]=w+1;
	}
	void cover(int l, int r, int c) {
		//printf("cover in\n"); fflush(stdout);
		//printf("st=[%d,%d] lr=[%d,%d]\n",s,t,l,r);
		l-=s, r-=s;
		//printf("lr=[%d,%d] next.sz=%d\n",l,r,next.size());
		for(int i=get_next(l); i<=r; i=get_next(i+1)) {
			next[i]=i+1;
			val[i]=c;
		}
		//printf("cover out\n"); fflush(stdout);
	}
	void go(VPI a, int w) {
		forn(i, a.size()) {
			int h=a[i].fi-w;
			int l=max(s, a[i].se-w);
			int r=min(t, a[i].se+w);
			if(l<=r) cover(l, r, h);
		}
	}
};

bool check(VPI a, VPI b, int w) {
	Segment sa(-w, w, w);
	sa.go(a, w);
	Segment sb(-w, w, w);
	sb.go(b, w);
	forn(i, sa.val.size())
		if(sa.val[i]+sb.val[i]>1)
			return true;
	return false;
}

int solve(int n) {
	VPI a, b;
	forint(i, 1, n) {
		int x, y; scanf("%d%d", &x,&y);
		if(x>0) a.PB(MP(x, y));
		else b.PB(MP(-x,y));
	}
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	int le=0, ri=MAXV;
	if(check(a, b, MAXV)) return MAXV;
	while(le<ri) {
		int mid=(le+ri)/2;
		if(check(a, b, mid))
			le=mid+1;
		else
			ri=mid;
	}
	return le;
}

int main() {
	int cs=0;
	while(1) {
		int n;
		scanf("%d", &n); if(n<0) break;
		int ans=solve(n);
		if(ans==MAXV)
			printf("Case %d: never\n",++cs);
		else
			printf("Case %d: %d\n",++cs,ans);
	}
	return 0;
}
