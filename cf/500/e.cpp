// 9:22 - 9:52 - crash
//      - 10:29 - ac
#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <set>
#include <map>
using namespace std;

#define _ (size_t)
#define all(a) a.begin(), a.end()
#define forint(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define forintdown(i, a, b) for(int i=int(a); i>=int(b); --i)
#define forn(i, n) forint(i, 0, (n)-1)
#define forndown(i, n) forintdown(i, (n)-1, 0)
#define fillchar(a, x) memset(a, x, sizeof(a))
#define fi first
#define se second
#define PB push_back
#define MP make_pair
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef pair<int,int> PII;
typedef pair<double,double> PDD;
typedef vector<LL> VL;
typedef vector<int> VI;
typedef vector<PII> VPI;
typedef vector<string> VS;
template<class T> void setmax(T &a, T b) { if(b>a) a=b; }
template<class T> void setmin(T &a, T b) { if(b<a) a=b; }
template<class T> T gcd(T a, T b) { return b==0?a:gcd(b,a%b); }


// ------------------------ template ends here ------------------------ //
const int MAXN=200010;
const int MAX_NODES=10000000;
const LL INFI=1LL<<40;
LL p[MAXN], r[MAXN]; int far[MAXN];
int n;

void init() {
	scanf("%d", &n);
	forint(i, 1, n) {
		int x, l; scanf("%d%d", &x,&l);
		p[i]=x;
		r[i]=x+l;
	}
	forint(i, 1, n) {
		int j=int(upper_bound(p+i, p+n+1, r[i])-p);
		far[i]=j-1;
	}
}

struct Node {
	LL sum; bool zero;
	int lc, rc;
};

Node nodes[MAX_NODES];

int new_node() {
	static int cur=0;
	int xi=cur++;
	if(xi>=MAX_NODES) exit(-1);
	Node *x=&nodes[xi];
	x->sum=INFI, x->zero=false;
	x->lc=x->rc=-1;
	return xi;
}

int acquire(int xi) {
	int yi=new_node();
	if(xi>=0) memmove(&nodes[yi], &nodes[xi], sizeof(Node));
	return yi;
}

void set_zero(int xi) {
	nodes[xi].zero=true;
	nodes[xi].sum=0;
}

void release(int xi) {
	Node *x=&nodes[xi];
	if(!x->zero) return;
	x->lc=acquire(x->lc);
	x->rc=acquire(x->rc);
	set_zero(x->lc);
	set_zero(x->rc);
	x->zero=false;
}

LL get_sum(int xi) { return xi>=0?nodes[xi].sum:INFI; }

int set_zero(int xi, int s, int t, int l, int r) {
	if(xi>=0 && nodes[xi].zero)
		return xi;
	xi=acquire(xi);
	if(l<=s && t<=r) {
		set_zero(xi);
		return xi;
	}
	Node *x=&nodes[xi];
	int m=(s+t)/2;
	if(l<=m) x->lc=set_zero(x->lc, s, m, l, r);
	if(m+1<=r) x->rc=set_zero(x->rc, m+1, t, l, r);
	x->sum=get_sum(x->lc)+get_sum(x->rc);
	return xi;
}

int set_val(int xi, int s, int t, int ind, LL v) {
	xi=acquire(xi);
	Node *x=&nodes[xi];
	if(s==t) {
		if(v<x->sum) x->sum=v;
		return xi;
	}
	release(xi);
	int m=(s+t)/2;
	if(ind<=m) x->lc=set_val(x->lc, s, m, ind, v);
		else x->rc=set_val(x->rc, m+1, t, ind, v);
	x->sum=get_sum(x->lc)+get_sum(x->rc);
	return xi;
}

void get_sum(int xi, int s, int t, int l, int r, LL &v) {
	if(l<=s && t<=r) {
		v+=nodes[xi].sum;
		return;
	}
	if(nodes[xi].zero)
		return;

	Node *x=&nodes[xi];
	int m=(s+t)/2;
	if(l<=m) get_sum(x->lc, s, m, l, r, v);
	if(m+1<=r) get_sum(x->rc, m+1, t, l, r, v);
}

int trees[MAXN];

void go() {
	int root=-1;
	trees[n]=root;
	forintdown(i, n-1, 1) {
	//printf("i=%d\n",i);
		int j=far[i];
		if(i<j)
			root=set_zero(root, 1, n, i, j-1);
	//printf("@1\n");
		if(j<n) {
			LL tmp=p[j+1]-r[i];
			root=set_val(root, 1, n, j, tmp);
		}
		trees[i]=root;
	}

	int q; scanf("%d", &q);
	while(q--) {
		int x, y; scanf("%d%d", &x,&y);
		LL sum=0;
		get_sum(trees[x], 1, n, x, y-1, sum);
		cout<<sum<<endl;
	}
}

int main() {
	fillchar(nodes, 0);
//printf("sz=%.4lf\n",sizeof(nodes)/1024./1024.);
	init();
	go();
	return 0;
}
