template<size_t N, size_t E> class TwoSat {
	Graph<N*2, E*2> graph, blocks;
	SCC<N*2, E*2> scc;
	int belong[N*2], head[N*2];
	int stack[N*2];
	bool answer[N*2];
	int n;   
	
public:
	void initalize(int nodes) {
		graph.initalize(nodes * 2);
		n = nodes;
	}
	
	void add_conflict(int x, int sx, int y, int sy) {
		graph.add_edge(x + sx*n, y + (sy^1)*n);
		graph.add_edge(y + sy*n, x + (sx^1)*n);
	}
	
	bool compute(int scheme[]) {
		scc.compute_scc(graph, blocks, belong, head);
	
		for (int i = 1; i <= n; i ++)
			if (belong[i] == belong[i+n])
				return false;
		for (int x = 1; x <= graph.n; x ++)
			for (int i = graph.first[x]; i > 0; i = graph.e_next[i])
				if (belong[x] != belong[graph.e_link[i]])
					blocks.add_edge(belong[graph.e_link[i]], belong[x]);
			
		memset(answer, true, sizeof(answer));
		int top = 0;
		for (int x = 1; x <= blocks.n; x ++)
			if (blocks.degree[x] == 0)
				stack[++ top] = x;
		while (top > 0) {
			int x = stack[top --];
			#define oppo(x) ((x)<=n?(x)+n:(x)-n)
			if (answer[x])
				answer[belong[oppo(head[x])]]=false;
			for (int i = blocks.first[x]; i > 0; i = blocks.e_next[i])
				if (-- blocks.degree[blocks.e_link[i]] == 0)
					stack[++ top] = blocks.e_link[i];
		}
		for (int i = 1; i <= n; i ++)
			scheme[i] = (answer[belong[i]] ? 0 : 1);
		return true;
	}
};
