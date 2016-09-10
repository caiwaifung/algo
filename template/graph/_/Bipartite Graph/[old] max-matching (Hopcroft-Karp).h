template <size_t maxn, size_t maxedges> class BiGraphMatching {
	int g[maxn], g_lnk[maxedges], g_next[maxedges];
	int dx[maxn], dy[maxn], q[maxn];
	int lx[maxn], ly[maxn];
	int n, m, ecnt;
	
	bool build() {
		int ss = 0, tt = 0;
		bool found = false;
		fillchar(dx, 0xff);
		fillchar(dy, 0xff);
		forn (x, n)
			if (lx[x] < 0)
				dx[q[tt++]=x] = 0;
		while (ss < tt)
			for (int x = q[ss++], e = g[x], y; e >= 0; e = g_next[e])
				if (dy[y=g_lnk[e]] < 0) {
					dy[y] = dx[x]+1;
					if (ly[y] < 0) found = true;
						else dx[q[tt++]=ly[y]] = dy[y]+1;
				}
		return found;
	}
	bool find(int x) {
		for (int e = g[x], y; e >= 0; e = g_next[e])
			if (dy[y=g_lnk[e]] > dx[x]) {
				dy[y] = -1;
				if (ly[y] < 0 || find(ly[y])) {
					lx[x] = y; ly[y] = x;
					return true;
				}
			}
		return false;
	}
public:
	void initialize(int _n, int _m) {
		n = _n, m = _m;
		ecnt = 0, fillchar(g, 0xff);
	}
	void add_edge(int x, int y) {
		g_lnk[ecnt] = y, g_next[ecnt] = g[x], g[x] = ecnt;
		++ ecnt;
	}
	int max_matching() {
		int ans = 0;
		fillchar(lx, 0xff);
		fillchar(ly, 0xff);
		while (build())
			forn (x, n)
				if (lx[x] < 0 && find(x))
					++ ans;
		return ans;
	}
};

