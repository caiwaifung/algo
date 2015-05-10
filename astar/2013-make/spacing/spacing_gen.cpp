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
	printf("50\n");
	for(int t=0; t<50; ++t) {
		int w=80000, n=50000;
		if(t<20) w-=rr()%(w/2), n-=rr()%(n/2);
		printf("%d %d\n", w, n);
		w=(w-1)/2;
		w=max(3, rand()%w+1);
		/*
		if(rand()%2==0) w=min(w, 10000);
		else if(rand()%2==0) w=min(w, 1000);
		else if(rand()%2==0) w=min(w, 100);
		*/
		//if(rand()%2==0) w=min(w, 10);
		for(int i=1; i<=n; ++i) {
			int t=w;
			//while(t>9 && rand()%2==0) t/=10;
			printf("%d%c", rr()%t+1, i<n?' ':'\n');
		}
	}
	return 0;
}
