#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;

int rr() {
	int x=rand()%10000*10000+rand()%10000;
	return x;
}

int main() {
	srand(123456789);
	printf("10\n");
	for(int t=0; t<10; ++t) {
		int n=2000;
		//if(t<20) w-=rr()%(w/2), n-=rr()%(n/2);
		printf("%d\n", n);
		int p=rand()%500+30;
		while(n>0) {
			int t=rr()%min(n,p)+1;
			n-=t;
			int a, b;
			while(1) {
				a=-rr()%100-1;
				b=rr()%10000;
				if(-b/a>100) break;
			}
			for(int i=0; i<t; ++i)
				while(1) {
					int x=rr()%1000+1;
					int y=a*x*x+b*x;
					if(y<1 || y>1000000) continue;
					else {
						printf("%d %d\n", x,y);
						break;
					}
				}
		}
	}
	return 0;
}
