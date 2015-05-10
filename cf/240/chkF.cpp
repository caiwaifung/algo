#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
typedef pair<int,int> PII;
#define MP make_pair
#define PB push_back

const int n=5;
const int m=3;
const int c=3;

int main() {
	srand(123423534);
	for(int cs=1; ; ++cs) {
		printf("Case #%d: ", cs);
		FILE *f=fopen("input.txt", "w");
		fprintf(f, "%d %d\n", n,m);
		for(int i=1; i<=n; ++i) fprintf(f, "%c", rand()%c+'a');
		fprintf(f, "\n");
		for(int i=1; i<=m; ++i) {
			int l=rand()%n+1, r=rand()%n+1;
			if(l>r) swap(l, r);
			fprintf(f, "%d %d\n", l,r);
		}
		fclose(f);
		system("./F2 > F2.out");
		system("./rngF");
		char a[n*2], b[n*2];
		freopen("F2.out", "r", stdin); scanf("%s", a);
		freopen("output.txt", "r", stdin); scanf("%s", b);
		if(strcmp(a,b)==0) printf("correct. %s\n", a);
		else {printf("erro!\n");for(;;);}
	}
	return 0;
}
