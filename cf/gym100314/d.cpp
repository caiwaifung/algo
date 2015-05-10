#include <cstdlib>
#include <set>
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

const int MAXN=1010;
const int MAXW=10010;

string words[MAXW];
char w1[MAXW], w2[MAXW];
char s[MAXN];
int n, wn;

int cnt[MAXN][MAXN], id[MAXN][MAXN];
int f[MAXN], p[MAXN];

struct Vec {
	int non_zeros;
	int a[33];
	Vec() {
		fillchar(a, 0);
		non_zeros=0;
	}
	void add(int x, int y) {
		if(a[x]==0) --non_zeros;
		a[x]+=y;
		if(a[x]==0) ++non_zeros;
	}
};

int main() {
	int cs; scanf("%d", &cs);
	while(cs--) {
		scanf("%s", s+1); n=strlen(s+1);
		scanf("%d", &wn);
		forint(i, 1, wn) {
			static char buf[999];
			scanf("%s", buf); words[i]=string(buf);
			w1[i]=words[i][0];
			w2[i]=words[i][words[i].size()-1];
		}
		fillchar(cnt, 0);
		forint(i, 1, wn) {
			int len=words[i].size();
			if(len>n) continue;
			Vec vec;
			forn(j, len) vec.add(words[i][j]-'a', -1);
			forint(j, 1, len) vec.add(s[j]-'a', 1);
			forint(j, len, n) {
				if(j>len) {
					vec.add(s[j-len]-'a', -1);
					vec.add(s[j]-'a', 1);
				}
				if(vec.non_zeros==0 && w1[i]==s[j-len+1] && w2[i]==s[j]) {
					++cnt[j-len+1][j];
					id[j-len+1][j]=i;
				}
			}
		}
		f[0]=1;
		forint(i, 1, n) {
			f[i]=0;
			forint(j, 1, i) if(f[j-1]>0 && cnt[j][i]>0) {
				f[i]+=f[j-1]*cnt[j][i];
				p[i]=j;
			}
			f[i]=min(f[i], 2);
		}
		if(f[n]==0) printf("impossible\n");
		else if(f[n]>1) printf("ambiguous\n");
		else {
			vector<string> ans;
			for(int i=n, j; i>=1; i=j-1) {
				j=p[i];
				ans.PB(words[id[j][i]]);
			}
			forndown(i, ans.size()) printf("%s ", ans[i].c_str());
			printf("\n");
		}
	}
	return 0;
}
