#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
using namespace std;

#define forint(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define forintdown(i, a, b) for(int i=int(a); i>=int(b); --i)
#define forn(i, n) forint(i, 0, (n)-1)
#define forndown(i, n) forintdown(i, (n)-1, 0)
#define fillchar(a, x) memset(a, x, sizeof(a))
#define fi first
#define se second
#define PB push_back
#define MP make_pair
typedef long long LL;
typedef pair<double,double> PDD;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
typedef vector<int> VI;
typedef vector<LL> VL;
typedef vector<PII> VPI;
typedef vector<PLL> VPL;

const int as[30]={
	100, 80, 60, 50, 45, 40, 36, 32, 29, 26, 24, 22, 20, 18, 16,
	15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

map<string, int> score;

void pre(const char *fname) {
	FILE *f=fopen(fname, "r");
	forn(i, 30) {
		char s[999];
		fgets(s, 900, f);
		int len=strlen(s);
		while(len>0 && (s[len-1]=='\n' || s[len-1]=='\r' || s[len-1]==' ' || s[len-1]=='\t'))
			--len;
		s[len]='\0';
		score[string(s)]+=as[i];
	}
	fclose(f);
}

int main() {
	score.clear();
	pre("r1.txt");
	pre("r2.txt");
	pre("r3.txt");
	printf("s.size=%d\n",score.size());

	vector<pair<int, string> > lst;
	for(map<string, int>::iterator it=score.begin(); it!=score.end(); ++it)
		lst.PB(MP(it->se, it->fi));
	sort(lst.rbegin(), lst.rend());
	forn(i, lst.size()) {
		printf("%2d: %3d  %s\n", i+1, lst[i].fi, lst[i].se.c_str());
	}
	return 0;
}
