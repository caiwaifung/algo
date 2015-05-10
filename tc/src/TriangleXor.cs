#include <iostream>
#include <sstream>
#include <algorithm>
#include <set>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

typedef long long LL;
typedef pair<int,int> PII;
typedef vector<int> VI;
#define PB push_back
#define MP make_pair
#define forint(i, a, b) for(int i=(int)(a); i<=(int)(b); ++i)
#define forintdown(i, a, b) for(int i=(int)(a); i>=(int)(b); --i)
#define forn(i, n) for(int i=0; i<(int)(n); ++i)
#define forndown(i, n) for(int i=(int)(n)-1; i>=0; --i)
#define fillchar(a, x) memset(a, x, sizeof(a))
template<class T> void setmin(T &a, T b) { if(b<a) a=b; }
template<class T> void setmax(T &a, T b) { if(b>a) a=b; }

class TriangleXor {
public:
	int theArea(int W) {
		double ans=0;
		int cnt=1000;
		forn(cnti, cnt) {
			double y=(double)(cnti+0.1)/(double)cnt;
			vector<double> le, ri;
			forint(i, 0, W) {
				double l=(double)i*y;
				double r=(double)W-(double)(W-i)*y;
				le.PB(l), ri.PB(r);
				//printf("i=%d l=%.5lf r=%.5lf\n",i,l,r);
			}
			double cur=0.;
			int c=0;
			for(int i=0, j=0; i<(int)le.size() || j<(int)ri.size(); ) {
				double nxt; bool sl;
				if(i<(int)le.size()) nxt=le[i], sl=true;
					else nxt=ri[j], sl=false;
				if(j<(int)ri.size() && ri[j]<nxt)
					nxt=ri[j], sl=false;
				if(c%2!=0) ans+=(nxt-cur);
				//printf("c=%d cur=%.9lf nxt=%.8lf p=%.8lf\n",c,cur,nxt,nxt-cur);
				cur=nxt;
				if(sl) ++i, ++c;
					else ++j, --c;
			}
		}
		ans/=(double)cnt;
		//printf("ans=%.9lf\n", ans);
		int ret=(int)(ans+1E-4);
		return ret;
	}


};


// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
