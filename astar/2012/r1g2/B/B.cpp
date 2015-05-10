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

const int MAX_N=1010;

struct Point {
	double x, y, z;
	//Point(double _x, double _y, double _z) : x(_x), y(_y), z(_z) { }
	void read() { scanf("%lf%lf%lf", &x, &y, &z); }
	double dif(const Point &tmp) { return sqr(x-tmp.x)+sqr(y-tmp.y)+sqr(z-tmp.z); }
} a[MAX_N];
int N, K;
bool vis[MAX_N];

void visit(int x, double limit) {
	vis[x]=true;
	forint(y, 1, N)
		if(!vis[y] && a[x].dif(a[y])<=limit)
			visit(y, limit);
}

int main() {
	scanf("%d%d", &N, &K);
	forint(i, 1, N) a[i].read();
	double le=0., ri=10.;
	forn(ttt, 50) {
		double mid=(le+ri)/2.;
		int cnt=0;
		fillchar(vis, false);
		forint(i, 1, N) if(!vis[i]) { visit(i, mid), ++cnt; }
		//printf("mid=%.6lf cnt=%d\n", mid, cnt);
		if (cnt>=K) le=mid;
			else ri=mid;
	}
	printf("%.6lf\n", le);
	return 0;
}
