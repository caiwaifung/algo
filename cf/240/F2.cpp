#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
typedef pair<int,int> PII;
#define MP make_pair
#define PB push_back

const int MAXN=100010;
const int MAXCHARS=26;

int str[MAXN];

int cnt[MAXN*4][MAXCHARS];
vector<PII> order[MAXN*4];
bool mark[MAXN*4];
void push(int x, vector<PII> o) {
	memset(cnt[x], 0, sizeof(cnt[x]));
	for(int i=0; i<(int)o.size(); ++i)
		cnt[x][o[i].first]+=o[i].second;
	order[x]=o;
	mark[x]=true;
}
vector<PII> copy(vector<PII> o, int st, int en) {
	int p=0;
	vector<PII> ans;
	for(int i=0; i<o.size(); ++i) {
		int le=max(p+1, st);
		int ri=min(p+o[i].second, en);
		if(le<=ri) ans.PB(MP(o[i].first, ri-le+1));
		p+=o[i].second;
	}
	return ans;
}
void release(int x, int s, int t) {
	if(!mark[x]) return;
	int mid=(s+t)/2;
	int sz1=mid-s+1;
	int sz2=t-mid;
	push(x*2, copy(order[x], 1, sz1));
	push(x*2+1, copy(order[x], sz1+1, sz1+sz2));
	mark[x]=false;
}
void build(int x, int s, int t) {
	mark[x]=false;
	if(s==t) {
		cnt[x][str[s]]=1;
		return;
	}
	int mid=(s+t)/2;
	build(x*2, s, mid);
	build(x*2+1, mid+1, t);
	for(int i=0; i<MAXCHARS; ++i) cnt[x][i]=cnt[x*2][i]+cnt[x*2+1][i];
}
void rearrange(int x, int s, int t, int st, int en, vector<PII> o) {
	if(st<=s && t<=en) {
		int p=s-st+1;
		int sz=t-s+1;
		push(x, copy(o, p, p+sz-1));
		//mark[x]=true;
		return;
	}
	release(x, s, t);
	int mid=(s+t)/2;
	if(st<=mid) rearrange(x*2, s, mid, st, en, o);
	if(mid<en) rearrange(x*2+1, mid+1, t, st, en, o);
	for(int i=0; i<MAXCHARS; ++i) cnt[x][i]=cnt[x*2][i]+cnt[x*2+1][i];
}
void getcnt(int x, int s, int t, int st, int en, int c[]) {
	if(st<=s && t<=en) {
		for(int i=0; i<MAXCHARS; ++i) c[i]+=cnt[x][i];
		return;
	}
	release(x, s, t);
	int mid=(s+t)/2;
	if(st<=mid) getcnt(x*2, s, mid, st, en, c);
	if(mid<en) getcnt(x*2+1, mid+1, t, st, en, c);
}

char buf[MAXN];
int n, nq;
void make(int st, int en) {
	int c[MAXCHARS]; memset(c, 0, sizeof(c));
	getcnt(1, 1, n, st, en, c);
	int odds=0;
	for(int i=0; i<MAXCHARS; ++i) if(c[i]%2==1) ++odds;
	//for(int i=0; i<MAXCHARS; ++i) if(c[i]>0) printf("[%d,%d]",i,c[i]);printf("\n");
	if(odds>1) return;
	vector<PII> o;
	for(int i=0; i<MAXCHARS; ++i)
		if(c[i]>=2) o.PB(MP(i, c[i]/2));
	for(int i=0; i<MAXCHARS; ++i)
		if(c[i]%2==1) o.PB(MP(i, 1));
	for(int i=MAXCHARS-1; i>=0; --i)
		if(c[i]>=2) o.PB(MP(i, c[i]/2));
	//for(int i=0; i<o.size(); ++i) printf("<%d,%d>",o[i].first,o[i].second);printf("\n");
	rearrange(1, 1, n, st, en, o);
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d%d", &n, &nq);
	scanf("%s", buf+1);
	for(int i=1; i<=n; ++i) str[i]=(int)(buf[i]-'a');
	memset(cnt, 0, sizeof(cnt));
	build(1, 1, n);
	for(int i=1; i<=nq; ++i) {
		int l, r;
		scanf("%d%d", &l, &r);
		//printf("l=%d r=%d\n",l,r);
		make(l, r);
	}
	for(int i=1; i<=n; ++i) {
		int c[MAXCHARS]; memset(c, 0, sizeof(c));
		getcnt(1, 1, n, i, i, c);
		char ch='$';
		for(int k=0; k<MAXCHARS; ++k)
			if(c[k]>0) if(ch!='$') for(;;); else ch=(char)('a'+k);
		printf("%c", ch);
	}
	printf("\n");
	return 0;
}
