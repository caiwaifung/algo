#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

#define forint(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define forn(i, n) forint(i, 0, (n)-1)
#define forintdown(i, a, b) for(int i=int(a); i>=int(b); --i)
#define fillchar(a, x) memset(a, x, sizeof(a))
typedef long long LL;

const int MAXR=12;
const int MAXC=12;
const int MAXSV=1600000; // 3^13
const int MAXS=79999;

bool valid[MAXR][MAXC];
int r, c;

int s_id[MAXSV], s_val[MAXS];
int s_cnt;

int get_id(int s) {
	if(s_id[s]<0) {
		s_val[s_cnt]=s;
		s_id[s]=s_cnt++;
	}
	return s_id[s];
}

struct State {
	int a[MAXC+1];
	void set(int i, int v) {
		a[i]=v;
	}
	void set(int i, int v1, int v2) {
		a[i]=v1, a[i+1]=v2;
	}
	int op(int i) {
		if(a[i]==0)
			return 0;
		int delta=(a[i]==1?1:-1);
		int c=0;
		while(1) {
			if(a[i]==1) ++c;
			if(a[i]==2) --c;
			if(c==0) break;
			i+=delta;
		}
		return i;
	}
};

State decode(int s) {
	State a;
	forint(i, 0, c)
		a.a[i]=s%3, s/=3;
	return a;
}

int encode(State a) {
	int s=0;
	forintdown(i, c, 0)
		s=s*3+a.a[i];
	return s;
}

void init() {
	scanf("%d%d", &r,&c);
	forn(i, r) {
		char buf[99]; scanf("%s", buf);
		forn(j, c) valid[i][j]=(buf[j]=='.');
	}
}

LL **f[MAXR+1]; //[MAXC+1][MAXS];

void new_f(int i) {
	f[i]=new LL*[MAXC+1];
	forn(j, MAXC+1) {
		f[i][j]=new LL[MAXS];
		memset(f[i][j], 0, sizeof(LL)*MAXS);
	}
}
void del_f(int i) {
	forn(j, MAXC+1) delete f[i][j];
	delete f[i];
}

void solve() {
	fillchar(s_id, 0xff);
	s_cnt=0;

	new_f(0);
	f[0][0][get_id(0)]=1;
	LL ans=0;
	forn(i, r) {
		new_f(i+1);
		forn(j, c) {
			LL tmp=0;
			forn(si, s_cnt) {
				LL val=f[i][j][si];
				int s=s_val[si];
				State a=decode(s), b;
				//printf("i=%d j=%d s=%d\n",i,j,s);

				if(!valid[i][j]) {
					if(a.a[j]==0 && a.a[j+1]==0)
						f[i][j+1][get_id(s)]+=val;
					continue;
				}
				if(a.a[j]==0 && a.a[j+1]==0) {
					b=a; b.set(j, 1, 2);
					f[i][j+1][get_id(encode(b))]+=val;
				}
				if(a.a[j]>0 && a.a[j+1]==0) {
					f[i][j+1][get_id(s)]+=val;
					b=a; b.set(j, 0, a.a[j]);
					f[i][j+1][get_id(encode(b))]+=val;
				}
				if(a.a[j]==0 && a.a[j+1]>0) {
					f[i][j+1][get_id(s)]+=val;
					b=a; b.set(j, a.a[j+1], 0);
					f[i][j+1][get_id(encode(b))]+=val;
				}
				if(a.a[j]>0 && a.a[j+1]>0) {
					int x=a.op(j), y=a.op(j+1);
					if(x==j+1) {
						b=a; b.set(j, 0, 0);
						int t=encode(b);
						if(t==0)
							tmp+=val;
					} else {
						b=a;
						b.set(j, 0, 0);
						if(a.a[j]==a.a[j+1]) {
							if(a.a[j]==1)
								b.set(y, 1);
							else
								b.set(x, 2);
						}
						f[i][j+1][get_id(encode(b))]+=val;
					}
				}
			}
			if(valid[i][j])
				ans=tmp;
		}
		//printf("#1\n");
		forn(si, s_cnt) {
			LL val=f[i][c][si];
			int s=s_val[si];
			State a=decode(s);
			if(a.a[c]==0) {
				forintdown(k, c, 1) a.a[k]=a.a[k-1];
				a.a[0]=0;
				f[i+1][0][get_id(encode(a))]+=val;
			}
		}
		del_f(i);
		//printf("#2\n");
	}
	cout<<ans<<endl;
}

int main() {
	freopen("in.txt", "r", stdin);
	init();
	solve();
	return 0;
}
