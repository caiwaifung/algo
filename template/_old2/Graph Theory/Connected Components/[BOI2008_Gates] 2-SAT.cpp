#include <iostream>
using namespace std;

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

template<size_t MAX_N, size_t MAX_E> class TwoSat {
	Graph<MAX_N*2, MAX_E*2> graph, blocks;
	SCC<MAX_N*2, MAX_E*2> scc;
	int belong[MAX_N*2], head[MAX_N*2];
	int stack[MAX_N*2];
	bool answer[MAX_N*2];
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

TwoSat<500010, 250010> two_sat;
int scheme[500010];
int n, m;

int main() {
   // freopen("in.txt","r",stdin);freopen("out.txt","w",stdout);
	scanf("%d%d", &m, &n);
	two_sat.initalize(n);
	while (m --) {
		int x, sx, y, sy;
		scanf("%d%d%d%d", &x, &sx, &y, &sy);
		two_sat.add_conflict(x, sx^1, y, sy^1);
	}
	if (two_sat.compute(scheme))
		for (int i = 1; i <= n; i ++)
			printf("%d\n", scheme[i]);
	else
		printf("IMPOSSIBLE\n");
	return 0;
}

