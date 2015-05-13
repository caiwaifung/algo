#include<cstdio>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<string>
#include<cmath>
#include<vector>
#include<queue>
#include<set>

using namespace std;

const int MAX_N = int(1e5) + 10;

const int MAX_F = MAX_N * 3;

typedef long long int64;

struct P {
	int x, y;
	P(int x = 0, int y = 0) :
			x(x), y(y) {
	}
	P operator+(P o) {
		return P(x + o.x, y + o.y);
	}
	P operator-(P o) {
		return P(x - o.x, y - o.y);
	}
	int64 operator*(P o) {
		return 1LL * x * o.x + 1LL * y * o.y;
	}
	int64 operator^(P o) {
		return 1LL * x * o.y - 1LL * y * o.x;
	}
	double al() {
		return atan2(y, x);
	}
	double abs() {
		return hypot(x, y);
	}
	void read() {
		scanf("%d%d", &x, &y);
		x *= 2, y *= 2;
	} //*2
	bool operator==(const P&o) const {
		return x == o.x && y == o.y;
	}
};

//replace alpha with det if posssible :)

int sign(int64 x) {
	return x < 0 ? -1 : x > 0;
}

int64 cross(P p1, P p2, P p3) {
	return (p2 - p1) ^ (p3 - p1);
}

int crossOp(P p1, P p2, P p3) {
	return sign(cross(p1, p2, p3));
}

int n, m, nQ;
P ps[MAX_N];

struct Edge;

vector<Edge*> allE;

struct Edge {
	Edge*rev, *nxt, *pre;
	double alpha;
	int sta, tar;
	int cst;

	int id;

	Edge(int sta, int tar, int cst) :
			sta(sta), tar(tar), cst(cst), id(-1) {
		alpha = (ps[tar] - ps[sta]).al();
		allE.push_back(this);
	}
};

vector<Edge*> es[MAX_N];

Edge* makeEdge(int u, int v, int c) {
	Edge*e = new Edge(u, v, c);
	es[u].push_back(e);
	return e;
}

void addEdge(int u, int v, int c) {
	Edge*uv = makeEdge(u, v, c);
	Edge*vu = makeEdge(v, u, c);
	uv->rev = vu, vu->rev = uv;
}

bool cmp(Edge*a, Edge*b) {
	return a->alpha < b->alpha;
}

int nId;

int forbid;

void buildGraph() {
	//sort
	for (int i = 0; i < n; ++i) {
		vector<Edge*>&arr = es[i];
		if (arr.empty())
			continue;
		sort(arr.begin(), arr.end(), cmp);
		for (int j = 0; j < arr.size(); ++j) {
			Edge*nxt;
			if (j + 1 < arr.size())
				nxt = arr[j + 1];
			else
				nxt = arr[0];
			arr[j]->nxt = nxt;
			nxt->pre = arr[j];
		}
	}

	//build

	nId = 0;
	for (int it = 0; it < allE.size(); ++it) {
		Edge*e = allE[it];
		if (e->id != -1)
			continue;

		int64 area = 0;

		while (e->id == -1) {
			area += ps[e->sta] ^ ps[e->tar];
			e->id = nId;
			e = e->rev->pre;
		}

		if (area < 0) {
			forbid = nId;
		}

		nId++;
	}

	//build MST
}
