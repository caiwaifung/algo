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

unsigned a[1<<21];
unsigned ts[6][5];
unsigned tt[6][5];

int main() {
	freopen("forbidden-words.in", "r", stdin);
	freopen("forbidden-words.out", "w", stdout);
#define bit(i) (1u<<int(i))
	fillchar(ts, 0);
	fillchar(tt, 0);
	forn(s, 32) {
		int cnt=0;
		forn(i, 5) if(s&bit(i)) ++cnt;
		forn(i, 5) if(s&bit(i)) {
			ts[cnt][i]|=bit(s);
			tt[cnt][i]|=bit(s^31);
		}
	}

	fillchar(a, 0);
	int n; scanf("%d", &n);
	while(n--) {
		unsigned cur=0; // [0,2^26)
		static char s[3000030];
		scanf("%s", s);
		int len=strlen(s);
		forn(i, len) cur|=bit(s[i]-'a');
		a[cur>>5]|=bit(cur&31);
	}

	//printf("a[0]=%x\n",a[0]);
	forn(st, 1<<21) {
		unsigned &ca=a[st];
		forintdown(cnt, 5, 1) forn(i, 5) {
			unsigned cur=tt[cnt][i];
			cur=cur&ca;
			cur=cur<<bit(i);
			ca|=cur;
		}
		forn(i, 21) if((st&bit(i))==0)
			a[st^bit(i)]|=ca;
	}
	forndown(st, 1<<21) {
		unsigned &ca=a[st];
		forintdown(cnt, 5, 1) forn(i, 5) {
			unsigned cur=ts[cnt][i];
			cur=cur&~ca;
			// i : [0,5)
			// bit(i) : [0,16)
			cur=cur>>bit(i);
			ca|=cur;
		}
		forn(i, 21) if(st&bit(i))
			a[st^bit(i)]|=~ca;
	}
	//printf("a[0]=%x\n",a[0]);
	printf("%s\n", ((a[0]&1)==1 ? "First" : "Second"));
	return 0;
}
