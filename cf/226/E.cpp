#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;

typedef long long LL;

const int MAXN=100010;
const int MAXLen=MAXN*2;

int lson[MAXN], rson[MAXN];
int n, root;
int st[MAXN], en[MAXN];
int ind[MAXLen];

int main() {
	scanf("%d", &n);
	memset(lson, 0, sizeof(lson));
	memset(rson, 0, sizeof(rson));
	for(int i=1; i<=n; ++i) {
		int j; scanf("%d", &j);
		if(j==0) root=i;
		else rson[i]=lson[j], lson[j]=i;
	}
	return 0;
}
