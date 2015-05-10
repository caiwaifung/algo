#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN=1000000+10;
const int MODNUM=1000000000+7;

int tmp[MAXN], vl[MAXN], el[MAXN], tl[MAXN];
char s[MAXN];
int n, k;

int main() {
	scanf("%d%d%s", &n, &k, s);
	for(int i=n; i>=1; --i) s[i]=s[i-1];
	tl[0]=1;
	for(int i=1; i<=n; ++i) tl[i]=(tl[i-1]*(s[i]=='X'?2:1))%MODNUM;
	vl[0]=el[0]=0;
	for(int i=k; i<=n; ++i) {
		
	}
	for(int i=0; i<k; ++i) vl[i]=0;
	for(int i=1; i<=k-1; ++i) cur+=(s[i]=='W');
	for(int i=k; i<=n; ++i) {
		vl[i]=(vl[i-1]*(s[i]=='X'?2:1))%MODNUM;
		cur+=(s[i]=='W');
		if(cur==0) vl[i]=(vl[i]+tmp[i-k])%MODNUM;
		cur-=(s[i-k+1]=='W');
	}
	for(int i=1; i<=n; ++i) printf("tmp[%d]=%d\n", i, tmp[i]);
	for(int i=1; i<=n; ++i) printf("vl[%d]=%d\n", i, vl[i]);

	cur=tmp[n+1]=1;
	for(int i=n; i>=1; --i)
		if(s[i]=='X') {
			tmp[i]=cur; cur=(cur*2)%MODNUM;
		} else
			if(s[i]=='W') tmp[i]=0;
				else tmp[i]=cur;
	cur=0;
	for(int i=n; i>=n-k+2; --i) cur+=(s[i]=='B');
	int ans=0;
	for(int i=n-k+1; i>=1; --i) {
		cur+=(s[i]=='B');
		if(cur==0) ans=(ans+vl[i-1])%MODNUM;
		cur-=(s[i+k-1]=='B');
	}
	printf("%d\n", ans);
	return 0;
}
