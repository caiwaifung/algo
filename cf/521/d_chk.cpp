#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <set>
#include <map>
using namespace std;

#define _ (size_t)
#define all(a) a.begin(), a.end()
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
typedef vector<string> VS;
typedef vector<int> VI;
typedef vector<PII> VPI;
template<class T> void setmax(T &a, T b) { if(b>a) a=b; }
template<class T> void setmin(T &a, T b) { if(b<a) a=b; }
template<class T> T gcd(T a, T b) { return b==0?a:gcd(b,a%b); }


// ------------------------ template ends here ------------------------ //

const int N=3;
const int P=3, Q=2;
const int V=5;
int a[N], pt[P], pi[P], pb[P];
LL stdans, ans;

void gen() {
	FILE *f=fopen("d.in", "w");
	fprintf(f, "%d %d %d\n", N, P, Q);
	forn(i, N) fprintf(f, "%d ", a[i]=rand()%V+1); fprintf(f, "\n");
	forn(i, P) {
		pt[i]=rand()%3+1;
		pi[i]=rand()%N;
		pb[i]=rand()%V+1;
		fprintf(f, "%d %d %d\n", pt[i],pi[i]+1,pb[i]);
	}
	fclose(f);
}

void run_vio() {
	stdans=0;
	forn(st, 1<<P) {
		int cnt=0; forn(i, P) if(st&(1<<i)) ++cnt;
		if(cnt>Q) continue;
		LL b[N]; forn(i, N) b[i]=a[i];
		forn(i, P) if(st&(1<<i)) if(pt[i]==1) b[pi[i]]=pb[i];
		forn(i, P) if(st&(1<<i)) if(pt[i]==2) b[pi[i]]+=pb[i];
		forn(i, P) if(st&(1<<i)) if(pt[i]==3) b[pi[i]]*=pb[i];
		LL tmp=1; forn(i, N) tmp*=b[i];
		setmax(stdans, tmp);
		//printf("st=%d tmp=%lld\n",st,tmp);
	}
	//printf("finish\n");
}

void run_mine() {
	//printf("mine\n");
	system("./d <d.in >d.out");
	FILE *f=fopen("d.out", "r");
	int p; fscanf(f, "%d", &p);
	LL b[N]; forn(i, N) b[i]=a[i];
	forn(k, p) {
		int i; fscanf(f, "%d", &i);
		--i;
		if(pt[i]==1) b[pi[i]]=pb[i];
		if(pt[i]==2) b[pi[i]]+=pb[i];
		if(pt[i]==3) b[pi[i]]*=pb[i];
	}
	LL tmp=1; forn(i, N) tmp*=b[i];
	ans=tmp;
	fclose(f);
}

int main() {
	for(int cs=1; ; ++cs) {
		printf("Case %d [", cs); fflush(stdout);
		gen();
		printf("."); fflush(stdout);

		run_vio();
		printf("."); fflush(stdout);

		run_mine();
		printf(".] "); fflush(stdout);

		if(stdans==ans) {
			printf("correct -> ans=%lld\n", ans);
			fflush(stdout);
		}
		else {
			printf("error. (ans=%lld, stdans=%lld)", ans, stdans);
			fflush(stdout);
			for(;;);
		}
	}
	return 0;
}
