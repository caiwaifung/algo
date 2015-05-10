#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
using namespace std;

#define forint(i, a, b) for(int i=(int)(a); i<=(int)(b); ++i)
#define forintdown(i, a, b) for(int i=(int)(a); i>=(int)(b); --i)
#define forn(i, n) forint(i, 0, (n)-1)
#define forndown(i, n) forintdown(i, (n)-1, 0)
#define fillchar(a, x) memset(a, x, sizeof(a))
typedef long long LL;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef vector<LL> VL;
typedef vector<PII> VPI;
#define MP make_pair
#define PB push_back
#define fi first
#define se second

const int MAXN=100010;

int a[MAXN], b[MAXN];
int n, m;
int x[MAXN];
VI pos[MAXN];

int main() {
	scanf("%d%d",&n,&m);
	forint(i, 1, m) {
		char s[99];
		scanf("%s%d", s,b+i);
		if(s[0]=='+') a[i]=1; else a[i]=-1;
		pos[b[i]].PB(i);
	}

	static bool ins[MAXN]; fillchar(ins, false);
	int minv=0;
	x[0]=0;
	forint(i, 1, m) {
		if(a[i]>0) ins[b[i]]=true;
		else {
			if(!ins[b[i]]) ++minv;
			else ins[b[i]]=false;
		}
		x[i]=x[i-1]+a[i];
	}
	forint(i, 0, m) x[i]+=minv;

	static bool ok[MAXN];
	set<int> cc;
	forint(i, 1, m) if(a[i]>0 && x[i-1]==0)
		cc.insert(b[i]);
	forint(i, 1, n) {
		if(pos[i].size()==0) {
			ok[i]=true; continue;
		}
		ok[i]=true;
		forn(j, pos[i].size()) {
			int k=pos[i][j];
			if(a[k]>0) {
				if(x[k-1]>0) ok[i]=false;
			} else {
				if(x[k]>0) ok[i]=false;
				if(cc.size()>1) ok[i]=false;
			}
		}
	}
	int t=0; forint(i, 1, n) if(ok[i]) ++t;
	printf("%d\n", t);
	forint(i, 1, n) if(ok[i]) printf("%d ", i); if(t) printf("\n");
	return 0;
}
