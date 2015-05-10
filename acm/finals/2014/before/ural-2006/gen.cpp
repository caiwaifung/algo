#include <vector>
#include <iostream>
#include <cstring>
#include <set>
#include <cstdio>
using namespace std;

int main() {
	printf("1000 100\n");
	printf("1 1\n");
	printf("1000 1\n");
	for(int i=1; i<=1000; ++i) {
		for(int j=1; j<=100; ++j) printf(".");
		printf("\n");
	}
	return 0;
}
