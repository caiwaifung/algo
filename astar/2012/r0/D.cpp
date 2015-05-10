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

int main() {
	int cs; scanf("%d", &cs);
	while (cs --) {
		int h, m;
		scanf("%d:%d", &h, &m);
		printf("%d\n", m == 0 ? ((h+11)%24+1) : 0);
	}
	return 0;
}
