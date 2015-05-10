#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
typedef pair<int,int> PII;
#define MP make_pair
#define PB push_back
#define l first
#define r second

const int MAXN=100010;
const int MAXCHARS=26;

int cnt[MAXN*4][MAXCHARS];
int first[MAXN*4][MAXCHARS];
void add(int x, int s, int t, int ind, int c, int v) {
	cnt[x][c]+=v;
	if(s==t) {
		if(cnt[x][c]>0) first[x][c]=s;
			else first[x][c]=MAXN;
		return;
	}
	int mid=(s+t)/2;
	if(ind<=mid) add(x*2, s, mid, ind, c, v);
		else add(x*2+1, mid+1, t, ind, c, v);
	first[x][c]=min(first[x*2][c], first[x*2+1][c]);
}
int getcnt(int x, int s, int t, int st, int en, int c) {
	if(st<=s && t<=en)
		return cnt[x][c];
	int mid=(s+t)/2;
	int ans=0;
	if(st<=mid) ans+=getcnt(x*2, s, mid, st, en, c);
	if(mid<en) ans+=getcnt(x*2+1, mid+1, t, st, en, c);
	return ans;
}
int getfirst(int x, int s, int t, int st, int en, int c) {
	if(st<=s && t<=en)
		return first[x][c];
	int mid=(s+t)/2;
	int ans=MAXN;
	if(st<=mid) ans=min(ans, getfirst(x*2, s, mid, st, en, c));
	if(mid<en) ans=min(ans, getfirst(x*2+1, mid+1, t, st, en, c));
	return ans;
}


char buf[MAXN];
int s[MAXN];
//int c[MAXN][30];
//int first[
PII q[MAXN];
int liml[MAXN];
int n, nq;

void swapchar(int i, int j) {
//printf("s %d %d\n",i,j);
	add(1, 1, n, i, s[i], -1);
	add(1, 1, n, j, s[j], -1);
	swap(s[i], s[j]);
	add(1, 1, n, i, s[i], 1);
	add(1, 1, n, j, s[j], 1);
}

int tr[MAXN];
void setmax(int x, int v) {
	for(; x<=n; x+=(x&-x)) tr[x]=min(tr[x], v);
}
int getmax(int x) {
	int ans=0;
	for(; x>=1; x-=(x&-x)) ans=min(ans, tr[x]);
	return ans;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d%d", &n, &nq);
	scanf("%s", buf+1);
	memset(cnt, 0, sizeof(cnt));
	memset(first, 50, sizeof(first));
	for(int i=1; i<=n; ++i)
		add(1, 1, n, i, s[i]=(int)(buf[i]-'a'), 1);
	for(int i=1; i<=nq; ++i) scanf("%d%d", &q[i].l, &q[i].r);
	/*
	sort(q+1, q+nq+1);
	int tnq=nq; nq=1;
	for(int i=2; i<=tnq; ++i)
		if(q[i].l==q[nq].l)
			q[nq].r=max(q[nq].r, q[i].r);
		else
			if(q[i].r>q[nq].r)
				q[++nq]=q[i];
	*/
	memset(tr, 0, sizeof(tr));
	for(int i=nq; i>=1; --i) {
		int l=q[i].l, r=q[i].r;
		liml[i]=l;
		while(l<r) {
			if(getmax(l)>=r) break;
			liml[i]=l;
			++l, --r;
		}
		setmax(q[i].l, q[i].r);
	}
	for(int cur=1; cur<=nq; ++cur) {
		int l=q[cur].l, r=q[cur].r;
		while(l<r && l<=liml[cur]) {
			int bestc=-1, odds=0;
			for(int k=MAXCHARS-1; k>=0; --k) {
				int c=getcnt(1, 1, n, l, r, k);
				if(c%2==1) ++odds;
				if(c>=2) bestc=k;
			}
			//printf("l=%d r=%d bestc=%d odds=%d\n",l,r,bestc,odds);
			if(odds>1) break;
			int p=getfirst(1, 1, n, l, r, bestc);
			if(!(p>=l && p<=r)) for(;;);
			//printf("p=%d\n", p);
			swapchar(l, p);
			p=getfirst(1, 1, n, l+1, r, bestc);
			if(!(p>=l+1 && p<=r)) for(;;);
			//printf("p=%d\n", p);
			swapchar(r, p);
			++l, --r;
		}
	}
	for(int i=1; i<=n; ++i) printf("%c", (char)(s[i]+'a'));
	printf("\n");
	return 0;
}
