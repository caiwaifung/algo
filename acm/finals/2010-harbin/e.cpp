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

const int MAXR=20;
const int MAXC=9;
const int MAXSV=2001000; // 5^MAXC
const int MAXS=79999;

const int NO=0;
const int LE=1;
const int RI=2;
const int START=3;
const int ELSE=4;
const int PRE_START=5;

int is_plug(int x) {
	return x>0 && x!=ELSE;
}

bool valid[MAXR][MAXC];
int valid_mask[MAXR];
int bits[1<<MAXC];
int r, c;

bool init() {
	scanf("%d%d", &r,&c);
	if(r==0 && c==0)
		return false;
	forn(i, r) {
		char buf[99];
		scanf("%s", buf);
		valid_mask[i]=0;
		forn(j, c) {
			valid[i][j]=(buf[j]=='.');
			if(valid[i][j])
				valid_mask[i]|=(1<<j);
		}
	}
	bits[0]=0;
	forint(s, 1, (1<<c)-1)
		bits[s]=bits[s^(s&-s)]+1;
	return true;
}

void decode(int s, int a[]) {
	forn(i, c)
		a[i]=s%5, s/=5;
}

int encode(int a[]) {
	int s=0;
	forndown(i, c)
		s=(s*5)+a[i];
	return s;
}

void get_op(int a[], int op[]) {
	static int stack[MAXC+1];
	int top=0;
	forn(i, c) {
		op[i]=-1;
		if(a[i]==PRE_START)
			op[i]=i;
		if(a[i]==LE)
			stack[++top]=i;
		if(a[i]==RI) {
			op[i]=stack[top];
			op[stack[top]]=i;
			--top;
		}
	}
}

bool make_start(int a[], int i) {
	int op[MAXC]; get_op(a, op);
	if(op[i]<0)
		return false;
	a[i]=ELSE;
	a[op[i]]=START;
	return true;
}

bool make_link(int a[], int i, int j) {
	int op[MAXC]; get_op(a, op);
	if(a[j]==START)
		swap(i, j);
	if(a[i]==START) {
		if(op[j]<0) return false;
		a[i]=a[j]=ELSE;
		a[op[j]]=START;
		return true;
	}
	int x=op[i], y=op[j];
	if(x<0 || y<0)
		return false;
	if(x==j)
		return false;
	if(x>y)
		swap(x, y);
	a[i]=a[j]=ELSE;
	a[x]=LE, a[y]=RI;
	return true;
}

void decode_bits(int s, int x[]) {
	forn(i, c)
		x[i]=(s&1), s>>=1;
}

int cal_next(int s, int cur) {
	int a[MAXC]; decode(s, a);
	int a_op[MAXC]; get_op(a, a_op);
	int x[MAXC]; decode_bits(cur, x);
	forn(i, c-1)
		if(x[i]>0 && x[i+1]>0 && a[i]>0 && a[i+1]>0)
			return -1;
	forn(i, c) {
		if(i>0 && x[i]>0 && a[i]==0 && x[i-1]==0 && a[i-1]>0)
			return -1;
		if(i+1<c && x[i]>0 && a[i]==0 && x[i+1]==0 && a[i+1]>0)
			return -1;
	}
	forn(i, c)
		if(a[i]>0 && !is_plug(a[i]) && x[i]>0)
			return -1;

	int b[MAXC];
	fillchar(b, 0);
	forn(i, c)
		b[i]=(x[i]>0 ? ELSE : NO);
	for(int la=-1, i=0; i<=c; ++i) {
		if(i==c || x[i]==0) {
			if(la>=0) {
				if(la<i-1) {
					b[la]=LE;
					b[i-1]=RI;
				} else
					b[la]=PRE_START;
				la=-1;
			}
		} else {
			if(la<0) la=i;
		}
	}
	forn(i, c)
		if(is_plug(a[i]) && b[i]==0)
			return -1;

	forn(i, c) {
		if(!is_plug(a[i]))
			continue;
		if(a[i]==START) {
			if(!make_start(b, i))
				return -1;
		} else {
			int j=a_op[i];
			if(i<j) {
				if(!make_link(b, i, j))
					return -1;
			}
		}
	}
	forn(i, c)
		if(b[i]==PRE_START)
			return -1;
	return encode(b);
}

int s_id[MAXSV], s_val[MAXS];
int s_next[MAXS][1<<MAXC];
int s_cnt;

int get_id(int s) {
	if(s_id[s]<0) {
		s_id[s]=s_cnt;
		s_val[s_cnt]=s;
		fillchar(s_next[s_cnt], 0xff);
		++s_cnt;
	}
	return s_id[s];
}

int get_next(int si, int cur) {
	if(s_next[si][cur]==-1) {
		int t=cal_next(s_val[si], cur);
		if(t<0)
			s_next[si][cur]=-2;
		else
			s_next[si][cur]=get_id(t);
	}
	return s_next[si][cur];
}

int f[MAXR+1][MAXS];
int pre[MAXR+1][MAXS];

bool is_valid_end(int s) {
	int a[MAXC]; decode(s, a);
	forn(i, c-1)
		if(is_plug(a[i]))
			return false;
	return a[c-1]==START;
}

void solve(int cs) {
	fillchar(s_id, 0xff);
	s_cnt=0;

	fillchar(f, 200);
	f[0][get_id(START)]=0;
	forn(i, r) {
		forn(si, s_cnt) {
			int val=f[i][si];
			if(val<0) continue;
			forn(cur, 1<<c) {
				if((valid_mask[i]&cur)!=cur)
					continue;
				int ti=get_next(si, cur);
				if(ti<0)
					continue;
				if(val+bits[cur]>f[i+1][ti]) {
					f[i+1][ti]=val+bits[cur];
					pre[i+1][ti]=si;
				}
			}
		}
	}
	printf("Case %d:\n", cs);
	char ans[MAXR][MAXC];
	forn(i, r) forn(j, c) ans[i][j]=(valid[i][j]?'.':'#');

	int maxv=-1;
	int i=r, si=-1;
	forn(k, s_cnt)
		if(is_valid_end(s_val[k]))
			if(f[r][k]>maxv) {
				maxv=f[r][k];
				si=k;
			}
	while(i>0) {
		int s=s_val[si];
		int a[MAXC]; decode(s, a);
		forn(j, c)
			if(a[j]>0)
				ans[i-1][j]='C';
		si=pre[i][si], --i;
	}
	forn(i, r) {
		forn(j, c) printf("%c", ans[i][j]);
		printf("\n");
	}
	printf("\n");
}

int main() {
	freopen("channel.in", "r", stdin);
	freopen("channel.out", "w", stdout);
	int cs=0;
	while(init()) {
		solve(++cs);
		//break;
	}
	
	return 0;
}

