#include <cstring>
#include <algorithm>
#include <string>
#include <cstdio>
#include <iostream>
#include <vector>
#ifdef __OFFLINE_TEST
#include <Windows.h>
#endif
using namespace std;

const int STEPS = 10000;
const int MAXN=16;
const int C_ELI = 10;
typedef long long LL;
#define PB push_back
#define MP make_pair
#define fi first
#define se second
typedef pair<int,int> PII;

int abs(int x) {
	return x < 0 ? -x : x;
}

int n;
int color_num;

struct Move {
	int i, j, dir;
	Move() : i(0), j(0), dir(1) {}
	Move(int i1, int j1, int i2, int j2) {
		if (i1 == i2) {
			dir = 1;
			if (j1 < j2) i = i1, j = j1;
				else i = i2, j = j2;
		} else {
			dir = 2;
			if (i1 < i2) i = i1, j = j1;
				else i = i2, j = j2;
		}
	}
};
struct MoveSeq {
	int val;
	vector<Move> moves;

	MoveSeq() : val(-1) {}
	MoveSeq(int val) : val((1<<30) - val) {}
	bool update(const MoveSeq &b) {
		if (val < b.val) {
			*this = b;
			return true;
		}
		return false;
	}
};

struct Board {
	int a[MAXN][MAXN];
	int seed;

	Board() {}
	Board(vector<string> board, int s) {
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				a[i][j]=int(board[i][j]-'0');
		seed = s;
	}

	static int next_seed(int &seed) {
		int ans = seed % color_num;
		seed = int((LL(seed) * 48271LL) % 2147483647LL);
		return ans;
	}

	bool eliminate() {
		for (int i = 0; i+1 < n; ++i)
			for (int j = 0; j+1 < n; ++j)
				if (a[i][j] == a[i+1][j] && a[i][j] == a[i][j+1] && a[i][j] == a[i+1][j+1]) {
					a[i][j] = next_seed(seed);
					a[i][j+1] = next_seed(seed);
					a[i+1][j] = next_seed(seed);
					a[i+1][j+1] = next_seed(seed);
					return true;
				}
		return false;
	}
	bool perform(const Move &move) {
		if (move.dir == 1) {
			swap(a[move.i][move.j], a[move.i][move.j+1]);
		} else {
			swap(a[move.i][move.j], a[move.i+1][move.j]);
		}
		bool flag = false;
		while (eliminate()) flag = true;
		return flag;
	}
};

#ifdef __OFFLINE_TEST
namespace Debug {
	bool enabled = true;
	void enable() {
		enabled = true;
	}
	void disable() {
		enabled = false;
	}
	void pboard(Board board) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j)
				cerr << board.a[i][j] << " ";
			cerr << endl;
		}
	}
	DWORD time[999];
	DWORD start[999];
	void start_tick(int i) {
		start[i] = GetTickCount();
	}
	void end_tick(int i) {
		time[i] += GetTickCount() - start[i];
	}
	double time_s(int i) {
		return time[i] / 1000.0;
	}
};
#endif

template<size_t N, class T> struct TopN {
	int d[N];
	T v[N];
	int max_val;
	TopN() {
		memset(d, 50, sizeof(d));
		max_val = d[0];
	}
	int size() const {
		int n = 0;
		while (n < N && d[n] < max_val)
			++n;
		return n;
	}
	void update(int cd, const T &cv) {
		if (cd < d[N - 1]) {
			d[N - 1] = cd;
			v[N - 1] = cv;
			for (int i = N - 1; i > 0 && d[i] < d[i - 1]; --i) {
				swap(d[i], d[i - 1]);
				swap(v[i], v[i - 1]);
			}
		}
	}
};

struct BipartiteGraph {
	int xi[4], xj[4], xn;
	int yi[16], yj[16], yn;
	int g[4][16];

	int mx[4], my[16];
	int min_cost;

	BipartiteGraph(const Board &b, int ci, int cj, int c) {
//Debug::start_tick(0);
		xn = 0;
		for (int u = 0; u < 2; ++u)
			for (int v = 0; v < 2; ++v)
				if (b.a[ci + u][cj + v] != c) {
					xi[xn] = ci + u;
					xj[xn] = cj + v;
					++xn;
				}
		vector<PII> lc;
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				if (b.a[i][j] == c) {
					if (i >= ci && i <= ci+1 && j >= cj && j <= cj+1)
						continue;
					lc.PB(MP(i, j));
				}

		yn = 0;
		for (int k = 0; k < xn; ++k) {
//Debug::start_tick(2);
			int u = xi[k], v = xj[k];
			TopN<4, PII> top;
			for (size_t p = 0; p < lc.size(); ++p) {
				int i = lc[p].fi, j = lc[p].se;
				top.update(abs(u - i) + abs(v - j), MP(i, j));
			}
			for (int p = 0; p < top.size(); ++p) {
				int i = top.v[p].fi;
				int j = top.v[p].se;
				bool flag = true;
				for (int q = 0; q < yn; ++q)
					if (i == yi[q] && j == yj[q])
						flag = false;
				if (flag) {
					yi[yn] = i;
					yj[yn] = j;
					++yn;
				}
			}
//Debug::end_tick(2);
		}

		for (int x = 0; x < xn; ++x)
			for (int y = 0; y < yn; ++y)
				g[x][y] = abs(xi[x] - yi[y]) + abs(xj[x] - yj[y]);
//Debug::end_tick(0);
	}

	bool compute_min() {
		if (yn < xn)
			return false;
		memset(mx, 0xff, sizeof(mx));
		memset(my, 0xff, sizeof(my));
		min_cost = 0;
		for (int x = 0; x < xn; ++x) {
			int best = 1<<30;
			int best_y = 0;
			for (int y = 0; y < yn; ++y)
				if (my[y] < 0 && g[x][y] < best) {
					best = g[x][y];
					best_y = y;
				}
			mx[x] = best_y;
			my[best_y] = x;
			min_cost += best;
		}
		return true;
	}
};

class SquareRemover {
public:
	MoveSeq compute_move(const Board &b, int ci, int cj, int c);
	vector<int> playIt(int color_n, vector<string> start_board, int start_seed);
};

// want to make a square at ([ci,ci+1],[cj,cj+1]) with color c
// return minimal moves as well as next move
MoveSeq SquareRemover::compute_move(const Board &b, int ci, int cj, int c) {
	int found = 0;
	for (int i = ci; i < ci + 2; ++i)
		for (int j = cj; j < cj + 2; ++j)
			if (b.a[i][j] == c)
				++found;
	if (found < 2)
		return MoveSeq();

	BipartiteGraph graph(b, ci, cj, c);
	if (!graph.compute_min())
		return MoveSeq();

	/*
	if (ci == 0 && cj == 2 && c == 1) {
		cerr << "compute_move: graph built (" << graph.xn << ", " << graph.yn << ")" << endl;
		cerr << "  graph.cost = " << graph.min_cost << endl;
		for (int i = 0; i < graph.xn; ++i) {
			cerr << "  graph.mx[(" << graph.xi[i] << ", " << graph.xj[i] << ")] = ";
			cerr << "[(" << graph.yi[graph.mx[i]] << ", " << graph.yj[graph.mx[i]] << ")]" << endl;
		}
	}
	*/

	int si = graph.xi[0], sj = graph.xj[0];
	int ti = graph.yi[graph.mx[0]], tj = graph.yj[graph.mx[0]];
	MoveSeq ans(graph.min_cost);
	for (int i = si, j = sj; b.a[i][j] != c; ) {
		si = i, sj = j;
		if (i != ti) {
			if (i < ti) ++i; else --i;
		} else {
			if (j < tj) ++j; else --j;
		}
		ans.moves.PB(Move(si, sj, i, j));
	}
	reverse(ans.moves.begin(), ans.moves.end());
	return ans;
}


vector<int> SquareRemover::playIt(int color_n, vector<string> start_board, int start_seed) {
	n = (int)start_board.size();
	color_num = color_n;

	Board board(start_board, start_seed);
	while (board.eliminate());

	vector<int> ret;
//Debug::start_tick(0);
	for (int cur = 0; cur < STEPS; ) {
		//if (cur > 300) { ret.PB(0); ret.PB(0); ret.PB(1); continue; }

		//if (cur % 1000 == 0) cerr << "cur = " << cur << endl; //Debug::pboard(board);

		MoveSeq best;
		//int bi, bj, bc;
		for (int i = 0; i+1 < n; ++i)
			for (int j = 0; j+1 < n; ++j)
				for (int c = 0; c < color_num; ++c) {
					MoveSeq cur = compute_move(board, i, j, c);
					best.update(cur);
					//if (best.update(cur))
						//bi = i, bj = j, bc = c;
				}
		for (size_t i = 0; i < best.moves.size(); ++i) {
			Move move = best.moves[i];
			ret.PB(move.i);
			ret.PB(move.j);
			ret.PB(move.dir);
			++cur;
			if (board.perform(move))
				break;
			if (cur >= STEPS)
				break;
		}
//Debug::end_tick(1);

		/*
if (cur % 100 == 0) {
cerr << "   tot time: " << Debug::time_s(1) << endl;
cerr << "   bi_graph time: " << Debug::time_s(0) << endl;
cerr << "   bi_graph sort time: " << Debug::time_s(2) << endl;
}
*/
		//cerr << "best.val = " << (1<<30) - best.val << endl;
		//cerr << "bi = " << bi << " bj = " << bj << " bc = " << bc << endl;

	}
//Debug::end_tick(0);
//cerr << "   tot time: " << Debug::time_s(0) << endl;
	return ret;
}

#ifdef __OFFLINE_TEST
int main() {
	int color_num, n, seed;
	vector<string> board;

	cin>>color_num>>n;
	board.resize(n);
	for (int i = 0; i < n; ++i)
		cin>>board[i];
	cin>>seed;

	vector<int> ret = (new SquareRemover())->playIt(color_num, board, seed);

	for (size_t i = 0; i < ret.size(); ++i)
		cout<<ret[i]<<endl;

	fflush(stdout);
	return 0;
}
#endif
