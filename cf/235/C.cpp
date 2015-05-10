// 1:53
// 2:23 (sample) TLE
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
typedef pair<int,int> PII;
#define MP make_pair
#define PB push_back

const int MAXLen=3110000;
const int MAXLogN=23;
const int MAXQ=100010;

int sa[MAXLen], rank[MAXLen], height[MAXLen], limit[MAXLen];
int wxa[MAXLen], wxb[MAXLen], wxc[MAXLen];
char str[MAXLen];
int len;
void cal_sa() {
	int *x=wxa, *y=wxb, *c=wxc, size=256;
	for(int i=0; i<=size; ++i) c[i]=0; //memset
	for(int i=1; i<=len; ++i) ++c[x[i]=(int)str[i]];
	for(int i=1; i<=size; ++i) c[i]+=c[i-1];
	for(int i=len; i>=1; --i) sa[c[x[i]]--]=i;

	for(int w=1; w<len; w*=2, size=len) {
		int p=0;
		for(int i=len-w+1; i<=len; ++i) y[++p]=i;
		for(int i=1; i<=len; ++i) if(sa[i]>w) y[++p]=sa[i]-w;

		for(int i=0; i<=size; ++i) c[i]=0; //memset
		for(int i=1; i<=len; ++i) ++c[x[i]];
		for(int i=1; i<=size; ++i) c[i]+=c[i-1];
		for(int i=len; i>=1; --i) sa[c[x[y[i]]]--]=y[i];
		std::swap(x, y); x[sa[1]]=1;
		for(int i=2; i<=len; ++i) {
			int j1=sa[i-1], j2=sa[i];
			int c1=y[j1], c2=y[j2];
			if(c1==c2) {
				c1=(j1+w<=len?y[j1+w]:0);
				c2=(j2+w<=len?y[j2+w]:0);
			}
			x[j2]=x[j1]+(c1<c2);
		}
	}
}
void cal_height() {
	for(int i=1; i<=len; ++i) rank[sa[i]]=i;
	for(int i=1, h=0; i<=len; ++i) {
		if(h>0) --h;
		int j=sa[rank[i]-1];
		while(i+h<=len && j+h<=len && str[i+h]==str[j+h])
			++h;
		height[rank[i]]=h;
	}
}

int lcp_st[MAXLen][MAXLogN];
int _log[MAXLen];
void cal_lcp() {
	for(int i=2; i<=len; ++i) lcp_st[i][0]=height[i];
	for(int k=1, w=1; 2+w<=len; ++k, w*=2)
		for(int i=2; i+w<=len; ++i)
			lcp_st[i][k]=min(lcp_st[i][k-1], lcp_st[i+w][k-1]);
	_log[1]=0;
	for(int i=2; i<=len; ++i) {
		_log[i]=_log[i-1];
		if((1<<(_log[i]+1))<=i) ++_log[i];
	}
}

char buf[MAXLen];
int qs[MAXQ], qlen[MAXQ];
int n, q;

int tr[MAXLen*4], tb[MAXLen*4], tcnt[MAXLen*4];
void build(int x, int s, int t) {
	tr[x]=0; tcnt[x]=0;
	if(s==t) {
		tb[x]=(sa[s]<=n);
		return;
	}
	int mid=(s+t)/2;
	build(x*2, s, mid);
	build(x*2+1, mid+1, t);
	tb[x]=tb[x*2]+tb[x*2+1];
}
inline void push(int x, int c) {
	tr[x]=c;
	tcnt[x]=c*tb[x];
}
inline void paint(int x, int s, int t, int st, int en, int c) {
	if(st<=s && t<=en) {
		push(x, c);
		return;
	}
	if(tr[x]>=0) {
		push(x*2, tr[x]);
		push(x*2+1, tr[x]);
		tr[x]=-1;
	}
	int mid=(s+t)/2;
	if(st<=mid) paint(x*2, s, mid, st, en, c);
	if(mid<en) paint(x*2+1, mid+1, t, st, en, c);
	tcnt[x]=tcnt[x*2]+tcnt[x*2+1];
}

int main() {
	scanf("%s", str+1);
	len=n=strlen(str+1);
	scanf("%d", &q);
	for(int i=1; i<=q; ++i) {
		scanf("%s", buf+1); qlen[i]=strlen(buf+1);
		str[++len]='#';
		qs[i]=len;
		for(int j=1; j<=qlen[i]; ++j) str[++len]=buf[j];
		for(int j=1; j<=qlen[i]; ++j) str[++len]=buf[j];
	}
	//printf("st\n"); fflush(stdout);
	cal_sa();
	cal_height();
	cal_lcp();
	//printf("pcp\n"); fflush(stdout);
	build(1, 1, len);
	for(int cur=1; cur<=q; ++cur) {
		//printf("cur=%d\n", cur); fflush(stdout);
		int limit=qlen[cur];
		paint(1, 1, len, 1, len, 0);
		for(int xi=qs[cur]+1; xi<=qs[cur]+limit; ++xi) {
			int i=rank[xi];
			int j1=i;
			for(int k=_log[j1-1]; k>=0; --k)
				if(lcp_st[j1-(1<<k)+1][k]>=limit)
					j1-=(1<<k);
			int j2=i;
			for(int k=_log[len-j2]; k>=0; --k)
				if(lcp_st[j2+1][k]>=limit)
					j2+=(1<<k);
			//printf("j1=%d j2=%d\n", j1,j2);fflush(stdout);
			paint(1, 1, len, j1, j2, 1);
		}
		int ans=tcnt[1];
		printf("%d\n", ans);
	}
	//printf("%.3lf\n", sizeof(lcp_st)/1024.0/1024.0);
	return 0;
}
