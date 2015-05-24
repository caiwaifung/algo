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

string s[1111];
vector<int> inside[111];
int n, m;
int ans_v, ans_c;

int cal(VI p) {
	if(p.size()==0) return 0;
	vector<string> t;
	forn(i, p.size()) t.PB(s[p[i]]);
	sort(t.begin(), t.end());
	int cnt=1;
	forn(i, t.size()) {
		cnt+=t[i].size();
		if(i>0) {
			size_t j=0, l=min(t[i-1].size(),t[i].size());
			while(j<l && t[i-1][j]==t[i][j]) ++j, --cnt;
		}
	}
	return cnt;
}

void dfs(int cur) {
	if(cur==n) {
		int sum=0;
		forn(i, m) sum+=cal(inside[i]);
		if(sum>ans_v) ans_v=sum, ans_c=0;
		if(sum==ans_v) ans_c++;
		return;
	}
	forn(i, m) {
		inside[i].PB(cur);
		dfs(cur+1);
		inside[i].pop_back();
	}
}

void solve() {
	scanf("%d%d", &n,&m);
	forn(i, n) {
		static char buf[999];
		scanf("%s", buf);
		s[i]=string(buf);
	}
	forn(i, m) inside[i].clear();
	ans_v=0;
	dfs(0);
	cout<<ans_v<<" "<<ans_c<<endl;
}

int main()  {
	int ncs; scanf("%d", &ncs);
	forint(cs, 1, ncs) {
		printf("Case #%d: ", cs);
		solve();
	}
	return 0;
}
