#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
#define forint(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define fillchar(a, x) memset(a, x, sizeof(a))
#define forintdown(i, a, b) for(int i=int(a); i>=int(b); --i)

const int MAXN=10010;
const int MAXLen=100;

struct Num {
	//*
	int a[MAXLen], n;
	Num() {
		n=0;
		fillchar(a, 0);
	}
	void set_val(int x) {
		fillchar(a, 0);
		n=1; a[1]=x;
	}
	void print() {
		while(n>0 && a[n]==0) --n;
		forintdown(i, n, 1) printf("%d", a[i]);
		if(n==0) printf("0");
		printf("\n");
	}
	void add(const Num &b) {
		while(n<b.n) a[++n]=0;
		forint(i, 1, b.n) a[i]+=b.a[i];
		forint(i, 1, n-1) {
			a[i+1]+=a[i]/10;
			a[i]%=10;
		}
		while(a[n]>=10) {
			a[n+1]=a[n]/10;
			a[n]%=10;
			++n;
		}
	}
	/*/
	ULL a;
	Num() : a(0) {}
	void set_val(int x) { a=x; }
	void print() { cout<<a<<endl; }
	void add(const Num &b) { a+=b.a; }
	//*/
};

void solve() {
	static char s[MAXN];
	int n;
	scanf("%s", s+1); n=strlen(s+1);
	
	static Num f[11];
	fillchar(f, 0);
	f[0].set_val(1);

	forint(i, 1, n) {
		int c=int(s[i]-'0');
		forint(j, 0, c) f[c+1].add(f[j]);
	}
	Num ans;
	forint(i, 1, 10)
		ans.add(f[i]);
	ans.print();
	/*
	static LL f[MAXN];
	s[0]='0'-1;
	f[0]=1;
	LL ans=0;
	forint(i, 1, n) {
		f[i]=0;
		forint(j, 0, i-1) if(s[j]<s[i])
			f[i]+=f[j];
		ans+=f[i];
		//if(s[i]=='0') ++ans;
	}
	*/
}

int main() {
	int t; scanf("%d", &t);
	forint(cs, 1, t) {
		printf("Case %d: ", cs);
		solve();
	}
	return 0;
}
