#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;

typedef long long LL;

const int MAXTOT=1010;
const int MAXN=1010;

double emax[MAXTOT][MAXN];
int ep[MAXTOT][MAXN];
int n, tot, sumk;

double cv[MAXN];
double se[MAXN];

pair<double, int> all[MAXN];
int allcnt;
int whole[MAXTOT];
int must[MAXTOT];
int but[MAXTOT];

int main() {
	scanf("%d%d", &n, &tot);
	sumk=0;
	emax[0][0]=0;
	allcnt=0;
	for(int i=1; i<=tot; ++i) {
		int ck; scanf("%d", &ck);
		whole[i]=ck;
		for(int j=1; j<=ck; ++j) {
			scanf("%lf", &cv[j]);
			all[++allcnt]=make_pair(cv[j], i);
		}
		se[0]=0.0;
		for(int j=1; j<=ck; ++j) {
			for(int k=j; k>=1; --k) {
				double p=(double)k/(double)j;
				se[k]=p*(se[k-1]+cv[j])+(1.0-p)*se[k];
			}
		}
		for(int j=0; j<=ck; ++j) printf("se[%d][%d]=%.5lf\n", i, j, se[j]);
		for(int j=0; j<=sumk+ck; ++j) emax[i][j]=0.0;
		for(int j=0; j<=sumk; ++j)
			for(int k=0; k<=ck; ++k) {
				double tmp=emax[i-1][j]+se[k];
				if(tmp>emax[i][j+k]) {
					emax[i][j+k]=tmp;
					ep[i][j+k]=k;
				}
			}
		sumk+=ck;
	}
	memset(must, 0, sizeof(must));
	sort(all+1, all+allcnt+1);
	for(int i=allcnt-n+1; i<=allcnt; ++i)
		must[all[i].second]++;
	memset(but, 0, sizeof(but));
	for(int i=tot, j=n; i>=1; j-=ep[i][j], --i)
		but[i]=ep[i][j];
for(int i=1; i<=tot; ++i) printf("w[%d]=%d must[%d]=%d but[%d]=%d\n", i,whole[i],i,must[i],i,but[i]);
	for(int i=1; i<=tot; ++i) {
		if(must[i]!=but[i]) {
			printf("%.10lf\n", 0.0);
			return 0;
		}
	}
	
	double ans=1.0;
	for(int i=1; i<=tot; ++i) {
		double c=1.0;
		for(int j=1; j<=must[i]; ++j)
			c=c*(double)(whole[i]-j+1)/(double)j;
		ans/=c;
	}
	printf("%.10lf\n", ans);
	return 0;
}
