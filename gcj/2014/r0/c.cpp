#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
using namespace std;

#define forint(i, a, b) for(int i=(int)(a); i<=(int)(b); ++i)
#define forintdown(i, a, b) for(int i=(int)(a); i>=(int)(b); --i)
#define forn(i, n) forint(i, 0, (n)-1)
#define forndown(i, n) forintdown(i, (n)-1, 0)
#define fillchar(a, x) memset(a, x, sizeof(a))
typedef long long LL;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef vector<LL> VL;
typedef vector<PII> VPI;
#define MP make_pair
#define PB push_back
#define fi first
#define se second

char b[99][99];
int r, c, n;
void p() {
	b[1][1]='c';
	forint(i, 1, r) {
		forint(j, 1, c) cout<<b[i][j];
		cout<<endl;
	}
}

int main() {
	int csn; cin>>csn;
	forint(cs, 1, csn) {
		cin>>r>>c>>n;
		cout<<"Case #"<<cs<<":"<<endl;
		n=r*c-n;

		fillchar(b, '*');
		if(r==1) {
			forint(i, 1, n) b[1][i]='.';
			p();
		} else if(c==1) {
			forint(i, 1, n) b[i][1]='.';
			p();
		} else {
			if(n==1) {
				b[1][1]='.'; p();
			} else if(n==2) {
				cout<<"Impossible"<<endl;
			} else if(n<=2*c) {
				if(n%2!=0) {
					if(r==2 || c==2 || n==3) {
						cout<<"Impossible"<<endl;
					} else {
					}
				} else {
					forint(j, 1, c) forint(i, 1, 2)
						if(n>0) b[i][j]='.', --n;
				}
			} else {
				forint(i, 3, r) forint(j, 1, c)
					if(n>0) b[i][j]='.', --n;
				p();
			}
		}
	}
	return 0;
}
