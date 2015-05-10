// 12:02 - 12:19 - ac
#include <cstring>
#include <iostream>
#include <cstdio>
using namespace std;

#define forint(i, a, b) for(int i=int(a); i<=int(b); ++i)
typedef long long LL;

const int MAXN=550;

int d[MAXN][MAXN];
int a, b;
int n, m;
LL ans;

int cd[MAXN];
int s, t;

int stack[MAXN], top;

void update(int i, int j, int h0) {
	if(i>j) return;
	bool flag=false;
	if(t-s+1<=a && j-i+1<=b) flag=true;
	if(t-s+1<=b && j-i+1<=a) flag=true;
	if(!flag) return;
	LL e=(t-s+1)*(j-i+1);
	LL h=(e*h0-1)/(n*m-e)+h0;
	LL tmp=e*h;
	//printf("s=%d t=%d i=%d j=%d h0=%d h=%I64d ans=%I64d\n",s,t,i,j,h0,h,ans);
	ans=max(ans, tmp);
}

int main() {
	while(scanf("%d%d", &a,&b)!=EOF) {
		scanf("%d%d", &n,&m);
		forint(i, 1, n) forint(j, 1, m) {
			scanf("%d", &d[i][j]);
		}
		ans=0;
		for(s=1; s<=n; ++s) {
			forint(j, 1, m) cd[j]=1<<30;
			cd[0]=-2, cd[m+1]=-1;
			for(t=s; t<=n; ++t) {
				forint(j, 1, m) cd[j]=min(cd[j], d[t][j]);
				top=0;
				stack[++top]=0;
				forint(j, 1, m+1) {
					while(cd[stack[top]]>=cd[j]) {
						update(stack[top-1]+1, j-1, cd[stack[top]]);
						--top;
					}
					stack[++top]=j;
				}
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
