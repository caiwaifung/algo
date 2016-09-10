#include <iostream>
#include <cstring>
#include <cstdio>
#include <map>
using namespace std;

typedef long long LL;
const int MAXN=15;
const int MAXHash=10007;
const int MAXNum=1600000;
const int MODNUM=(int)1E9+7;

char board[MAXN][MAXN];
int N, M, K;

#define cut(st, i) ((st>>((i)<<1))&3)
#define erase1(st, i) (st&~(3<<((i)<<1)))
#define erase2(st, i, j) erase1(erase1(st, i), j)
#define erase(st, i, j, k, l) erase2(erase2(st, i, j), k, l)
#define bit1(i) (1<<((i)<<1))
#define bit2(i) (2<<((i)<<1))

struct States {
	int st[MAXNum], val[MAXNum], next[MAXNum];
	char cc[MAXNum];
	int h[MAXHash];
	int n;
	void clear() {
		n=0;
		memset(h, 0, sizeof(h));
	}
	void add(int s, int c, int v) {
		int code=s%MAXHash;
		for(int i=h[code]; i>0; i=next[i])
			if(st[i]==s && (int)cc[i]==c) {
				(val[i]+=v)%=MODNUM;
				return;
			}
		++n; st[n]=s, cc[n]=(char)c, val[n]=v;
		next[n]=h[code], h[code]=n;
	}
};

int op[MAXN];
int co[MAXN];
int stack[MAXN];
void decode(int st) {
	int p=0;
	for(int i=0, x; i<=M; ++i, st>>=2) {
		x=co[i]=(st&3);
		if(x==1) stack[++p]=i;
		if(x==2) {
			op[i]=stack[p];
			op[stack[p]]=i;
			--p;
		}
	}
}

inline void transfer(int *ans, States *old, States *cur, bool valid, int j) {
	cur->clear();
	if(valid) *ans=0;
	for(int h=0; h<MAXHash; ++h)
		for(int k=old->h[h]; k>0; k=old->next[k]) {
			int st=old->st[k], cc=(int)old->cc[k];
			int curval=old->val[k];
			int a=cut(st, j), b=cut(st, j+1);
			if(!valid) {
				if(a==0 && b==0)
					cur->add(st, cc, curval);
				continue;
			}
			if(a>0 && a==b) {
				decode(st);
				int st2=erase2(st, j, j+1);
				if(a==1) st2-=bit1(op[j+1]);
					else st2+=bit1(op[j]);
				cur->add(st2, cc, curval);
				continue;
			}
			if(a==2 && b==1) {
				cur->add(erase2(st, j, j+1), cc, curval);
				continue;
			}
			if(a==1 && b==2) {
				decode(st);
				int cnt=0;
				for(int p=0; p<j; ++p)
					cnt+=(co[p]==1)-(co[p]==2);
				if(cnt%2!=0) continue;
				if(cc+1<K)
					cur->add(erase2(st, j, j+1), cc+1, curval);
				else if(erase2(st, j, j+1)==0)
					(*ans+=curval)%=MODNUM;
				continue;
			}
			if(a==0 && b==0) {
				cur->add(st|bit1(j)|bit2(j+1), cc, curval);
				continue;
			}
			if(a==0 && b>0) {
				cur->add(st, cc, curval);
				cur->add(erase1(st,j+1)|(b*bit1(j)), cc, curval);
				continue;
			}
			if(a>0 && b==0) {
				cur->add(st, cc, curval);
				cur->add(erase1(st,j)|(a*bit1(j+1)), cc, curval);
				continue;
			}
		}
}

States f[2];
int o1, o2;
void solve() {
	scanf("%d%d%d", &N, &M, &K);
	for(int i=0; i<N; ++i)
		scanf("%s", board[i]);

	o1=0, o2=1;
	f[o1].clear();
	f[o1].add(0, 0, 1);
	int ans=1;
	for(int i=0; i<N; ++i) {
		for(int j=0; j<M; ++j, o1=o2, o2^=1)
			transfer(&ans, &f[o1], &f[o2], board[i][j]=='.', j);
		f[o2].clear();
		for(int h=0; h<MAXHash; ++h)
			for(int k=f[o1].h[h]; k>0; k=f[o1].next[k]) {
				int st=f[o1].st[k], cc=f[o1].cc[k];
				if(cut(st, M)==0)
					f[o2].add(st<<2, cc, f[o1].val[k]);
			}
		o1=o2, o2^=1;
	}
	printf("%d\n", ans);
}

int main() {
	int cs; scanf("%d", &cs);
	for(int i=1; i<=cs; ++i)
		solve();
	return 0;
}
