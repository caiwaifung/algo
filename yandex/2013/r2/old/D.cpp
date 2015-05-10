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
template<class T> T gcd(T a, T b) { return b==0 ? a : gcd(b,a%b); }

int main() {
	int x, y, z; scanf("%d%d%d", &x,&y,&z);
	bool b1, b2, b3, b4;
	b1=(x+y==z);
	b2=(x==y+z);
	b3=((LL)x*(LL)y==(LL)z);
	b4=((LL)x==(LL)y*(LL)z);
	if(y==0) b4=false;
	int c=0;
	if(b1) ++c;
	if(b2) ++c;
	if(b3) ++c;
	if(b4) ++c;
	if(c!=1) {
		printf("Invalid\n");
	} else if(b1) printf("+\n");
	else if(b2) printf("-\n");
	else if(b3) printf("*\n");
	else if(b4) printf("/\n");
	return 0;
}
