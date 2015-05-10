#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;

int rr() {
	int x=rand()%10000*10000+rand()%10000;
	return x;
}
int r() {
	int x=rr();
	x=x%200001;
	x-=100000;
	return x;
}

int main() {
	srand(123456789);
	printf("10\n");
	for(int t=0; t<10; ++t) {
		int n=80000, m=100000;
		for(int p=0; p<7; ++p) if(t<=p) n/=2,m/=2;
		printf("%d %d\n", n, m);
		for(int i=1; i<=n; ++i) printf("%d%c", r(), i<n?' ':'\n');
		while(m--) {
			if(rand()%2==0) {
				printf("I %d %d\n",rr()%n+1, r());
			} else {
				int L=rr()%n+1;
				int R=rr()%n+1;
				if(L>R) swap(L,R);
				int k=min(4,R-L+1);
				k=rand()%k+1;
				printf("C %d %d %d\n",L,R,k);
			}
		}
	}
	return 0;
}
