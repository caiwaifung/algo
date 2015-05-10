// 12:23 - 13:04 found some problem
// 16:10 - 16:56 fail sample
// 12:00 - 12:51 pass sample
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cassert>
#include <cstdio>
#include <vector>
using namespace std;

#define forint(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define forn(i, n) forint(i, 0, (n)-1)
#define forintdown(i, a, b) for(int i=int(a); i>=int(b); --i)
#define forndown(i, n) forintdown(i, (n)-1, 0)
#define fillchar(a, x) memset(a, x, sizeof(a))
#define PB push_back
typedef long long LL;
typedef vector<int> VI;

const int MAXR=8;
const int MAXC=8;
const int MAXSV=370000*4; // 9!
const int MAXS=3333;
const int MAXDV=MAXR*MAXC;
const int MAXD=MAXDV*2+1;

// global data

int painted[MAXR], painted_color[MAXR];
int score[MAXR][1<<MAXC];
int r, c;

void init() {
	scanf("%d%d", &r,&c);
	forn(i, r) {
		static char buf[99]; scanf("%s", buf);
		painted[i]=0;
		painted_color[i]=0;
		forn(j, c)
			if(buf[j]!='.') {
				painted[i]|=(1<<j);
				if(buf[j]=='x')
					painted_color[i]|=(1<<j);
			}
	}
	static int s[MAXR][MAXC];
	forn(i, r) forn(j, c)
		scanf("%d", &s[i][j]);
	forn(i, r) {
		forn(cur, 1<<c) {
			int sum=0;
			forn(j, c)
				if(cur&(1<<j))
					sum+=s[i][j];
				else
					sum-=s[i][j];
			score[i][cur]=sum;
		}
	}
}

bool valid_paint(int i, int cur) {
	return (painted[i]&cur)==painted_color[i];
}

// about state hashing

int s_id[MAXSV], s_val[MAXS];
int s_cnt;

int get_id(int s) {
	if(s_id[s]<0) {
		s_id[s]=s_cnt;
		s_val[s_cnt]=s;
		++s_cnt;
	}
	return s_id[s];
}

void s_init() {
	s_cnt=0;
	fillchar(s_id, 0xff);
}

// about state handling

struct UF {
	VI fa;
	int n;

	UF(int n) : n(n) {
		fa.resize(n);
		forn(i, n)
			fa[i]=i;
	}
	void unite(int i, int j) {
		i=get(i);
		j=get(j);
		if(i>j)
			swap(i, j);
		fa[j]=i;
	}
	int get(int i) {
		if(fa[i]==i)
			return i;
		return fa[i]=get(fa[i]);
	}
};

struct State {
	int color[MAXC];
	int pre[MAXC];
	bool visited[2];

	int get_pre(int i) {
		return pre[i]>=0 ? pre[i] : i;
	}

	void print() {
		forn(i, c)
			printf("%2d[%2d] ",color[i],pre[i]); 
		printf(" (%d,%d)\n",visited[0],visited[1]);
	}
};

int next_state[MAXS][1<<MAXC];

State make_start_state(int cur) {
	State a;
	a.visited[0]=a.visited[1]=false;
	forn(i, c) {
		int x=(cur&(1<<i))?1:0;
		a.color[i]=x;
		a.visited[a.color[i]]=true;
		if(i>0 && a.color[i]==a.color[i-1])
			a.pre[i]=a.get_pre(i-1);
		else
			a.pre[i]=-1;
	}
	return a;
}

bool is_valid_end(const State &a) {
	if(!a.visited[0] || !a.visited[1])
		return false;
	int cnt[2]={0, 0};
	forn(i, c)
		if(a.pre[i]<0)
			++cnt[a.color[i]];
	return cnt[0]<=1 && cnt[1]<=1;
}

State decode(int s) {
	State a;
	int x=s%4; s/=4;
	a.visited[0]=((x&1)>0);
	a.visited[1]=((x&2)>0);
	forn(i, c) {
		int n=i+2;
		int x=s%n; s/=n;
		if(x<2) {
			a.pre[i]=-1;
			a.color[i]=x;
		} else {
			a.pre[i]=x-2;
			a.color[i]=a.color[a.pre[i]];
		}
	}
	return a;
}

int encode(const State &a) {
	int s=0;
	forndown(i, c) {
		int n=i+2;
		int x;
		if(a.pre[i]<0)
			x=a.color[i];
		else
			x=a.pre[i]+2;
		s=s*n+x;
	}
	int x=0;
	if(a.visited[0]) x|=1;
	if(a.visited[1]) x|=2;
	s=s*4+x;
	return s;
}

bool compute_next(const State &a, State &b, int cur) {
//printf("get_next\n");
	forn(i, c)
		b.color[i]=((cur&(1<<i))?1:0);
	forn(i, c-1)
		if(b.color[i]==b.color[i+1] && a.color[i]==a.color[i+1] && b.color[i]==a.color[i])
			return false;
	forn(i, c) {
		b.pre[i]=-1;
		if(i>0 && b.color[i-1]==b.color[i])
			b.pre[i]=b.get_pre(i-1);
	}

	UF uf(c*2);
	forn(i, c) {
		if(b.pre[i]>=0)
			uf.unite(b.pre[i], i);
		if(a.pre[i]>=0)
			uf.unite(c+a.pre[i], c+i);
		if(a.color[i]==b.color[i])
			uf.unite(i, c+i);
	}
	forn(i, c) {
		int j=uf.get(i);
		assert(j>=0 && j<c);
		if(j==i)
			b.pre[i]=-1;
		else
			b.pre[i]=j;
	}
	int old[2]={0, 0};
	forn(i, 2) old[i]=(a.visited[i]?1:0);
	forn(i, c) old[a.color[i]]=0;

	int cnt[2]={0, 0};
	forn(i, c)
		cnt[b.color[i]]=1;
	forn(i, c)
		if(uf.get(i+c)==i+c)
			++cnt[a.color[i]];
	forn(i, 2) {
		if(cnt[i]>1) return false;
		if(old[i] && cnt[i]>0) return false;
	}
	
	forn(i, 2) b.visited[i]=a.visited[i];
	forn(i, c) b.visited[b.color[i]]=true;

	return true;
}

// main proc

int f[MAXR][MAXD][MAXS];
char pd[MAXR][MAXD][MAXS];
short ps[MAXR][MAXD][MAXS];

int enc_d(int d) {
	return d+MAXDV;
}
int dec_d(int dv) {
	return dv-MAXDV;
}

void upt(int i, int d, int s, int val, int ed, int es) {
	//printf("%d %d %d %d\n",i,d,s,val);
	f[i][d][s]+=val;
	pd[i][d][s]=(char)ed;
	ps[i][d][s]=(short)es;
}

int get_next(int si, int cur) {
	int &ans=next_state[si][cur];
	if(ans==-1) {
		State a=decode(s_val[si]), b;
		if(!compute_next(a, b, cur))
			ans=-2;
		else
			ans=get_id(encode(b));
	}
	return ans;
}

void solve(int cs) {
	s_init();
	fillchar(next_state, 0xff);
	fillchar(f, 0);
	//printf("%d\n",painted[0]);
	//printf("%d\n",painted_color[0]);
	forn(cur, 1<<c)
		if(valid_paint(0, cur)) {
			State a=make_start_state(cur);
			//printf("make start %d\n", cur);
			upt(0, enc_d(score[0][cur]), get_id(encode(a)), 1, 0, 0);
		}
	//printf("s_cnt=%d\n",s_cnt);
	forint(i, 1, r-1) {
		VI valid_cur;
		forn(cur, 1<<c)
			if(valid_paint(i, cur))
				valid_cur.PB(cur);
		forn(dv, MAXD) forn(si, s_cnt) {
			int val=f[i-1][dv][si];
			if(val==0)
				continue;
			int d=dec_d(dv);
			//printf("f[%d,%d,%d]=%d\n",i-1,d,s,val);
			forn(k, valid_cur.size()) {
				int cur=valid_cur[k];
				int ti=get_next(si, cur);
				if(ti>=0)
					upt(i, enc_d(d+score[i][cur]), ti, val, dv, si);
			}
		}
	}

	//printf("scnt=%d\n",s_cnt);

	int min_delta=0, tot=0;
	while(min_delta<=MAXDV) {
		forn(si, s_cnt) {
			int tmp=f[r-1][enc_d(min_delta)][si];
			if(min_delta>0) tmp+=f[r-1][enc_d(-min_delta)][si];
			if(tmp==0)
				continue;
			State a=decode(s_val[si]);
			//printf("min_delta=%d si=%d\n",min_delta,si);
			//a.print();
			if(is_valid_end(a)) {
				//printf("valid tmp=%d\n",tmp);
				tot+=tmp;
			}
		}
		if(tot>0)
			break;
		++min_delta;
	}
	printf("Case %d: ", cs);
	if(tot==0) {
		printf("0 0\n");
		return;
	}
	char ans[MAXR][MAXC];
	int i=r-1, dv, si;
	for(si=0; si<s_cnt; ++si) {
		dv=enc_d(min_delta);
		if(f[i][dv][si]>0)
			break;
		dv=enc_d(-min_delta);
		if(f[i][dv][si]>0)
			break;
	}
	while(i>=0) {
		State a=decode(s_val[si]);
		forn(j, c)
			ans[i][j]=(a.color[j]==0?'o':'x');
		int d0=pd[i][dv][si], s0=ps[i][dv][si];
		dv=d0, si=s0, --i;
	}
	printf("%d %d\n", min_delta, tot);
	forn(i, r) {
		forn(j, c) printf("%c", ans[i][j]);
		printf("\n");
	}
	//printf("scnt=%d\n",s_cnt);
}

int main() {
	int cs; scanf("%d", &cs);
	forint(i, 1, cs) {
		init();
		solve(i);
		printf("\n");
		//break;
	}
	return 0;
}
