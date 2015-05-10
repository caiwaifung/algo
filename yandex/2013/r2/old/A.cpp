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

const int MAXN=110;

int n, d[MAXN];

int main() {
	int s=0;
	scanf("%d", &n); forint(i, 1, n) scanf("%d", d+i), s+=d[i];
	if(s!=(n-1)*2) printf("None\n"); else {
		for(int i=1; i<=n; )
			if(d[i]==1) d[i]=d[n--];
			else ++i;
		if(n<=2) printf("Unique\n"); else {
			bool same=true;
			forint(i, 1, n) if(d[i]!=d[1]) same=false;
			if(same) {
				if(d[1]==2 || n==3)
					printf("Unique\n");
				else
					printf("Multiple\n");
			} else {
				printf("Multiple\n");
			}
		}
	}
	return 0;
}
