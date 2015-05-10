#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <map>
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
typedef pair<int,int> PII;
typedef vector<PII> VPI;
typedef pair<double,double> PDD;

const int MAXN=1010;

int s[MAXN][MAXN];
int a[MAXN];
int n;

int main() {
	scanf("%d", &n);
	forint(i, 1, n) forint(j, 1, n) scanf("%d", &s[i][j]);
	if(n==2) {printf("1 1\n"); return 0;}
	int t=(s[1][2]+s[1][3]+s[2][3])/2;
	a[1]=t-s[2][3];
	forint(i, 2, n) a[i]=s[1][i]-a[1];
	forint(i, 1, n) printf("%d%c", a[i], i<n?' ':'\n');
	return 0;
}
