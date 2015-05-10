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

const int MAXL=10010;

char st[55][55];
char w[MAXL];
int n, d, len;

int matched_len[55][55][MAXL];

int f[MAXL][2];

int main() {
	scanf("%d%d", &n,&d);
	forint(i, 1, n) scanf("%s", st[i]+1);
	scanf("%s", w+1); len=strlen(w+1);

	fillchar(matched_len, 0);
	forint(i, 1, n) {
		forintdown(j, d, 1)
			forint(p, 1, len)
				if(st[i][j]==w[p])
					matched_len[i][j][p]=matched_len[i][j+1][p+1]+1;
	}

	fillchar(f, 50); int maxval=f[0][0];
	f[0][0]=0;
	forint(p, 0, len-1) {
		// 0
		if(f[p][0]<maxval) {
			forint(i, 1, n) forint(j, 1, d) {
				if(j-1>p) break;
				int mat=matched_len[i][j][p+1];
				int k=p+mat;
				int z=(j+mat-1==d ? 0 : 1);
				f[k][z]=min(f[k][z], f[p][0]+1);
			}
		}
		// 1
		if(f[p][1]<maxval) {
			forint(i, 1, n) forint(j, 1, d) {
				if(j-1>p) break;
				int p2=p-j+2;
				int mat=matched_len[i][1][p2];
				int k=p2+mat-1;
				if(k>=p+1) {
					int z=(mat==d ? 0 : 1);
					f[k][z]=min(f[k][z], f[p][1]+1);
				}
			}
		}
	}
	if(f[len][0]==maxval) printf("NO\n");
		else printf("%d\n", f[len][0]);

	return 0;
}
