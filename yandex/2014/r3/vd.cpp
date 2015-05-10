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


bool ok(int n) {
	int t=n, p=0;
	while(t>0) p=p*10+(t%10), t/=10;
	return p==n;
}

int cal(int n, int k) {
	if(k>0) {
		while(1) {
			++n; if(ok(n))--k;
			if(k==0) return n;
		}
	} else {
		while(1) {
			--n; if(n<0) return -1;
			if(ok(n)) ++k;
			if(k==0) return n;
		}
	}
}

int main() {
	for(int cs=1; ; ++cs) {
int n, k;
		n=rand()%10001-5000;
		do {k=rand()%101-50;}while(k==0);
		FILE *f=fopen("d.in", "w");
		fprintf(f,"%d %d\n",n,k);
		fclose(f);
		system("d <d.in >d.out");
		int ans=0;
		f=fopen("d.out", "r");
		fscanf(f, "%d", &ans);
		fclose(f);
		int t=cal(n,k);
		if(ans!=t) {
			printf("error n=%d k=%d ans=%d t=%d\n",n,k,ans,t);
			for(;;);
		} else printf("ok. n=%d k=%d ans=%d\n",n,k,ans);
	}
	return 0;
}
