#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <set>
#include <map>
using namespace std;

#define _ (size_t)
#define all(a) a.begin(), a.end()
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
typedef pair<LL,LL> PLL;
typedef pair<int,int> PII;
typedef pair<double,double> PDD;
typedef vector<LL> VL;
typedef vector<int> VI;
typedef vector<PII> VPI;
typedef vector<string> VS;
template<class T> void setmax(T &a, T b) { if(b>a) a=b; }
template<class T> void setmin(T &a, T b) { if(b<a) a=b; }
template<class T> T gcd(T a, T b) { return b==0?a:gcd(b,a%b); }


// ------------------------ template ends here ------------------------ //
const int D[4][4]={
	{0, 1, 2, 3},
	{1, 4, 3, -2},
	{2, -3, 4, 1},
	{3, 2, -1, 4}};

PII m(PII a, PII b) {
	PII c;
	c.fi=a.fi*b.fi;
	c.se=D[a.se][b.se];
	if(c.se<0) c.se=-c.se, c.fi=-c.fi;
	if(c.se>3) c.se=0, c.fi=-c.fi;
	return c;
}

PII a[19999]; int n;
int cur;

bool match(PII k) {
	PII x=MP(1, 0);
	while(cur<=n) {
		x=m(x, a[cur++]);
		if(x==k) return true;
	}
	return false;
}

int main() {
	//auto t=m(MP(1,2), MP(1,3)); cout<<t.fi<<" "<<t.se<<endl;
	int cs; cin>>cs;
	forint(csi, 1, cs) {
		int times;
		static char s[19999];
		scanf("%d%d%s", &n,&times,s+1);
		forint(j, n+1, n*times) s[j]=s[j-n];
		n*=times;
		forint(i, 1, n) {
			if(s[i]=='i') a[i]=MP(1,1);
			if(s[i]=='j') a[i]=MP(1,2);
			if(s[i]=='k') a[i]=MP(1,3);
		}

		cur=1;
		bool flag=true;
		if(!match(MP(1,1))) flag=false;
		if(!match(MP(1,2))) flag=false;
		if(!match(MP(1,3))) flag=false;
		while(cur<=n) {
			if(!match(MP(1,0))) flag=false;
		}

		printf("Case #%d: %s\n",csi, flag?"YES":"NO");
	}
	return 0;
}
