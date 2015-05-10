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

const int LIM=20;
bool f[LIM+5][LIM+5][LIM+5][3][3];

int main() {
	int p, q, r;
	scanf("%d%d%d", &p,&q,&r);
	if(p>LIM) p-=(p-LIM)/2*2; while(p>LIM) p-=2;
	if(q>LIM) q-=(q-LIM)/2*2; while(q>LIM) q-=2;
	if(r>LIM) r-=(r-LIM)/2*2; while(r>LIM) r-=2;
	fillchar(f, false);
	f[p][q][r][0][1]=true;
	forintdown(cp, p, 0) forintdown(cq, q, 0) forintdown(cr, r, 0)
		forint(x0, 0, 2) forint(x1, 0, 2) {
			if(!f[cp][cq][cr][x0][x1]) continue;
			int x2=3-x0-x1;
			if(cp>0) {
				swap(x0, x1);
				f[cp-1][cq][cr][x0][x1]=true;
				swap(x0, x1);
			}
			if(cq>0) {
				swap(x0, x2);
				f[cp][cq-1][cr][x0][x1]=true;
				swap(x0, x2);
			}
			if(cr>0) {
				swap(x1, x2);
				f[cp][cq][cr-1][x0][x1]=true;
				swap(x1, x2);
			}
		}
	char s[99]; scanf("%s", s);
	int x0, x1;
	if(s[0]=='R') x0=0;
	else if(s[0]=='G') x0=1; 
	else x0=2;
	if(s[1]=='R') x1=0;
	else if(s[1]=='G') x1=1; 
	else x1=2;
	printf("%s\n", f[0][0][0][x0][x1]?"Yes":"No");

	return 0;
}
