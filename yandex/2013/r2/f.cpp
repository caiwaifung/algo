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

void make(int &x) {
	scanf("%d", &x);
	if(x>50) x-=(x-50)/2*2;
	while(x>50) x-=2;
}

bool f[55][55][55][3][3][3];

int main() {
	int p, q, r;
	make(p);
	make(q);
	make(r);
	char buf[5]; scanf("%s", buf);
	int target[3];
	forn(i, 3) {
		if(buf[i]=='R') target[i]=0;
		if(buf[i]=='G') target[i]=1;
		if(buf[i]=='B') target[i]=2;
	}
	fillchar(f, false);
	f[p][q][r][0][1][2]=true;
	forintdown(a, p, 0) forintdown(b, q, 0) forintdown(c, r, 0)
		forint(x, 0, 2) forint(y, 0, 2) forint(z, 0, 2) {
			if(!f[a][b][c][x][y][z]) continue;
			if(a>0) f[a-1][b][c][y][x][z]=true;
			if(b>0) f[a][b-1][c][z][y][x]=true;
			if(c>0) f[a][b][c-1][x][z][y]=true;
		}
	printf("%s\n", f[0][0][0][target[0]][target[1]][target[2]]?"Yes":"No");
	return 0;
}
