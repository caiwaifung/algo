#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

#define fi first
#define se second
#define PB push_back
#define MP make_pair

typedef vector<pair<char,int> > AnsT;
typedef long long LL;
AnsT no;
int a, m, p, q, r, s;

bool better(AnsT a, AnsT b) {
	if(a==no) return false;
	//printf("#1\n");
	if(b==no) return true;
	//printf("#2\n");
	int sa=0; for(size_t i=0; i<a.size(); ++i) sa+=a[i].se;
	int sb=0; for(size_t i=0; i<b.size(); ++i) sb+=b[i].se;
	if(sa!=sb) return sa<sb;
	for(size_t i=0; i<a.size(); ++i) {
		if(a[i].fi!=b[i].fi) return a[i].fi<b[i].fi;
		if(a[i].se!=b[i].se)
			return (a[i].fi=='A' ? a[i].se>b[i].se : a[i].se<b[i].se);
	}
	return false;
}

AnsT cal(int n_mul) {
	int x=1;
	for(int i=1; i<=n_mul; ++i) {
		if(x>s/m) return no;
		x*=m;
	}
	//printf("x=%d\n",x);
	int y=0;
	if(p<=r/x) {
		int delta=r-p*x;
		y=(delta+a-1)/a;
	}
	//printf("y=%d\n",y);
	if(LL(q)*LL(x)+LL(y)*LL(a)>s) return no;
	int y2=(s-q*x)/a;
	//printf("here\n");
	AnsT ans; int cy=0;
	vector<int> px(n_mul+1);
	px[n_mul]=1;
	for(int i=n_mul-1; i>=0; --i)
		px[i]=px[i+1]*m;
	for(int i=0; i<=n_mul; ++i) {
		int c1=(y2-cy)/px[i];
		int c2=(y-cy+px[i]-1)/px[i];
		int cur=min(c1, c2);
		cy+=cur*px[i];
		if(cur>0) ans.PB(MP('A',cur));
		if(i<n_mul) {
			if(ans.size()>0 && ans.back().fi=='M')
				++ans[ans.size()-1].se;
			else ans.PB(MP('M',1));
		}
	}
	return ans;
}

int main() {
	no.PB(MP('*',0));
	int cs=0;
	while(1) {
		cin>>a>>m>>p>>q>>r>>s;
		if(a==0) break;
		AnsT ans=no;
		for(int t=0; t<=32; ++t) {
			AnsT tmp=cal(t);
			//printf("t=%d tmp=%d ans=%d\n",t,tmp==no,ans==no);
			if(better(tmp, ans)) ans=tmp;
			//printf("t=%d tmp=%d ans=%d\n",t,tmp==no,ans==no);
		}
		printf("Case %d:", ++cs);
		if(ans==no) printf(" impossible\n");
		else if(ans.size()==0) printf(" empty\n");
		else {
			for(size_t i=0; i<ans.size(); ++i)
				printf(" %d%c", ans[i].se,ans[i].fi);
			printf("\n");
		}
	}
	return 0;
}
