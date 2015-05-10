#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

#define forint(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define forintdown(i, a, b) for(int i=int(a); i>=int(b); --i)
#define forn(i, n) forint(i, 0, (n)-1)
#define forndown(i, n) forintdown(i, (n)-1, 0)
#define fillchar(a, x) memset(a, x, sizeof(a))
#define fi first
#define se second
#define PB push_back
#define MP make_pair
typedef long long LL;
typedef pair<int,int> PII;
typedef vector<PII> VPI;
typedef pair<double,double> PDD;

const int dx[8]={-1, -1, -1, 0, 0, 1, 1, 1};
const int dy[8]={-1, 0, 1, -1, 1, -1, 0, 1};
const int score[9]={0,0,0, 1,1, 2, 3, 5, 11};

const int MAXNODE=301000*8;
const int MAXN=300010;

int trie[MAXNODE][26];
int tcnt[MAXNODE], tcur[MAXNODE];
int tmp_tcur[MAXNODE];
int node_cnt;
string words[MAXN];

bool vis[6][6];
int ans_s, ans_c; string ans_b;
char board[6][6];

void dfs(int x, int y, int cur) {
	if(vis[x][y]) return;
	cur=trie[cur][board[x][y]-'A'];
	if(cur==0 || tcnt[cur]==0) return;
	if(tcur[cur]>0) {
		int i=tcur[cur]; tcur[cur]=0;
		ans_s+=score[words[i].size()];
		ans_c++;
		if(words[i].size()>ans_b.size() || (words[i].size()==ans_b.size() && words[i]<ans_b))
				ans_b=words[i];
	}
	vis[x][y]=true;
	forn(i, 8) dfs(x+dx[i], y+dy[i], cur);
	vis[x][y]=false;
}

int main() {
	node_cnt=1;
	fillchar(trie, 0);
	fillchar(tcur, 0);
	fillchar(tcnt, 0);
	int n; scanf("%d", &n);
	forint(i, 1, n) {
		char s[99]; scanf("%s", s); int len=strlen(s);
		int cur=1;
		words[i]=string(s);
		forn(j, len) {
			++tcnt[cur];
			int y=s[j]-'A';
			if(trie[cur][y]==0)
				trie[cur][y]=++node_cnt;
			cur=trie[cur][y];
		}
		++tcnt[cur], tcur[cur]=i;
	}

	int cs; scanf("%d", &cs);
	memmove(tmp_tcur, tcur, sizeof(tcur));
	while(cs--) {
		memmove(tcur, tmp_tcur, sizeof(tcur));
		forint(i, 1, 4) scanf("%s", board[i]+1);
		fillchar(vis, true);
		forint(i, 1, 4) forint(j, 1, 4) vis[i][j]=false;
		ans_s=ans_c=0, ans_b="";
		forint(i, 1, 4) forint(j, 1, 4) dfs(i, j, 1);
		printf("%d %s %d\n", ans_s, ans_b.c_str(), ans_c);
	}
	return 0;
}
