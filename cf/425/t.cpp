#include <cstdio>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <map>
#include <vector>
using namespace std;

#define forint(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define forintdown(i, a, b) for(int i=int(a); i>=int(b); --i)
#define forn(i, n) forint(i, 0, (n)-1)
#define forndown(i, n) forintdown(i, (n)-1, 0)
#define fi first
#define se second
#define PB push_back
#define MP make_pair
typedef long long LL;
typedef pair<int,int> PII;
typedef vector<PII> VPI;
typedef pair<double,double> PDD;

int main() {
	while(1) {
		printf("temporary compiler>>> ");
		char s[99], t[999];
		scanf("%s", s);
		if(s[0]=='e') break;
		if(s[0]=='c') {
			scanf("%s", s);
			sprintf(t, "g++ %s.cpp -o %s -g -Wall -Wconversion -Wextra", s,s);
			system(t);
			continue;
		}
		if(s[0]=='r') {
			scanf("%s", s);
			system(s);
			continue;
		}
		if(s[0]=='t') {
			scanf("%s", s);
			sprintf(t, "%s <%s.in", s,s);
			system(t);
			continue;
		}
	}
	return 0;
}
