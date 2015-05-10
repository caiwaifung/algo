#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN=100010*2;
const int MAXLogN=20;

int sa[MAXN], rank[MAXN], height[MAXN], limit[MAXN];
int bbc[MAXN], wxa[MAXN], wxb[MAXN];
char str[MAXN];
int len;
void cal_sa() {
	int *x=wxa, *y=wxb, size=256;
	memset(bbc, 0, sizeof(bbc));
	for(int i=1; i<=len; ++i) ++bbc[x[i]=(int)str[i]];
	for(int i=1; i<=size; ++i) bbc[i]+=bbc[i-1];
	for(int i=len; i>=1; --i) sa[bbc[x[i]]--]=i;
	for(int w=1; w<len; w*=2, size=len) {
		int p=0;
		for(int i=len-w+1; i<=len; ++i) y[++p]=i;
		for(int i=1; i<=len; ++i) if(sa[i]>w) y[++p]=sa[i]-w;
		memset(bbc, 0, sizeof(bbc));
		for(int i=1; i<=len; ++i) ++bbc[x[i]];
		for(int i=1; i<=size; ++i) bbc[i]+=bbc[i-1];
		for(int i=len; i>=1; --i) sa[bbc[x[y[i]]]--]=y[i];
		swap(x, y); x[sa[1]]=1;
		for(int i=2; i<=len; ++i) {
			int j=sa[i], k=sa[i-1];
			x[j]=x[k]+(y[k]<y[j]||y[k+w]<y[j+w]);
		}
	}
}
void cal_height() {
	for(int i=1; i<=len; ++i) rank[sa[i]]=i;
	for(int i=1, j, h=0; i<=len; height[rank[i++]]=h)
		for(h?h--:0, j=sa[rank[i]-1]; str[i+h]==str[j+h]; ++h);
}

int lcp_st[MAXLogN][MAXN];
int lcp_k[MAXN], lcp_w[MAXN];
void cal_lcp() {
	for(int i=2; i<=len; ++i) lcp_st[0][i]=min(limit[sa[i]], height[i]);
	for(int k=1, w=1; 2+w<=len; ++k, w*=2)
		for(int i=2; i+w<=len; ++i)
			lcp_st[k][i]=min(lcp_st[k-1][i], lcp_st[k-1][i+w]);
	for(int i=1, k=0, w=1; i<=len; ++i) {
		while(w*2<=i) w*=2, ++k;
		lcp_k[i]=k, lcp_w[i]=w;
	}
}
int lcp(int i, int j) {
	if(i==j) return limit[i];
	i=rank[i], j=rank[j]; if(i>j) swap(i, j);
	++i;
	int k=lcp_k[j-i+1], w=lcp_w[j-i+1];
	return min(limit[sa[i-1]], min(lcp_st[k][i], lcp_st[k][j-w+1]));
}

int tree[MAXN*4];
void setmax(int x, int s, int t, int st, int en, int val) {
	if(st<=s && t<=en) {
		tree[x]=max(tree[x], val);
		return;
	}
	int m=(s+t)/2;
	if(st<=m) setmax(x*2, s, m, st, en, val);
	if(m+1<=en) setmax(x*2+1, m+1, t, st, en, val);
}
int getmax(int x, int s, int t, int ind) {
	if(s==t) return tree[x];
	int m=(s+t)/2;
	if(ind<=m) return max(tree[x], getmax(x*2, s, m, ind));
	else return max(tree[x], getmax(x*2+1, m+1, t, ind));
}

long long ans[MAXN];
int belong[MAXN];
int hash[MAXN];
char buf[MAXN];
int n, k;

int main() {
	scanf("%d%d", &n, &k);
	len=0;
	for(int i=1; i<=n; ++i) {
		scanf("%s", buf);
		int curlen=strlen(buf);
		for(int j=0; j<curlen; ++j) {
			str[++len]=buf[j];
			belong[len]=i;
			limit[len]=curlen-j;
		}
		str[++len]='$';
		belong[len]=0;
	}
	cal_sa();
	cal_height();
	cal_lcp();

	memset(tree, 0, sizeof(tree));
	int cnt;

	memset(hash, 0, sizeof(hash));
	cnt=0; hash[0]=1;
	for(int i=1, j=0; i<=len; ++i) {
		while(cnt<k) {
			if(++j>len) break;
			if(hash[belong[sa[j]]]++==0)
				++cnt;
		}
		if(j>len) break;
		int p=lcp(sa[i], sa[j]);
		setmax(1, 1, len, i, j, p);
		//printf("update [%d,%d] %d\n", i, j, p);
		if(--hash[belong[sa[i]]]==0)
			--cnt;
	}
	memset(hash, 0, sizeof(hash));
	cnt=0; hash[0]=1;
	for(int j=len, i=len+1; j>=1; --j) {
		while(cnt<k) {
			if(--i<1) break;
			if(hash[belong[sa[i]]]++==0)
				++cnt;
		}
		if(i<1) break;
		int p=lcp(sa[i], sa[j]);
		setmax(1, 1, len, i, j, p);
		//printf("update [%d,%d] %d\n", i, j, p);
		if(--hash[belong[sa[j]]]==0)
			--cnt;
	}

	memset(ans, 0, sizeof(ans));
	for(int i=1; i<=len; ++i)
		if(belong[sa[i]]>0) {
			ans[belong[sa[i]]]+=getmax(1, 1, len, i);
		}
	for(int i=1; i<=n; ++i)
		printf("%lld%c", ans[i], i<n?' ':'\n');
	return 0;
}
