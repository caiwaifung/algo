#include <cstdio>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <map>
#include <vector>
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

const int MAXN=111;
const int MOD=int(1e9+7);

string s[MAXN];
int head[MAXN], tail[MAXN];
int n;

bool check() {
	int oc[33]; fillchar(oc, 0);
	forint(i, 1, n) {
		int o[33]; fillchar(o, 0);
		forn(j, s[i].size()) {
			int k=int(s[i][j]-'a'+1);
			if(o[k]==0) {
				++o[k]; ++oc[k];
			}
		}
	}

	forint(i, 1, n) {
		bool flag=true;
		forn(j, s[i].size()) if(s[i][j]!=s[i][0]) flag=false;
		if(flag) {
			head[i]=tail[i]=int(s[i][0]-'a'+1);
			continue;
		}
		int x=0, y=s[i].size()-1;
		head[i]=int(s[i][x]-'a'+1);
		tail[i]=int(s[i][y]-'a'+1);
		if(s[i][x]==s[i][y]) return false;
		while(s[i][x]==s[i][0]) ++x;
		while(s[i][y]==s[i][s[i].size()-1]) --y;
		forint(j, x, y) {
			if(oc[int(s[i][j]-'a'+1)]>1) return false;
		}
		char la=s[i][x]; bool o[33]; fillchar(o, false);
		forint(j, 0, s[i].size()-1) {
			if(o[int(s[i][j]-'a'+1)] && la!=s[i][j]) return false;
			o[int(s[i][j]-'a'+1)]=true;
			la=s[i][j];
		}
	}
	return true;
}

int go() {
	int oc[33], mi[33];
	fillchar(oc, 0); fillchar(mi, 0);
	forint(i, 1, n) {
		++oc[head[i]]; ++oc[tail[i]];
		if(head[i]==tail[i]) ++mi[head[i]];
	}

	int lnk[33]; fillchar(lnk, 0);
	int plnk[33]; fillchar(plnk, 0);
	forint(i, 1, n) if(head[i]!=tail[i]) {
		if(lnk[head[i]]>0) return 0;
		if(plnk[tail[i]]>0) return 0;
		lnk[head[i]]=tail[i];
		plnk[tail[i]]=head[i];
	}
	bool vis[33]; fillchar(vis, false);
	int cnt=0;
	forint(c, 1, 30) if(oc[c]>0 && plnk[c]==0 && !vis[c]) {
		++cnt;
		for(int x=c; x; x=lnk[x]) vis[x]=true;
	}
	forint(c, 1, 30) if(oc[c]>0 && !vis[c]) return 0;

	int fac[111];
	fac[0]=1;
	forint(i, 1, 110) {
		fac[i]=int(LL(fac[i-1])*LL(i)%MOD);
	}
	LL ans=fac[cnt];
	forint(c, 1, 30) if(oc[c]>0) {
		ans=(ans*fac[mi[c]])%MOD;
	}
	return int(ans);
}

int main() {
	freopen("B-large-practice.in", "r", stdin);
	freopen("B.out", "w", stdout);
	int csn; scanf("%d",&csn);
	forint(cs, 1, csn) {
		//printf("cs=%d csn=%d\n",cs,csn);
		printf("Case #%d: ", cs);
		scanf("%d", &n); forint(i, 1, n) {
			char b[999]; scanf("%s", b);
			s[i]=string(b);
		}
		if(!check()) {printf("0\n"); continue;}
		//forint(i, 1, n) printf("[%d %d]\n",head[i],tail[i]);
		int ans=go();
		printf("%d\n", ans);
		/*
		int p[999]; forint(i, 1, n) p[i]=i;
		int std=0;
		//forint(i, 1, n) printf("(%d %d)\n",head[i],tail[i]);
		do {
			int now=head[p[1]];
			bool vis[99]; fillchar(vis, false);
			vis[head[p[1]]]=true;
			bool ok=true;
			forint(i, 1, n) {
				if(vis[head[p[i]]] && now!=head[p[i]]) ok=false;
				if(vis[tail[p[i]]] && head[p[i]]!=tail[p[i]]) ok=false;
				vis[head[p[i]]]=true;
				vis[tail[p[i]]]=true;
				now=tail[p[i]];
			}
			if(ok) ++std;
		} while(next_permutation(p+1, p+n+1));
		if(ans!=std) {printf("erro! std=%d\n",std);for(;;);}
		//*/
	}
	return 0;
}
