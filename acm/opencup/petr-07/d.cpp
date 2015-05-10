#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
using namespace std;

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
typedef pair<double,double> PDD;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
typedef vector<int> VI;
typedef vector<LL> VL;
typedef vector<PII> VPI;
typedef vector<PLL> VPL;

const int MAXQ=100000;
const int ADD=0x01;
const int DEL=0x02;
const int QUERY=0x03;

struct Operation {
	int type, i;
	Operation(int t, int i) : type(t), i(i) {}
};

struct Edge {
	int a, b;
	bool enabled;
	Edge(int a, int b, bool e) : a(a), b(b), enabled(e) {}
};

bool ans[MAXQ];

struct UF {
	vector<int> fa;
	UF(int n) {
		fa.resize(n);
		forn(i, n) fa[i]=i;
	}
	void unite(int x, int y) {
		x=find(x);
		y=find(y);
		if(x!=y) fa[x]=y;
	}
	int find(int x) {
		if(fa[x]==x) return x;
		return fa[x]=find(fa[x]);
	}
};

void pre(int &n, vector<Edge> &es, vector<Operation> &ops) {
	vector<bool> vis(es.size(), false);
	forn(i, ops.size())
		if(ops[i].type==ADD || ops[i].type==DEL)
			vis[ops[i].i]=true;
	//printf("  #1\n");fflush(stdout);
	UF uf(n);
	forn(i, es.size())
		if(!vis[i] && es[i].enabled)
			uf.unite(es[i].a, es[i].b);
	//printf("  #2\n");fflush(stdout);

	vector<int> v_id(n, -1);
	int n2=0;
	forn(i, n) {
		int j=uf.find(i);
		if(v_id[j]<0) v_id[j]=n2++;
		v_id[i]=v_id[j];
	}
	n=n2;
	//printf("  #3\n");fflush(stdout);

	vector<int> e_id(es.size(), -1);
	vector<Edge> es2;
	forn(i, es.size())
		if(vis[i]) {
			e_id[i]=es2.size();
			es[i].a=v_id[es[i].a];
			es[i].b=v_id[es[i].b];
			es2.PB(es[i]);
		}
	es=es2;
	//printf("  #4\n");fflush(stdout);
	forn(i, ops.size())
		if(ops[i].type==ADD || ops[i].type==DEL)
			ops[i].i=e_id[ops[i].i];
}

void work(int n, vector<Edge> es, vector<Operation> ops) {
	pre(n, es, ops);
	/*
	printf("\n");
	printf("work n=%d |E|=%d |Q|=%d\n",n,es.size(),ops.size());
	printf("after pre n=%d |E|=%d |Q|=%d\n",n,es.size(),ops.size());
	forn(i, es.size()) {
		printf(" [%d,%d](%d)", es[i].a,es[i].b,es[i].enabled);
	}
	printf("\n");
	forn(i, ops.size()) {
		printf(" ");
		if(ops[i].type==ADD) printf("A");
		if(ops[i].type==DEL) printf("D");
		if(ops[i].type==QUERY) printf("Q");
		printf("%d", ops[i].i);
	}
	printf("\n");
	*/
	if(ops.size()==1) {
		if(ops[0].type==QUERY)
			ans[ops[0].i]=(n==1);
		return;
	}
	if(n>(int)es.size()+1) {
		forn(i, ops.size())
			if(ops[i].type==QUERY)
				ans[ops[i].i]=false;
		return;
	}
	vector<Operation> l, r;
	int mid=ops.size()/2;
	forint(i, 0, mid-1) l.PB(ops[i]);
	forint(i, mid, ops.size()-1) r.PB(ops[i]);

	work(n, es, l);
	forn(i, l.size()) {
		if(l[i].type==ADD) es[l[i].i].enabled=true;
		if(l[i].type==DEL) es[l[i].i].enabled=false;
	}
	work(n, es, r);
}

int main() {
	freopen("disconnected.in", "r", stdin);
	freopen("disconnected.out", "w", stdout);

	vector<Edge> edges;
	vector<Operation> ops;
	int n, m, qn;

	scanf("%d%d", &n, &m);
	forn(i, m) {
		int a, b; scanf("%d%d", &a,&b);
		--a, --b;
		edges.PB(Edge(a, b, true));
	}
	scanf("%d", &qn);
	forn(i, qn) {
		VI p; int k;
		scanf("%d", &k);
		p.resize(k);
		forn(j, k) scanf("%d", &p[j]), p[j]--;
		forn(j, k) ops.PB(Operation(DEL, p[j]));
		ops.PB(Operation(QUERY, i));
		forn(j, k) ops.PB(Operation(ADD, p[j]));
	}

	work(n, edges, ops);
	forn(i, qn) printf("%s\n", ans[i]?"Connected":"Disconnected");

	return 0;
}
