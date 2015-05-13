#include <iostream>
#include <cstring>
#include <cstdio>
#include <map>
using namespace std;

typedef long long LL;
const int MAXN=12;
const int MAXHash=10007;
const int MAXNum=1600000;

char board[MAXN][MAXN];
int N, M;

#define cut(st, i) ((st>>((i)<<1))&3)
#define erase1(st, i) (st&~(3<<((i)<<1)))
#define erase2(st, i, j) erase1(erase1(st, i), j)
#define erase(st, i, j, k, l) erase2(erase2(st, i, j), k, l)
#define bit1(i) (1<<((i)<<1))
#define bit2(i) (2<<((i)<<1))

struct States {
	int st[MAXNum], next[MAXNum];
	LL val[MAXNum];
	int h[MAXHash];
	int n;
	void clear() {
		n=0;
		memset(h, 0, sizeof(h));
	}
	void add(int s, LL v) {
		int code=s%MAXHash;
		for(int i=h[code]; i>0; i=next[i])
			if(st[i]==s) {
				val[i]+=v;
				return;
			}
		++n; st[n]=s, val[n]=v;
		next[n]=h[code], h[code]=n;
	}
};

int oppo(int st, int i) {
	if(cut(st, i)==1) {
		/*
		for(int n=1, j=i+1, t=(st>>(j<<1)); ; ++j, t>>=2) {
			n+=((t&3)==1)-((t&3)==2);
			if(0==(n)) return j;
		}
		/*/
		for(int cnt=1, j=i+1, x; ; ++j) {
			if((x=cut(st, j))==1) ++cnt;
			else if(x==2 && --cnt==0) return j;
		}//*/
	} else {
		for(int cnt=1, j=i-1, x; ; --j) {
			if((x=cut(st, j))==2) ++cnt;
			else if(x==1 && --cnt==0) return j;
		}
	}
}

inline void transfer(LL *ans, States *old, States *cur, bool valid, int j) {
	LL ret=0;
	cur->clear();
	for(int h=0; h<MAXHash; ++h)
		for(int k=old->h[h]; k>0; k=old->next[k]) {
			int st=old->st[k];
			LL curval=old->val[k];
			int a=cut(st, j), b=cut(st, j+1);
			if(!valid) {
				if(a==0 && b==0)
					cur->add(st, curval);
				continue;
			}
			if(a>0 && b>0) {
				if(a==b) {
					int za=oppo(st, j);
					int zb=oppo(st, j+1);
					if(za>zb) swap(za, zb);
					int st2=erase(st, j, j+1, za, zb)+bit1(za)+bit2(zb);
					cur->add(st2, curval);
				} else if(a==2 && b==1)
					cur->add(erase2(st, j, j+1), curval);
				else if(erase2(st, j, j+1)==0)
					ret+=curval;
			} else if(a==0 && b==0)
				cur->add(st | bit1(j) | bit2(j+1), curval);
			else if(a==0) {
				cur->add(st, curval);
				cur->add(erase1(st,j+1) | (b*bit1(j)), curval);
			} else if(b==0) {
				cur->add(st, curval);
				cur->add(erase1(st,j) | (a*bit1(j+1)), curval);
			}
		}
	if(valid) *ans=ret;
}
States f[2];
int o1, o2;

int main() {
	scanf("%d%d", &N, &M);
	for(int i=0; i<N; ++i) for(int j=0; j<M; ++j)
		do {
			board[i][j]=getchar();
		} while(board[i][j]!='.' && board[i][j]!='*');

	o1=0, o2=1;
	f[o1].clear();
	f[o1].add(0, 1);
	LL ans=1;
	for(int i=0; i<N; ++i) {
		for(int j=0; j<M; ++j, o1=o2, o2^=1)
			transfer(&ans, &f[o1], &f[o2], board[i][j]=='.', j);
		f[o2].clear();
		for(int h=0; h<MAXHash; ++h)
			for(int k=f[o1].h[h]; k>0; k=f[o1].next[k]) {
				int st=f[o1].st[k];
				if(cut(st, M)==0) f[o2].add(st<<2, f[o1].val[k]);
			}
		o1=o2, o2^=1;
	}
	cout<<ans<<endl;
	return 0;
}
