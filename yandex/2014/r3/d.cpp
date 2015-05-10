#include <cstdlib>
#include <cassert>
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

const int MAXLen=100010;
const LL INFI=1LL<<40;

void die() {
	printf("-1\n"); exit(0);
}

struct Num {
	LL a[MAXLen];
	int len;
	void init(char *s) {
		len=strlen(s);
		forint(i, 1, len) a[i]=char(s[len-i]-'0');
	}
	void make_palin() {
		for(int i=len, j=1; i>j; --i, ++j)
			a[j]=a[i];
	}
	int get_m() {
		if(len%2==0) return len/2+1;
		else return len/2+1;
	}
	LL up_v() {
		int m=get_m();
		LL ans=0;
		forintdown(i, len, m) {
			ans=ans*10+9-a[i];
			ans=min(ans, INFI);
		}
		return ans;
	}
	LL dn_v() {
		int m=get_m();
		LL ans=0;
		forintdown(i, len, m) {
			int cur=0;
			if(len>1 && i==len) cur=1;
			ans=ans*10+a[i]-cur;
			ans=min(ans, INFI);
		}
		return ans;
	}
	void add(LL x) {
		int m=get_m();
		forint(i, m, len) {
			a[i]+=x;
			x=a[i]/10, a[i]%=10;
		}
	}
	void dec(LL x) {
		int m=get_m();
		x=-x;
		forint(i, m, len) {
			a[i]+=x;
			x=a[i]/10, a[i]%=10;
			if(a[i]<0) a[i]+=10, --x;
		}
	}
	bool operator <(const Num &p) const {
		assert(len==p.len);
		forintdown(i, len, 1)
			if(a[i]!=p.a[i])
				return a[i]<p.a[i];
		return false;
	}
};

void output(const Num &a) {
	forintdown(i, a.len, 1) printf("%d", (int)a.a[i]);
	printf("\n");
	exit(0);
}

int main() {
	static char buf[MAXLen];
	scanf("%s", buf);
	static Num n, m;
	bool neg;
	if(buf[0]=='-') n.init(buf+1), neg=true;
		else n.init(buf), neg=false;
	LL k; cin>>k;

	if(neg) {
		if(k<0) die();
		if(k==1) {
			printf("0\n"); exit(0);
		}
		--k, n.len=1, n.a[1]=0;
	}
	if(k>0) {
		m=n;
		m.make_palin();
		if(n<m) {
			--k; if(k==0) output(m);
		}
		while(1) {
			LL t=m.up_v();
			if(t>=k) break;
			k-=t;
			++m.len; forint(i, 1, m.len) m.a[i]=0; m.a[m.len]=1;
			m.make_palin();
			if(k==1) output(m);
			--k;
		}
		m.add(k);
		m.make_palin();
		output(m);
	} else {
		k=-k;
		m=n;
		m.make_palin();
		if(m<n) {
			--k; if(k==0) output(m);
		}
		while(1) {
			//printf("k=%I64d\n",k);
			LL t=m.dn_v();
			if(t>=k) break;
			if(m.len==0) die();
			k-=t;
			--m.len; forint(i, 1, m.len) m.a[i]=9;
			if(k==1) output(m);
			--k;
		}
		m.dec(k);
		m.make_palin();
		output(m);
	}

	return 0;
}
