template<size_t MAX_N, size_t MAX_E> struct Graph {
	int e_link[MAX_E], e_next[MAX_E];
	int first[MAX_N], degree[MAX_N];
	int n, e;
	void initalize(int nodes) {
		memset(first, 0, sizeof(first));
		memset(degree, 0, sizeof(degree));
		n = nodes;
		e = 0;
	}
	void add_edge(int x, int y) {
		e_link[++ e] = y;
		e_next[e] = first[x];
		first[x] = e;
		degree[y] ++;
	}
};

template<size_t MAX_N, size_t MAX_E> class SCC {
	int low[MAX_N], dfn[MAX_N], cnt;
	int stack[MAX_N], top;
	void dfs(const Graph<MAX_N, MAX_E> &graph, Graph<MAX_N, MAX_E> &blocks,
			int belong[], int head[], int x) {
		low[x] = dfn[x] = ++ cnt;
		stack[++ top] = x;
		belong[x] = -1;
		for (int e = graph.first[x]; e > 0; e = graph.e_next[e]) {
			int y = graph.e_link[e];
			if (-1 == belong[y])
				low[x] = min(low[x], dfn[y]);
			if (0 == belong[y]) {
				dfs(graph, blocks, belong, head, y);
				low[x] = min(low[x], low[y]);
			}
		}
		if (low[x] == dfn[x]) {
			head[++ blocks.n] = x;
			do {
				belong[stack[top --]] = blocks.n;
			} while (stack[top + 1] != x);
		}
	}
public:	
	void compute_scc(const Graph<MAX_N, MAX_E> &graph, Graph<MAX_N, MAX_E> &blocks,
			int belong[], int head[]) {
		blocks.initalize(0);
		for (int i = 1; i <= graph.n; i ++)
			belong[i] = 0;
		cnt = top = 0;
		for (int i = 1; i <= graph.n; i ++)
			if (0 == belong[i])
				dfs(graph, blocks, belong, head, i);
	}	
};
