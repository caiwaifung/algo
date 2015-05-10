#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
using namespace std;

typedef long long int64;
typedef unsigned long long qword;
template <class T> T abs_val(T x) { return x > 0 ? x : -x; }
template <class T> T sqr(T x) { return x*x; }
template <class T> T gcd(T a, T b) { return b == 0 ? a : gcd(b, a%b); }
template <class T> void set_max(T &a, T b) { if (a < b) a = b; }
template <class T> void set_min(T &a, T b) { if (a > b) a = b; }
#define fillchar(a, x) memset(a, x, sizeof(a))
#define movechar(a, b) memmove(b, a, sizeof(a))
#define forn(i, n) for (int i = 0; i < (int)(n); ++ i)
#define forint(i, s, t) for (int i = (int)(s); i <= (int)(t); ++ i)
#define forintdown(i, s, t) for (int i = (int)(s); i >= (int)(t); -- i)
#define forall(it, a) for (typeof(a.begin()) it = a.begin(); it != a.end(); ++ it)

const int n=25;

int a[n];
int ans1, ans2;

void dfs(int i, int cur) {
	if(i==n) {
		if(cur>ans2) ans2=cur;
		if(ans2>ans1) swap(ans1, ans2);
		return;
	}
	dfs(i+1, cur); dfs(i+1, cur^a[i]);
}

void gen() {
	forn(i, n) {
		a[i]=0; forn(j, 31) if(rand()%2) a[i]^=(1<<j);
	}
	FILE *f=fopen("in1", "w");
	fprintf(f, "%d\n", n); forn(i, n) fprintf(f, "%d ", a[i]); fprintf(f, "\n");
	fclose(f);
	
	ans1=ans2=0;
	dfs(0, 0);
	//f=fopen("ans1", "w"); fprintf(f, "%d %d\n", ans1, ans2); fclose(f);
}

int main() {
	srand(1234631);
	for(int cs=1; ; ++cs) {
		printf("Case %d: ", cs);
		gen();
		system("./a.out <in1 >ou1");
		int ou1, ou2;
		FILE *f=fopen("ou1", "r"); fscanf(f, "%d%d", &ou1, &ou2); fclose(f);
		if(ans1==ou1 && ans2==ou2) printf("correct. %d %d\n", ans1, ans2);
			else {printf("err!\n"); for(;;);}
	}
	return 0;
}
