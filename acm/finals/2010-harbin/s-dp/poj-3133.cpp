// 11:02 - 11:32 wa sample
// 11:47 pass sample - ac
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

const int MAXR=9;
const int MAXC=9;
const int MAXSV=9990000; // 5^10
const int MAXS=99999;

const int LE=1;
const int RI=2;
const int PA=3;
const int PB=4;

// global data

int g[MAXR][MAXC]; // 0:obstacle 1:empty PA/PB:A/B
int r, c;

bool init() {
	scanf("%d%d", &r,&c);
	if(r==0 && c==0) return false;
	forn(i, r) forn(j, c) {
		int x; scanf("%d", &x);
		if(x==0) g[i][j]=1;
		else if(x==1) g[i][j]=0;
		else if(x==2) g[i][j]=PA;
		else if(x==3) g[i][j]=PB;
	}
	return true;
}

// about state hashing

int s_id[MAXSV], s_val[MAXS];
int s_cnt;

void s_init() {
	fillchar(s_id, 0xff);
	s_cnt=0;
}

int get_id(int s) {
	if(s_id[s]<0) {
		s_id[s]=s_cnt;
		s_val[s_cnt]=s;
		++s_cnt;
	}
	return s_id[s];
}

// about state operations

bool is_lr(int x) {
	return x==LE || x==RI;
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
			if(a[i]==LE)
				stack[top++]=i;
			if(a[i]==RI) {
				--top;
				op[i]=stack[top];
				op[stack[top]]=i;
			}
		}
	}

	bool connect(int i, int j) {
		if(is_lr(a[i]) && is_lr(a[j])) {
			int op[MAXC+1]; get_op(op);
			int x=op[i], y=op[j];
			if(x==j)
				return false;
			if(x>y)
				swap(x, y);
			set(i, 0), set(j, 0);
			set(x, LE), set(y, RI);
			return true;
		}
		if(is_lr(a[j])) {
			int op[MAXC+1]; get_op(op);
			set(op[j], a[i]);
			set(i, 0), set(j, 0);
			return true;
		}
		if(is_lr(a[i]))
			return connect(j, i);
		// both A/B now
		if(a[i]==a[j]) {
			set(i, 0), set(j, 0);
			return true;
		} else
			return false;
	}

	bool make_start(int i, int type) {
		if(is_lr(a[i])) {
			int op[MAXC+1]; get_op(op);
			set(op[i], type);
			set(i, 0);
			return true;
		}
		if(a[i]==type) {
			set(i, 0);
			return true;
		} else
			return false;
	}
};

State decode(int s) {
	State a;
	forint(i, 0, c)
		a.a[i]=s%5, s/=5;
	return a;
}

int encode(const State &a) {
	int s=0;
	forintdown(i, c, 0)
		s=s*5+a.a[i];
	return s;
}

// main proc

LL max_val;

inline void upt(LL &a, LL b) {
	if(b<a) a=b;
}

string _(int s) {
	State a=decode(s);
	string t;
	forint(i, 0, c) t+=char('0'+a.a[i]);
	return t;
}

void trans(LL f1[], LL f2[], int i, int j) {
	forn(si, s_cnt) {
		LL val=f1[si];
		if(val==max_val)
			continue;
		int s=s_val[si];
		State a=decode(s);
		//printf("i=%d j=%d si=%d s=%s v=%I64d\n",i,j,si,_(s).c_str(),val);

		if(g[i][j]==0) {
			if(a.a[j]==0 && a.a[j+1]==0)
				upt(f2[si], val);
			continue;
		}

		if(g[i][j]==PA || g[i][j]==PB) {
			if(a.a[j]==0 && a.a[j+1]==0) {
				State b;
				b=a; b.set(j, g[i][j]);
				upt(f2[get_id(encode(b))], val+1);
				b=a; b.set(j+1, g[i][j]);
				upt(f2[get_id(encode(b))], val+1);
			}
			else if(a.a[j]>0 && a.a[j+1]==0) {
				State b=a;
				if(b.make_start(j, g[i][j]))
					upt(f2[get_id(encode(b))], val);
			}
			else if(a.a[j]==0 && a.a[j+1]>0) {
				State b=a;
				if(b.make_start(j+1, g[i][j]))
					upt(f2[get_id(encode(b))], val);
			}
			continue;
		}

		// now g[i][j]=empty
		if(a.a[j]==0 && a.a[j+1]==0) {
			upt(f2[si], val);
			State b=a; b.set(j, 1, 2);
			upt(f2[get_id(encode(b))], val+2);
		}
		else if(a.a[j]==0 || a.a[j+1]==0) {
			upt(f2[si], val+1);
			State b=a; b.set(j, a.a[j+1], a.a[j]);
			upt(f2[get_id(encode(b))], val+1);
		}
		else {
			State b=a;
			if(b.connect(j, j+1))
				upt(f2[get_id(encode(b))], val);
		}
	}
}

void trans_row(LL f1[], LL f2[]) {
	forn(si, s_cnt) {
		LL val=f1[si];
		if(val==max_val)
			continue;
		int s=s_val[si];
		State a=decode(s);
		if(a.a[c]==0) {
			forintdown(k, c, 1) a.a[k]=a.a[k-1];
			a.a[0]=0;
			upt(f2[get_id(encode(a))], val);
		}
	}
}

void solve() {
	LL f[2][MAXS];
	int o1=0, o2=1;

	s_init();
	fillchar(f[o1], 50); max_val=f[o1][0];
	f[o1][get_id(0)]=0;
	forn(i, r) {
		forn(j, c) {
			fillchar(f[o2], 50);
			trans(f[o1], f[o2], i, j);
			swap(o1, o2);
		}
		fillchar(f[o2], 50);
		trans_row(f[o1], f[o2]);
		swap(o1, o2);
	}

	LL ans=f[o1][0];
	if(ans==max_val) ans=0;
	cout<<ans<<endl;
}

int main() {
	while(init()) {
		solve();
		//break;
	}
	return 0;
}
