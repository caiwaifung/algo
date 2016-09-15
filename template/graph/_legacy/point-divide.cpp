const int MAX_N = int(1e5) + 10, INF = ~0U >> 1;
int n;
int size[MAX_N];

struct Edge {
	int t, c;
	Edge(int t, int c) :
			t(t), c(c) {
	}
};

vector<Edge> E[MAX_N];
bool del[MAX_N];
typedef long long int64;

struct Data {

	void add(int64 d) {
	}

	int64 eval(int64 d) {
	}
};

struct Split {
	//Branch
	Data all;
	vector<Data> maps;

	void clear() {
		all = Data();
		maps.clear();
	}
};

struct SplitPtr {
	Split*sp;
	int at;
	int64 val;

	SplitPtr(Split*sp, int at, int64 val) :
			sp(sp), at(at), val(val) {
	}

	int64 eval() {
		return sp->all.eval(val) - sp->maps[at].eval(val);
	}

	void add() {
		sp->all.add(val), sp->maps[at].add(val);
	}
};

int seq[MAX_N], pt, opt[MAX_N];

void dfs(int u, int par) {
	size[u] = 1, seq[pt++] = u;
	opt[u] = 0;
	for (vector<Edge>::iterator e = E[u].begin(); e != E[u].end(); ++e)
		if (e->t != par && !del[e->t]) {
			dfs(e->t, u), size[u] += size[e->t];
			opt[u] = max(opt[u], size[e->t]);
		}
}

int que[MAX_N], qh, qt, fa[MAX_N];
void bfs(int rt, int par) {
	qh = qt = 0;
	que[qt++] = rt;
	fa[rt] = par;

	while (qh < qt) {
		int u = que[qh++];
		for (vector<Edge>::iterator e = E[u].begin(); e != E[u].end(); ++e)
			if (e->t != fa[u] && !del[e->t]) {
				que[qt++] = e->t;
				fa[e->t] = u;
			}
	}
}

Split splits[MAX_N];
vector<SplitPtr> my[MAX_N];

void dfs2(int u, int par, int64 dep, Split*sp, int at) {
	my[u].push_back(SplitPtr(sp, at, dep));

	for (vector<Edge>::iterator e = E[u].begin(); e != E[u].end(); ++e)
		if (e->t != par && !del[e->t]) {
			dfs2(e->t, u, dep + e->c, sp, at);
		}
}

void bfs2(int rt, int par, int64 dep, Split*sp, int at) {
	static int64 D[MAX_N];
	qh = qt = 0;
	que[qt++] = rt;
	fa[rt] = par;
	D[rt] = dep;

	while (qh < qt) {
		int u = que[qh++];

		my[u].push_back(SplitPtr(sp, at, D[u]));

		for (vector<Edge>::iterator e = E[u].begin(); e != E[u].end(); ++e)
			if (e->t != fa[u] && !del[e->t]) {
				fa[e->t] = u;
				D[e->t] = D[u] + e->c;
				que[qt++] = e->t;
			}
	}
}

void build(int rt) {

	bfs(rt, -1);

	for (int i = qt - 1; i >= 0; --i) {
		int u = que[i];
		size[u] = 1;
		opt[u] = 0;
		for (auto e : E[u])
			if (!del[e.t] && fa[e.t] == u) {
				size[u] += size[e.t];
				opt[u] = max(opt[u], size[e.t]);
			}
	}

	int tot = size[rt];
	int minOpt = tot + 1, by = -1;
	for (int i = 0; i < tot; ++i) {
		int u = que[i];
		opt[u] = max(opt[u], tot - size[u]);
		if (opt[u] < minOpt)
			minOpt = opt[u], by = u;
	}

	rt = by;
	int cnt = 0;
	del[rt] = true;

	Split*sp = splits + rt;
	sp->clear();

	for (vector<Edge>::iterator e = E[rt].begin(); e != E[rt].end(); ++e)
		if (!del[e->t]) {
			sp->maps.push_back(DistDesc());
			bfs2(e->t, rt, e->c, sp, cnt), cnt++;
		}

//  sp->all.ensure(value[rt]);
	sp->maps.push_back(DistDesc());
	my[rt].push_back(SplitPtr(sp, cnt, 0)), cnt++;

	for (vector<Edge>::iterator e = E[rt].begin(); e != E[rt].end(); ++e)
		if (!del[e->t]) {
			build(e->t);
		}
}

int64 eval(int u) {
	int64 ans = 0;
	for (vector<SplitPtr>::iterator e = my[u].begin(); e != my[u].end(); ++e) {
		ans += e->eval();
	}
	return ans;
}

void add(int u) {
	for (vector<SplitPtr>::iterator e = my[u].begin(); e != my[u].end(); ++e) {
		e->add();
	}
}
