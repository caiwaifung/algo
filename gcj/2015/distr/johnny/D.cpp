#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include "message.h"
#include "johnny.h"
using namespace std;
typedef long long int64;

vector<int> E[int(2e4) + 10];
bool vis[int(2e4) + 10];

void dfs(int u) {
	if (vis[u])
		return;

	vis[u] = true;
	for (vector<int>::iterator e = E[u].begin(); e != E[u].end(); ++e) {
		dfs(*e);
	}
}

int main() {
	int N = NumberOfCards();
	int nNodes = NumberOfNodes();
	int64 block = N / nNodes + 1;
	int id = MyNodeId();
	int64 L = id * block, R = (id + 1) * block;
	if (R > N)
		R = N;

	//every one find a chain
	static int chain[int(2e4) + 10];
	static int at[int(2e4) + 10];
	int tot = 0;
	chain[tot++] = 0;
	for (int i = 1; i < N; ++i) {
		if (IsBetter(i, chain[0])) {
			memmove(chain + 1, chain, sizeof(int) * tot);
			chain[0] = i;
			++tot;
			continue;
		}
		if (IsBetter(chain[tot - 1], i)) {
			chain[tot++] = i;
			continue;
		}
		int L = 0, R = tot - 1;
		//chain[L]>i and i>chain[R]
		while (L + 1 < R) {
			int M = (L + R) >> 1;
			if (IsBetter(chain[M], i)) {
				L = M;
			} else {
				R = M;
			}
		}
		memmove(chain + R + 1, chain + R, sizeof(int) * (tot - R));
		chain[R] = i;
		++tot;
	}

	for (int i = 0; i + 1 < N; ++i) {
		assert(IsBetter(chain[i], chain[i + 1]));
	}

	//now we have the chain
	//chain[0]->chain[1]->....chain[n-1]
	for (int i = 0; i < N; ++i) {
		at[chain[i]] = i;
	}

	static int maxPrev[int(2e4) + 10];

	for (int i = L; i < R; ++i) {
		maxPrev[i] = i;
		for (int j = 0; j < i; ++j) {
			if (IsBetter(chain[i], chain[j])) {
				maxPrev[i] = j;
				break;
			}
		}
	}

	if (id > 0) {
		PutInt(0, R - L);
		for (int i = L; i < R; ++i) {
			PutInt(0, maxPrev[i]);
		}
		Send(0);
		return 0;
	} else {
		int cur = R;
		for (int i = 1; i < nNodes; ++i) {
			Receive(i);
			int cnt = GetInt(i);
			while (cnt--)
				maxPrev[cur++] = GetInt(i);
		}

		for (int i = 0; i < N; ++i) {
			if (i + 1 < N)
				E[i].push_back(i + 1);	//i->i+1
			if (maxPrev[i] != i)
				E[i].push_back(maxPrev[i]);
		}
		dfs(N - 1);
		int cnt = 0;
		for (int i = 0; i < N; ++i) {
			if (vis[i])
				++cnt;
		}

		if (cnt == N) {
			puts("IMPOSSIBLE");
		} else {
			cout << N - cnt << endl;
		}
	}
}
