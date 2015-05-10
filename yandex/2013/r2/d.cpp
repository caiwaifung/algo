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

int main() {
	LL x, y, z; cin>>x>>y>>z;
	vector<char> ans;
	if(x+y==z) ans.PB('+');
	if(x-y==z) ans.PB('-');
	if(x*y==z) ans.PB('*');
	if(y!=0 && x==z*y) ans.PB('/');
	if(ans.size()==1) cout<<ans[0]<<endl;
	else cout<<"Invalid"<<endl;
	return 0;
}
