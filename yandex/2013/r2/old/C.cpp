#include <iostream>
#include <sstream>
#include <algorithm>
#include <set>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

typedef long long LL;
typedef pair<int,int> PII;
typedef vector<int> VI;
#define PB push_back
#define MP make_pair
#define forint(i, a, b) for(int i=(int)(a); i<=(int)(b); ++i)
#define forintdown(i, a, b) for(int i=(int)(a); i>=(int)(b); --i)
#define forn(i, n) for(int i=0; i<(int)(n); ++i)
#define forndown(i, n) for(int i=(int)(n)-1; i>=0; --i)
#define fillchar(a, x) memset(a, x, sizeof(a))
template<class T> void setmin(T &a, T b) { if(b<a) a=b; }
template<class T> void setmax(T &a, T b) { if(b>a) a=b; }
template<class T> T gcd(T a, T b) { return b==0 ? a : gcd(b,a%b); }

const int MAXN=2020;

struct Point {
	int x, y;
	friend bool operator <(const Point &a, const Point &b) {
		LL tmp=(LL)a.x*(LL)b.y - (LL)a.y*(LL)b.x;
		return tmp>0;
	}
};

Point a[MAXN];
int n;
Point b[MAXN];
int num;

double v1, v2;
void compute() {
	if(num<=1) return;
	sort(b+1, b+num+1);
	double sx=0, sy=0;
	forintdown(i, num, 1) {
		v1+=b[i].x*sy - b[i].y*sx;
		v2+=num-i;
		sx+=b[i].x, sy+=b[i].y;
	}
}

int main() {
	scanf("%d", &n);
	forint(i, 1, n) scanf("%d%d", &a[i].x,&a[i].y);
	v1=v2=0.;
	forint(i, 1, n) {
		num=0;
		forint(j, 1, n) {
			int x=a[j].x-a[i].x;
			int y=a[j].y-a[i].y;
			if(x>0 || (x==0 && y>0)) {
				++num; b[num].x=x; b[num].y=y;
			}
		}
		compute();
	}
	double ans=v1/v2/2.;
	printf("%.15lf\n", ans);
	return 0;
}
