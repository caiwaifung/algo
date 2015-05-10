#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
typedef pair<int,int> PII;
#define MP make_pair
#define PB push_back
#define forint(i, a, b) for(int i=(int)a; i<=(int)b; ++i)

const int MAXH=1<<23;

int h[MAXH];
LL hx[MAXH]; int hnxt[MAXH]; int hn;

int main() {
	hn=0;
	memset(h, 0, sizeof(h));
	forint(i, 1, 2000) {
		//printf("i=%d\n", i);
		forint(j, 1, 2000)
			forint(k, 1, 2000) {
				LL tmp=(LL)i*(LL)j*(LL)k;
				int p=tmp&(MAXH-1);
				bool found=false;
				for(int k=h[p]; k>0; k=hnxt[k])
					if(hx[k]==tmp) {
						found=true;
						break;
					}
				if(!found) {
					++hn;
					hx[hn]=tmp; hnxt[hn]=h[p]; h[p]=hn;
					if(hn%100000==0) printf("i=%d hn=%d\n", i,hn);
				}
			}
	}
	printf("ans=%d\n", hn);
	return 0;
}
