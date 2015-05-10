#include <iostream>
#include <sstream>
#include <algorithm>
#include <set>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

typedef long long LL;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef vector<LL> VLL;
#define PB push_back
#define MP make_pair
#define forint(i, a, b) for(int i=(int)(a); i<=(int)(b); ++i)
#define forintdown(i, a, b) for(int i=(int)(a); i>=(int)(b); --i)
#define forn(i, n) for(int i=0; i<(int)(n); ++i)
#define forndown(i, n) for(int i=(int)(n)-1; i>=0; --i)
#define fillchar(a, x) memset(a, x, sizeof(a))
template<class T> void setmin(T &a, T b) { if(b<a) a=b; }
template<class T> void setmax(T &a, T b) { if(b>a) a=b; }

class EnclosingTriangle {
public:
	int mult(int x0, int y0, int x1, int y1, int x2, int y2) {
		LL tmp=(LL)(x1-x0)*(LL)(y2-y0) - (LL)(x2-x0)*(LL)(y1-y0);
		if(tmp==0) return 0; else return tmp<0 ? -1 : 1;
	}
	bool check(VI &x, VI &y, int x1, int y1, int x2, int y2, int sgn) {
		forn(i, x.size())
			if(sgn*mult(x1, y1, x2, y2, x[i], y[i])<0)
				return false;
		return true;
	}
	long long getNumber(int m, vector <int> x, vector <int> y) {
		#define nxt(i) ((i)==num-1?0:(i+1))
		#define lst(i) ((i)==0?num-1:(i-1))
		VI posX, posY;
		int num=m*4;
		posX.resize(num);
		posY.resize(num);
		forint(i, 0, m-1) {
			posX[i]=i, posY[i]=0;
			posX[i+m]=m, posY[i+m]=i;
			posX[i+m*2]=m-i, posY[i+m*2]=m;
			posX[i+m*3]=0, posY[i+m*3]=m-i;
		}
		//forn(i, num) printf("%d: (%d,%d)\n", i, posX[i],posY[i]);
		VI pl, pr, pdr; VLL sdr;
		pl.resize(num);
		pr.resize(num);
		pl[0]=lst(0);
		for(int i=0; ; i=lst(i)) {
			while(1) {
				int p=lst(pl[i]);
				if(!check(x, y, posX[i], posY[i], posX[p], posY[p], -1)) break;
				pl[i]=p;
			}
			if(lst(i)==0) break;
			pl[lst(i)]=pl[i];
		}
		pr[0]=nxt(0);
		for(int i=0; ; i=nxt(i)) {
			while(1) {
				int p=nxt(pr[i]);
				if(!check(x, y, posX[i], posY[i], posX[p], posY[p], +1)) break;
				pr[i]=p;
			}
			if(nxt(i)==0) break;
			pr[nxt(i)]=pr[i];
		}
		//forn(i, num) printf("%d: l=%d r=%d\n", i,pl[i],pr[i]);
		pdr.resize(num);
		sdr.resize(num);
		forn(i, num) {
			pdr[i]=pr[i];
			if(pdr[i]<i) pdr[i]+=num;
			sdr[i]=pdr[i];
			if(i>0) sdr[i]+=sdr[i-1];
		}
		//
		LL ans=0;
		forn(x, num) {
			int y=pl[x];
			int z=pr[x];
			int p=pr[z];
			int q=pl[y];
			//printf("x=%d y=%d z=%d p=%d q=%d tmp=%lld\n", x,y,z,p,q,0);
			if(mult(posX[x],posY[x], posX[y],posY[y], posX[p],posY[p])<0) continue;
			if(mult(posX[x],posY[x], posX[z],posY[z], posX[q],posY[q])>0) continue;
			LL tmp=0;
			if(z>=q) {
				tmp=sdr[z];
				if(q>0) tmp-=sdr[q-1];
				if(y<z) y+=num;
				tmp-=(LL)(y-1)*(LL)(z-q+1);
			} else {
				tmp=sdr[z];
				if(y<z) y+=num;
				tmp-=(LL)(y-1)*(LL)(z+1);
				y%=num;

				tmp+=sdr[num-1]-sdr[q-1];
				y+=num;
				tmp-=(LL)(y-1)*(LL)(num-q);
			}
			if(y==z) tmp-=6;
			//printf("x=%d y=%d z=%d p=%d q=%d tmp=%lld\n", x,y,z,p,q,tmp);
			//printf("x=%d y=%d z=%d p=%d q=%d tmp=%lld\n", x,y,z,p,q,tmp);
			ans+=tmp;
		}
		return ans/3;
	}

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 4; int Arr1[] = { 1, 2, 3 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = { 1, 3, 2 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 19LL; verify_case(0, Arg3, getNumber(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 7; int Arr1[] = { 1, 1, 6, 6 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = { 1, 6, 1, 6 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 0LL; verify_case(1, Arg3, getNumber(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 4; int Arr1[] = { 2 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = { 2 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 224LL; verify_case(2, Arg3, getNumber(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 10; int Arr1[] = { 2, 6, 7, 6 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = { 7, 7, 9, 3 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 81LL; verify_case(3, Arg3, getNumber(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 15; int Arr1[] = { 7, 6, 5, 4, 3 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = { 1, 4, 7, 10, 13 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 283LL; verify_case(4, Arg3, getNumber(Arg0, Arg1, Arg2)); }

// END CUT HERE

};
// BEGIN CUT HERE
int main(){
	EnclosingTriangle ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
