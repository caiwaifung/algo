#include <cstdlib>
#include <set>
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

const int MAXN=5010;

int days(int y, int m) {
	if(m==1 || m==3 || m==5 || m==7 || m==8 || m==10 || m==12) return 31;
	if(m==4 || m==6 || m==9 || m==11) return 30;
	if(y%400==0 || (y%100!=0 && y%4==0)) return 29;
	return 28;
}

struct T {
	int Y, M, D, h, m;
	void add(int _m) {
		m+=_m;
		if(m>=60) h+=m/60, m%=60;
		if(h>=24) D+=h/24, h%=24;
		if(D>days(Y, M)) D-=days(Y, M), ++M;
		if(M>12) ++Y, M-=12;
	}
	void read() {
		scanf("%d-%d-%d %d:%d", &Y,&M,&D,&h,&m);
	}
	bool operator <(const T &b) const {
#define cmp(p, q) if(p!=q) return (p)<(q)
		cmp(Y, b.Y);
		cmp(M, b.M);
		cmp(D, b.D);
		cmp(h, b.h);
		cmp(m, b.m);
		return false;
	}
	bool operator <=(const T &b) const {
		return !(b<*this);
	}
};

pair<T,T> a[MAXN];
int n, ctime;

int main() {
	int cs; scanf("%d", &cs);
	while(cs--) {
		scanf("%d%d", &n,&ctime);
		forint(i, 1, n) {
			scanf("%*s");
			a[i].fi.read();
			a[i].se.read();
			a[i].se.add(ctime);
		}
		//printf("before sort\n");fflush(stdout);
		sort(a+1, a+n+1);
		//printf("after sort\n");fflush(stdout);
		sort(a+1, a+n+1);
		multiset<T> s;
		forint(i, 1, n) {
			if(s.size()>0) {
				T cur=*s.begin();
				if(cur<=a[i].fi)
					s.erase(s.begin());
			}
			s.insert(a[i].se);
		}
		printf("%d\n", s.size());
	}
	return 0;
}
