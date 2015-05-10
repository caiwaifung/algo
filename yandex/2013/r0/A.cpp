#include <iostream>
#include <cstdio>
using namespace std;

int main() {
	int s[2], n, l;
	scanf("%d%d", &n, &l);
	s[0]=s[1]=0;
	for(int i=1; i<=n; ++i) {
		int k, p; scanf("%d%d", &k, &p);
		k--;
		if(p<0) s[k]++; else
		if(p<=l) s[k]+=2;
		else s[k]+=3;
	}
	printf("%d:%d\n", s[0],s[1]);
	return 0;
}
