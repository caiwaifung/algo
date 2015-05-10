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


int main() {
	int csn; cin>>csn;
	forint(cs, 1, csn) {
		set<int> a, b;
		a.clear();
		forint(i, 1, 16) a.insert(i);
		forn(tt, 2) {
			b.clear();
			int r; cin>>r;
			forint(i, 1, 4) forint(j, 1, 4) {
				int x; cin>>x;
				if(i==r && a.count(x)>0) b.insert(x);
			}
			a=b;
		}
		cout<<"Case #"<<cs<<": ";
		if(a.size()==0) cout<<"Volunteer cheated!"<<endl;
		else if(a.size()>1) cout<<"Bad magician!"<<endl;
		else cout<<*a.begin()<<endl;
	}
	return 0;
}
