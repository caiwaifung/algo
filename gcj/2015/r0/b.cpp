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

int D, P[1010];

bool ok(int TL) {
	forint(x, 0, TL-1) {
		int t=TL-x, r=x;
		forint(i, 1, D) {
			int need=(P[i]-1)/t+1;
			r-=need-1;
		}
		if(r>=0) return true;
	}
	return false;
}

int main() {
	int cs; cin>>cs;
	forint(csi, 1, cs) {
		scanf("%d", &D); forint(i, 1, D) scanf("%d", &P[i]);
		int le=0, ri=1010;
		while(le<ri) {
			int mid=(le+ri)/2;
			if(ok(mid)) ri=mid;
				else le=mid+1;
		}
		printf("Case #%d: %d\n",csi, le);
	}
	return 0;
}
