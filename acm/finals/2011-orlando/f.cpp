// 15:43
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
#define forn(i, n) forint(i, 0, (n)-1)
#define fillchar(a, x) memset(a, x, sizeof(a))
typedef pair<int, int> PII;
typedef long long LL;
typedef vector<int> VI;
typedef pair<LL,LL> PLL;
typedef long double LD;

const int MAXN=100010;

struct Machine {
	int day, in, out, profit;
	bool operator <(const Machine &m) const {
		return day<m.day;
	}
} a[MAXN];
LL f[MAXN];
int n, C, D;

LL useless(PLL cur, PLL le, PLL ri) {
	LD z=LD(ri.fi-cur.fi)*LD(le.se-cur.se) - LD(ri.se-cur.se)*LD(le.fi-cur.fi);
	if(abs(z)>1e10) return z>0;
	LL t=(ri.fi-cur.fi)*(le.se-cur.se) - (ri.se-cur.se)*(le.fi-cur.fi);
	return t>=0;
}

struct Treap {
	set<PLL> s;
	void clear() {
		s.clear();
	}
	void insert(LL x, LL y) { // insert (x,y)
		PLL cur=MP(x, y);
		set<PLL>::iterator it;
		it=s.lower_bound(MP(x, -1));
		if(it!=s.end() && it->fi==x) {
			if(it->se<y)
				s.erase(it);
			else
				return;
		}
		it=s.lower_bound(cur);
		if(it!=s.end() && it!=s.begin()) {
			PLL ri=*it, le=*(--it);
			if(useless(cur, le, ri))
				return;
		}
		while(1) {
			it=s.lower_bound(cur);
			if(it==s.end()) break;
			PLL y=*it;
			++it; if(it==s.end()) break;
			PLL z=*it;
			if(useless(y, cur, z)) s.erase(y);
			else break;
		}
		while(1) {
			it=s.lower_bound(cur);
			if(it==s.begin()) break; --it;
			PLL y=*it;
			if(it==s.begin()) break; --it;
			PLL z=*it;
			if(useless(y, z, cur)) s.erase(y);
			else break;
		}
		s.insert(cur);
	}
	LL get(LL d) { // find max{x*d+y}; -1 if none
		if(s.size()==0)
			return -1;
		/*
		LL ans=0;
		for(set<PLL>::iterator it=s.begin(); it!=s.end(); ++it) {
			PLL a=*it;
			LL va=a.fi*d+a.se;
			ans=max(ans, va);
		} return ans;
		*/

		while(1) {
			set<PLL>::iterator it=s.begin();
			PLL a=*it;
			++it; if(it==s.end()) break;
			PLL b=*it;
			LL va=a.fi*d+a.se;
			LL vb=b.fi*d+b.se;
			if(vb>=va) s.erase(a);
				else break;
		}
		return s.begin()->fi*d+s.begin()->se;
	}
} tr;

void solve(int cs) {
	forint(i, 1, n) scanf("%d%d%d%d", &a[i].day,&a[i].in,&a[i].out,&a[i].profit);
	sort(a+1, a+n+1);

	tr.clear();
	forint(i, 1, n) {
		LL val=C;
		val=max(val, tr.get(a[i].day));
		if(val>=a[i].in) {
			f[i]=val-a[i].in+a[i].out;
			LL x=a[i].profit;
			LL y=f[i]-LL(a[i].day+1)*LL(a[i].profit);
			tr.insert(x, y);
		} else {
			f[i]=-1;
		}
	}

	LL ans=C;
	forint(i, 1, n) if(f[i]>=0) {
		LL tmp=f[i]+(D-a[i].day)*LL(a[i].profit);
		ans=max(ans, tmp);
	}
	printf("Case %d: ", cs);
	cout<<ans<<endl;
}

int main() {
	int cs=0;
	while(1) {
		scanf("%d%d%d", &n, &C, &D);
		if(n==0) break;
		solve(++cs);
	}
	return 0;
}
