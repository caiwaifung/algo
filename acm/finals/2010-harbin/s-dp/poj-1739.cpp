// 10:18 - 10:39 wa sample
// 10:39 - 10:43 pass sample - ac
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

#define forint(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define forn(i, n) forint(i, 0, (n)-1)
#define forintdown(i, a, b) for(int i=int(a); i>=int(b); --i)
#define forndown(i, n) forintdown(i, (n)-1, 0)
#define fillchar(a, x) memset(a, x, sizeof(a))
typedef long long LL;

const int MAXR=8;
const int MAXC=8;
const int MAXS=20000; // 3^9

bool valid[MAXR][MAXC];
int r, c, s_cnt;

bool init() {
	scanf("%d%d", &r,&c);
	if(r==0 && c==0)
		return false;
	forndown(i, r) {
		char buf[88]; scanf("%s", buf);
		forn(j, c)
			valid[i][j]=(buf[j]=='.');
	}
	s_cnt=1;
	forn(i, c+1) s_cnt*=3;
	return true;
}

struct State {
	int a[MAXC+1];
	void set(int i, int v) {
		a[i]=v;
	}
	void set(int i, int v1, int v2) {
		a[i]=v1, a[i+1]=v2;
	}
	void get_op(int op[]) {
		static int stack[MAXC+1];
		int top=0;
		forint(i, 0, c) {
			op[i]=-1;
			if(a[i]==1)
				stack[++top]=i;
			if(a[i]==2) {
				op[i]=stack[top];
				op[stack[top]]=i;
				--top;
			}
		}
	}
};

State decode(int s) {
	State a;
	forint(i, 0, c)
		a.a[i]=s%3, s/=3;
	return a;
}

int encode(const State &a) {
	int s=0;
	forintdown(i, c, 0)
		s=s*3+a.a[i];
	return s;
}

int make_start_s() {
	State a;
	fillchar(a.a, 0);
	a.a[1]=1, a.a[c]=2;
	return encode(a);
}

LL trans(LL f1[], LL f2[], int i, int j) {
	LL tmp=0;
	forn(s, s_cnt) {
		LL val=f1[s];
		if(val==0)
			continue;
		//printf("i=%d j=%d s=%d v=%I64d\n", i,j,s,val);

		State a=decode(s);

		if(!valid[i][j]) {
			if(a.a[j]==0 && a.a[j+1]==0)
				f2[s]+=val;
			continue;
		}

		if(a.a[j]==0 && a.a[j+1]==0) {
			State b=a; b.set(j, 1, 2);
			f2[encode(b)]+=val;
		}
		if((a.a[j]>0 && a.a[j+1]==0) || (a.a[j]==0 && a.a[j+1]>0)) {
			f2[s]+=val;
			State b=a; b.set(j, a.a[j+1], a.a[j]);
			f2[encode(b)]+=val;
		}
		if(a.a[j]>0 && a.a[j+1]>0) {
			if(a.a[j]==2 && a.a[j+1]==1) {
				State b=a; b.set(j, 0, 0);
				f2[encode(b)]+=val;
			}
			if(a.a[j]==a.a[j+1]) {
				int op[MAXC+1]; a.get_op(op);
				int x=op[j], y=op[j+1];
				if(x>y) swap(x, y);
				State b=a;
				b.set(j, 0, 0); b.set(x, 1), b.set(y, 2);
				f2[encode(b)]+=val;
			}
			if(a.a[j]==1 && a.a[j+1]==2) {
				State b=a; b.set(j, 0, 0);
				int t=encode(b);
				if(t==0) tmp+=val;
			}
		}
	}
	return tmp;
}

void trans_row(LL f1[], LL f2[]) {
	forn(s, s_cnt) {
		State a=decode(s);
		if(a.a[c]==0) {
			forintdown(i, c, 1) a.a[i]=a.a[i-1];
			a.a[0]=0;
			f2[encode(a)]+=f1[s];
		}
	}
}

void solve() {
	static LL f[2][MAXS];
	int o1=0, o2=1;
	LL ans=0;
	fillchar(f[o1], 0);
	f[o1][make_start_s()]=1;
	forn(i, r) {
		forn(j, c) {
			fillchar(f[o2], 0);
			LL tmp=trans(f[o1], f[o2], i, j);
			if(valid[i][j])
				ans=tmp;
			swap(o1, o2);
		}

		fillchar(f[o2], 0);
		trans_row(f[o1], f[o2]);
		swap(o1, o2);
	}
	cout<<ans<<endl;
}

int main() {
	while(init())
		solve();
	return 0;
}
