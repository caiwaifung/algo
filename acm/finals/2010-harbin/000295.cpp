#include <cstdio>
#include <iostream>
#include <algorithm>
#include <map>
#include <cmath>
#include <vector>
#include <cstring>
#include <iomanip>
#include <cassert>
#define FORE(e,x) for(__typeof(x.begin()) e=x.begin();e!=x.end();++e)
using namespace std;

#define pb push_back

typedef double R;

#define TASK "channel"

const int MAXC = 9;
const int MAXN = 22;
const int MAXS = 11234;

const int EMPTY = 0;
const int LEFT = 1;
const int RIGHT = 2;
const int START = 3;
const int OTHER = 4;
const int SINGLE = 5;

char s[MAXN][MAXC + 1];
int state[MAXS][MAXC];
int toId[1953125];//5**9
int size[1<<9];
int nextState[MAXS][1<<9];
int cur[MAXC];
int scnt;

int c;

bool isEmpty(int x) {
	return x == EMPTY;
}

bool isOther(int x) {
	return x == OTHER;
}

bool isStub(int x) {
	return EMPTY < x && x < OTHER;
}

bool checkValid(int state[]) {
	int pcnt = 0;
	int scnt = 0;
	int j;
	for (j = 0; j < c; j++) {
		if(j > 0 && isStub(state[j]) && isStub(state[j-1]))
			return false;
		if(j > 1 && isStub(state[j-1]) && !isEmpty(state[j]) && !isEmpty(state[j-2]))
			return false;
		if (state[j] == START) {
			scnt++;
			if (pcnt != 0)
				return false;
		} else if (state[j] == LEFT)
			pcnt++;
		else if (state[j] == RIGHT) {
			pcnt--;
			if (pcnt < 0)
				return false;
		}
	}

	return scnt == 1 && pcnt == 0;
}

int toHash(int state[]){
	int ret = 0;
	for(int j = c-1; j >= 0; j--)
		ret = ret*5+state[j];
	return ret;
}

void dfs(int i) {
	int j;
	if (i >= c) {
		if (!checkValid(cur))
			return;
		for (j = 0; j < c; j++)
			state[scnt][j] = cur[j];
		toId[toHash(cur)] = scnt;
		scnt++;
		return;
	}

	if (i == 0 || !isStub(cur[i - 1])) {
		for (j = 0; j < 5; j++) {
			cur[i] = j;
			dfs(i + 1);
		}
	}
	else {
		for (j = 0; j < 5; j += 4) {//j \in \{EMPTY, OTHER\}
			cur[i] = j;
			dfs(i + 1);
		}
	}
}

int getStub(int id){
	int ret = 0;
	for(int j = 0; j < c; j++)
		ret |= isStub(state[id][j])<<j;
	return ret;
}

int getOther(int id){
	int ret = 0;
	for(int j = 0; j < c; j++)
		ret |= isOther(state[id][j])<<j;
	return ret;
}

int findLeft(int state[], int pos){
	assert(state[pos] == RIGHT);
	int pcnt = 1;
	while(pcnt != 0){
		pos--;
		if(state[pos] == RIGHT)
			pcnt++;
		else if(state[pos] == LEFT)
			pcnt--;
	}

	return pos;
}

int findRight(int state[], int pos){
	assert(state[pos] == LEFT);
	int pcnt = 1;
	while(pcnt != 0){
		pos++;
		if(state[pos] == LEFT)
			pcnt++;
		else if(state[pos] == RIGHT)
			pcnt--;
	}

	return pos;
}

int getNextState(int id, int mask){
	int next[MAXC+1];
	int stub = getStub(id);
	int j, k;
	if((mask & stub) != stub)
		return -1;
	int other = getOther(id);
	if(((mask^stub)&other) || ((mask^stub)&other<<1) || ((mask^stub)<<1&other))
		return -1;

	next[0] = EMPTY;
	for(j = 1; j <= c; j++)
		next[j] = state[id][j-1];

	for(j = 0; j < c; j++){
		if(mask&1<<j){
			if(isStub(next[j]) && isStub(next[j+1])){
				int cj, cj1;
				cj = cj1 = -1;
				if(next[j] == LEFT)
					cj = findRight(next, j);
				else if(next[j] == RIGHT)
					cj = findLeft(next, j);

				if(next[j+1] == LEFT)
					cj1 = findRight(next, j+1);
				else if(next[j+1] == RIGHT)
					cj1 = findLeft(next, j+1);

				if(cj == j+1 || cj1 == j)
					return -1;

				if(cj != -1 && cj1 != -1){
					if(next[j] == LEFT){
						next[cj1] = LEFT;
					}
					else if(next[j+1] == RIGHT){
						next[cj] = RIGHT;
					}
					else{

					}
				}
				else{
					if(cj != -1)
						next[cj] = next[j+1];
					if(cj1 != -1)
						next[cj1] = next[j];
				}
				next[j] = next[j+1] = OTHER;
			}
			else if(isStub(next[j]) || isStub(next[j+1])){
				int t;
				if(isStub(next[j]))
					t = next[j];
				else
					t = next[j+1];
				if(mask&1<<(j+1)){
					next[j+1] = t;
					next[j] = OTHER;
				}
				else{
					next[j] = t;
					next[j+1] = OTHER;
				}
			}
			else{
				next[j] = LEFT;
				next[j+1] = RIGHT;
			}
		}
		else{
			if(isStub(next[j]) || isStub(next[j+1]))
				return -1;
			next[j] = next[j+1] = EMPTY;
		}
	}

	if(checkValid(next))
		return toId[toHash(next)];

	return -1;
}

short f[MAXN][MAXS];
short pre[MAXN][MAXS];

int main() {
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
#else
	freopen(TASK".in", "r", stdin);
	freopen(TASK".out", "w", stdout);
#endif
	int nc = 1;
	while (true) {
		int n;
		int i, j, k;

		scnt = 0;
		scanf("%d%d", &n, &c);
		if (n == 0)
			break;

		for (i = 0; i < n; i++)
			scanf("%s", s[i]);

		dfs(0);

		memset(size, 0, sizeof size);
		for(i = 0; i < c; i++)
			for(j = 0; j < 1<<c; j++)
				if(1<<i&j)
					size[j]++;

		for(i = 0; i < scnt; i++)
			for(j = 0; j < 1<<c; j++)
				nextState[i][j] = getNextState(i, j);

		memset(f, -10, sizeof f);
		for(i = 0; i < c; i++)
			cur[i] = EMPTY;
		cur[0] = START;
		f[0][toId[toHash(cur)]] = 0;

		for(i = 0; i < n; i++){
			int block = 0;
			for(j = 0; j < c; j++)
				if(s[i][j] == '#')
					block |= 1<<j;
			for(j = 0; j < scnt; j++){
				if(f[i][j] >= 0){
					for(k = (1<<c)-1&~block; k > 0; k = (k-1)&~block){
						int t = nextState[j][k];
						if(t != -1 && f[i][j] + size[k] > f[i+1][t]){
							f[i+1][t] = f[i][j] + size[k];
							pre[i+1][t] = k;
						}
					}
				}
			}
		}

		int ans = -1;
		int ansj;
		for(j = 0; j < 1<<(c-1); j++){
			for(i = 0; i < c; i++){
				if(1<<i&j)
					cur[i] = OTHER;
				else
					cur[i] = EMPTY;
			}
			cur[c-1] = START;
			if(f[n][toId[toHash(cur)]] > ans){
				ans = f[n][toId[toHash(cur)]];
				ansj = toId[toHash(cur)];
			}
		}
		i = n;
		j = ansj;

		while(i > 0){
			int t = pre[i][j];
			i--;
			for(k = 0; k < c; k++)
				if(1<<k&t)
					s[i][k] = 'C';
			k = t;
			for(int jj = 0; jj < scnt; jj++)
				if(nextState[jj][k] == j && f[i][jj] + size[k] == f[i+1][j]){
					j = jj;
					break;
				}
		}

		cout << "Case " << nc++ << ":" << endl;
		for(i = 0; i < n; i++){
			s[i][c] = '\0';
			printf("%s\n", s[i]);
		}
		printf("\n");
	}

	return 0;
}
