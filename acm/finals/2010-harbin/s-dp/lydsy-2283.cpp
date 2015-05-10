// 19:24 - 19:39 found some problem about number of states - decide use hashing
// 19:50 - 20:30 wa sample
// 20:30 - 20:45 found some bugs and have dinner now
// 21:15 - 21:26 pass sample - wa
// 21:26 - 21:28 found bug that forget MOD - wa
// 21:28 - 21:30 found bug that forget NO SOLUTION - ac
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

#define forint(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define forintdown(i, a, b) for(int i=int(a); i>=int(b); --i)
#define forn(i, n) forint(i, 0, (n)-1)
#define forndown(i, n) forintdown(i, (n)-1, 0)
#define fillchar(a, x) memset(a, x, sizeof(a))
#define MP make_pair
#define fi first
#define se second
typedef long long LL;
typedef pair<int,int> PII;

const int MAXN=12;
const int MAXS=int(1e6+7);
const int MAXVal=1<<30;
const int MOD=int(1e9+7);

const int EMPTY=1;
const int LE=1;
const int RI=2;
const int SA=3;
const int SB=4;
const int SC=5;

void die() {
	for(;;);
}

// global info

int ga[MAXN][MAXN], gb[MAXN][MAXN];
int n;

int read_int() {
	int x; scanf("%d", &x);
	return x;
}

int parse_g(int x) {
	if(x==0) return EMPTY;
	if(x==1) return SA;
	if(x==2) return SB;
	if(x==3) return SC;
	return 0;
}

bool is_lr(int x) {
	return x==LE || x==RI;
}
bool is_label(int x) {
	return x==SA || x==SB || x==SC;
}

bool init() {
	if(scanf("%d", &n)<1)
		return false;
	forn(i, n*2)
		forn(j, n*2)
			ga[i][j]=gb[i][j]=0;
	forn(i, n) {
		forn(j, n+i) {
			ga[i][j]=parse_g(read_int());
			gb[i][j]=parse_g(read_int());
		}
		ga[i][n+i]=parse_g(read_int());
	}
	forn(i, n) {
		gb[n+i][i]=parse_g(read_int());
		forint(j, i+1, 2*n-1) {
			ga[n+i][j]=parse_g(read_int());
			gb[n+i][j]=parse_g(read_int());
		}
	}
	n*=2;
	return true;
}

// state handling

struct State {
	int a[MAXN+2]; // [0..n+1]

	void set(int i, int v) {
		a[i]=v;
	}
	void set(int i, int v1, int v2) {
		a[i]=v1, a[i+1]=v2;
	}

	void get_op(int op[]) {
		static int stack[MAXN+2];
		int top=0;
		forint(i, 0, n+1) {
			op[i]=0;
			if(a[i]==LE) {
				stack[top++]=i;
			}
			if(a[i]==RI) {
				--top;
				op[stack[top]]=i;
				op[i]=stack[top];
			}
		}
	}
	
	bool make_start(int i, int cur) {
		if(is_lr(a[i])) {
			int op[MAXN+2]; get_op(op);
			a[i]=0;
			a[op[i]]=cur;
			return true;
		} 
		if(a[i]==cur) {
			a[i]=0;
			return true;
		}
		return false;
	}

	bool connect(int i, int j) {
		if(!is_lr(a[i])) {
			int t=a[i]; a[i]=0;
			return make_start(j, t);
		}
		if(!is_lr(a[j]))
			return connect(j, i);

		// now both L/R
		int op[MAXN+2]; get_op(op);
		if(op[i]==j)
			return false;
		int x=op[i], y=op[j];
		if(x>y) swap(x, y);
		a[i]=a[j]=0;
		a[x]=LE, a[y]=RI;
		return true;
	}

	bool move_row() {
		if(a[n]!=0 || a[n+1]!=0)
			return false;
		forintdown(i, n+1, 2)
			a[i]=a[i-2];
		a[0]=a[1]=0;
		return true;
	}

	void print() {
		forint(i, 0, n+1) printf(" %d", a[i]); printf("\n");
	}
};


LL encode(const State &a) {
	LL s=0;
	forint(i, 0, n+1)
		s=s*6+a.a[i];
	return s;
}

State decode(LL s) {
	State a;
	forintdown(i, n+1, 0)
		a.a[i]=int(s%6), s/=6;
	return a;
}

// state hashing

int s_h[MAXS], s_next[MAXS];
LL s_val[MAXS];
State s_state[MAXS];
int s_cnt;

int get_id(LL s) {
	int k=int(s%MAXS);
	for(int si=s_h[k]; si>=0; si=s_next[si])
		if(s_val[si]==s)
			return si;
	if(s_cnt==MAXS)
		die();
	int si=s_cnt++;
	s_val[si]=s, s_state[si]=decode(s);
	s_next[si]=s_h[k], s_h[k]=si;
	return si;
}

void s_init() {
	fillchar(s_h, 0xff);
	s_cnt=0;
}

// main proc

void upt(PII &a, PII b) {
	if(b.fi<a.fi)
		a=MP(b.fi, 0);
	if(b.fi==a.fi) {
		a.se+=b.se;
		if(a.se>=MOD)
			a.se-=MOD;
	}
}

void trans_a(PII f1[], PII f2[], int row_id, int i) {
	forn(si, s_cnt) {
		PII val=f1[si];
		if(val.fi==MAXVal)
			continue;
		PII val_0=val;
		PII val_1=MP(val.fi+1, val.se);
		PII val_2=MP(val.fi+2, val.se);
		State a=s_state[si];
		int cur=ga[row_id][i];
		//printf("tA i=%d j=%d v=[%d,%d]\n",row_id,i,val.fi,val.se);
		//a.print();

		if(cur==0) {
			if(a.a[i]==0 && a.a[i+1]==0)
				upt(f2[si], val_0);
			continue;
		}
		if(cur==EMPTY) {
			if(a.a[i]==0) {
				upt(f2[si], val_0);
				State b=a; b.set(i, LE, RI);
				//printf("go: "); b.print();
				upt(f2[get_id(encode(b))], val_2);
			} else {
				upt(f2[si], val_1);
				State b=a; b.set(i, 0, a.a[i]);
				//printf("go: "); b.print();
				upt(f2[get_id(encode(b))], val_1);
			}
		}
		else {
			if(a.a[i]==0) {
				State b;
				b=a; b.set(i, cur);
				upt(f2[get_id(encode(b))], val_1);
				b=a; b.set(i+1, cur);
				upt(f2[get_id(encode(b))], val_1);
			} else {
				State b=a;
				if(b.make_start(i, cur))
					upt(f2[get_id(encode(b))], val_0);
			}
		}
	}
}

void trans_b(PII f1[], PII f2[], int row_id, int i) {
	forn(si, s_cnt) {
		PII val=f1[si];
		if(val.fi==MAXVal)
			continue;
		PII val_0=val;
		PII val_1=MP(val.fi+1, val.se);
		State a=s_state[si];
		int cur=gb[row_id][i];

		//printf("tB i=%d j=%d v=[%d,%d]\n",row_id,i,val.fi,val.se);
		//a.print();

		if(cur==0) {
			if(a.a[i+1]==0 && a.a[i+2]==0)
				upt(f2[si], val_0);
			continue;
		}
		if(cur==EMPTY) {
			if(a.a[i+1]>0 && a.a[i+2]>0) {
				State b=a;
				if(b.connect(i+1, i+2))
					upt(f2[get_id(encode(b))], val_0);
			}
			else if(a.a[i+1]>0) {
				upt(f2[si], val_1);
			}
			else if(a.a[i+2]>0) {
				State b=a; b.set(i+1, a.a[i+2], 0);
				upt(f2[get_id(encode(b))], val_1);
			}
			else { // no links here
				upt(f2[si], val_0);
			}
		}
		else {
			if(a.a[i+1]>0 && a.a[i+2]>0) { // invalid case
			}
			else if(a.a[i+1]>0 || a.a[i+2]>0) {
				int k=(a.a[i+1]>0 ? i+1 : i+2);
				State b=a;
				if(b.make_start(k, cur))
					upt(f2[get_id(encode(b))], val_0);
			}
			else {
				State b=a; b.set(i+1, cur);
				upt(f2[get_id(encode(b))], val_1);
			}
		}
	}
}

void trans_row(PII f1[], PII f2[]) {
	forn(si, s_cnt) {
		PII val=f1[si];
		if(val.fi==MAXVal)
			continue;
		State a=s_state[si];
		if(a.move_row())
			upt(f2[get_id(encode(a))], val);
	}
}

void solve() {
	s_init();

	static PII f[2][MAXS];
	int o1=0, o2=1;
	fill_n(f[o1], MAXS, MP(MAXVal,0));
	f[o1][get_id(0)]=MP(0,1);
	forn(i, n) {
		forn(j, n) {
			//printf("\n");
			fill_n(f[o2], MAXS, MP(MAXVal,0));
			trans_a(f[o1], f[o2], i, j);
			swap(o1, o2);
			//printf("\n");
			fill_n(f[o2], MAXS, MP(MAXVal,0));
			trans_b(f[o1], f[o2], i, j);
			swap(o1, o2);
		}
		fill_n(f[o2], MAXS, MP(MAXVal,0));
		trans_row(f[o1], f[o2]);
		swap(o1, o2);
	}

	PII ans=f[o1][get_id(0)];
	if(ans.fi==MAXVal)
		ans=MP(-1, -1);
	printf("%d %d\n", ans.fi,ans.se);
}

int main() {
	while(init())
		solve();
	return 0;
}

