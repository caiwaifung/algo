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

map<string,int> s;
vector<pair<int,string> > a;

int main() {
	freopen("pre.txt", "r", stdin);
	while(1) {
		char buf[999]; if(scanf("%s",buf)==EOF) break;
		int sc;
		scanf("%*d"); scanf("%*d"); scanf("%*d");
		scanf("%*d"); scanf("%*d"); scanf("%*d");
		scanf("%d", &sc); scanf("%*d"); scanf("%*d");
		s[string(buf)]=sc;
	}
	for(map<string,int>::iterator it=s.begin(); it!=s.end(); ++it)
		a.PB(MP(it->se,it->fi));
	sort(a.rbegin(), a.rend());
	forn(i, a.size()) {
		printf("#%2d %3d %s\n",i+1,a[i].fi,a[i].se.c_str());
		if(i==24) printf("\n");
	}
	return 0;
}
