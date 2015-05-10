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

vector<int> a;
vector<int> basket, basket_i;
int n;

int main() {
	scanf("%d", &n); a.resize(n);
	forn(i, n) scanf("%d", &a[i]);
	basket.clear();
	for(int ci=30; ci>=0; --ci) {
		int cur=-1;
		forn(i, n) if(a[i]&(1<<ci)) { cur=a[i]; break; }
		if(cur<0) continue;
		basket.push_back(cur);
		basket_i.push_back(ci);
//		printf("ci=%d cur=%d\n", ci, cur);
		forn(i, n) if(a[i]&(1<<ci)) a[i]^=cur;
	}
	//forn(i, n) printf("%d\n", basket[i]); printf("----\n");
	forintdown(i, basket.size()-1, 0)
		forintdown(j, i-1, 0)
			if(basket[j]&(1<<basket_i[i]))
				basket[j]^=basket[i];
//	forn(i, n) printf("%d\n", basket[i]);
	int ans1=0, ans2=0;
	forn(i, n) ans1^=basket[i];
	ans2=ans1^basket.back();
	printf("%d %d\n", ans1, ans2);
	return 0;
}
