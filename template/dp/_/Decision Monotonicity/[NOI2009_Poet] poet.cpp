#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

typedef unsigned long long ULL;
typedef long double LD;

const ULL maxval=(ULL)1E18;
const int maxn=100010;
const int maxl=3000010;

char word[maxn][35];
int len[maxn], sum[maxn];
int n, l, p;

LD f[maxn];
int pre[maxn];

LD abs(LD x) { return x>0?x:-x; }
LD pow(int x) {
	LD a=abs(x), ans=1;
	for(int i=p; i; i>>=1, a*=a) if(i&1) ans*=a;
	return ans;
}

/*	start template	*/
LD w(int i, int j) {
	return pow(sum[j]-sum[i-1]-l);
}

bool worse(int x, int i, int j) {
	return f[i]+w(i+1,x)>=f[j]+w(j+1,x);
}

int cal(int i, int j) {
	int le=max(i,j)+1, ri=n+1;
	while(le<ri) {
		int x=(le+ri)>>1;
		if(worse(x, i, j)) ri=x;
			else le=x+1;
	}
	return le;
}

void solve() {
	int time[maxn], q[maxn];
	int ss, tt;
	q[ss=tt=1]=0;
	f[0]=0;
	memset(pre, sizeof(pre), 0);
	for(int i=1; i<=n; i++) {
		while(ss<tt && worse(i, q[ss], q[ss+1])) ss++;
		int j=pre[i]=q[ss];
		f[i]=f[j]+pow(sum[i]-sum[j]-l);
		while(ss<tt && time[tt-1]>=cal(q[tt], i)) tt--;
		q[++tt]=i;
		if(ss<tt) time[tt-1]=cal(q[tt-1], q[tt]);
	}
}
/*	end template	*/

void init() {
	scanf("%d%d%d", &n, &l, &p);
	l++;
	for(int i=1; i<=n; i++) {
		scanf("%s", word[i]);
		len[i]=strlen(word[i])+1;
	}
	sum[0]=0;
	for(int i=1; i<=n; i++) sum[i]=sum[i-1]+len[i];
}

bool lab[maxn];
void answer() {
	memset(lab, 0, sizeof(lab));
	for(int i=n; i; i=pre[i]) lab[i]=true;
	ULL ans=0;
	int cur=0;
	for(int i=1; i<=n; i++) {
		cur+=len[i];
		if(lab[i]) {
			cur=abs(cur-l);
			ULL tmp=1;
			for(int j=1; j<=p; j++)
				if (cur>0 && tmp>maxval/cur) {
					printf("Too hard to arrange\n"); return;
				} else tmp*=cur;
			ans+=tmp;
			if(ans>maxval) {
				printf("Too hard to arrange\n"); return;
			}
			cur=0;
		}
	}
	cout<<ans<<endl;
	for(int i=1; i<=n; i++) printf("%s%c", word[i], lab[i]?'\n':' ');
}

int main() {
	freopen("poet.in", "r", stdin);
	freopen("poet.out", "w", stdout);
	int cs;
	scanf("%d", &cs);
	while(cs--) {
		init();
		solve();
		answer();
		for(int i=1; i<=20; i++) printf("-");
		printf("\n");
	}
	return 0;
}
