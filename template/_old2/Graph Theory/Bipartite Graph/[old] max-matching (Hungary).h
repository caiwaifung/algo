template <size_t SZ_X, size_t SZ_RIGHT, size_t SZ_EDGES> class BiGraphMatching {
	struct Edge {
		int lnk;
		Edge *next;
	};
	Edge edges[SZ_EDGES];
	Edge* first[SZ_X];
	int ly[SZ_RIGHT];
	bool visy[SZ_RIGHT];
	int N, M, e_cnt;
	
	bool find(int x) {
		for (Edge* e = first[x]; e != NULL; e = e->next)
			if (! visy[e->lnk]) {
				visy[e->lnk] = true;
				if (ly[e->lnk] < 0 || find(ly[e->lnk])) {
					ly[e->lnk] = x;
					return true;
				}
			}
		return false;
	}
public:
	void initialize(int _N, int _M) {
		N = _N, M = _M;
		e_cnt = 0, fillchar(first, 0);
	}
	void add_edge(int x, int y) {
		Edge* e = &edges[e_cnt ++];
		e->lnk = y, e->next = first[x], first[x] = e;
	}
	int max_matching() {
		int ans = 0;
		fillchar(ly, 0xFF);
		forn (i, N) {
			fillchar(visy, false);
			if (find(i)) ++ ans;
		}
		return ans;
	}
};
