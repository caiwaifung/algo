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
	char s[999]; scanf("%*d%s", s); int n=strlen(s);
	int c=0; forint(i, 0, n-1) c+=(s[i]=='x');
	int d=c-n/2;
	if(d<0) {
		d=-d; int cd=d;
		forn(i, n) if(s[i]=='X' && d>0) s[i]='x', --d;
		printf("%d\n%s\n", cd,s);
	} else {
		int cd=d;
		forn(i, n) if(s[i]=='x' && d>0) s[i]='X', --d;
		printf("%d\n%s\n", cd,s);
	}

	return 0;
}
