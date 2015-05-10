#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <set>
#include <map>
using namespace std;

#define all(a) a.begin(), a.end()
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
typedef vector<string> VS;
typedef vector<int> VI;
typedef vector<PII> VPI;
template<class T> void setmax(T &a, T b) { if(b>a) a=b; }
template<class T> void setmin(T &a, T b) { if(b<a) a=b; }
template<class T> T gcd(T a, T b) { return b==0?a:gcd(b,a%b); }


// ------------------------ template ends here ------------------------ //

const int B1=1000000;

class TheLuckyBasesDivOne {
	LL lucks[199999];
	int num;
	void dfs(LL x) {
		if(x>LL(1e16))
			return;
		if(x>0)
			lucks[++num]=x;
		dfs(x*10+4);
		dfs(x*10+7);
	}
	bool isLuck(LL n) {
		if(n==0)
			return false;
		while(n>0) {
			LL x=n%10; n/=10;
			if(x!=4 && x!=7)
				return false;
		}
		return true;
	}
	bool isLuck(LL n, LL b) {
		if(n==0)
			return false;
		while(n>0) {
			LL x=n%b; n/=b;
			if(!isLuck(x))
				return false;
		}
		return true;
	}
public:
	LL goTwoDigits(LL n) { // b > B1
		LL ans=0;
		// n = x b + y
		forint(i, 1, num) {
			LL x=lucks[i];
			if(x*(x+1)>n) break;
			forint(j, 1, num) {
				LL y=lucks[j];
				if(x*(y+1)>n) break;
				LL b=(n-y)/x;
				if(x*b+y==n && x<b && y<b && b>B1)
					++ans;
			}
		}
		return ans;
	}
	LL solve(LL x, LL y, LL z, LL n) {
		LL le=B1+1;
		setmax(le, x+1);
		setmax(le, y+1);
		setmax(le, z+1);
		if(x*le*le+y*le+z>n) return 0;
		LL ri=(LL)sqrt(double(n/x)*1.2);
		while(le<ri) {
			LL b=(le+ri+1)/2;
			if(x*b*b+y*b+z>n)
				ri=b-1;
			else
				le=b;
		}
		return le;
	}
	LL goThreeDigits(LL n) { // b > B1
		LL ans=0;
		// n = x b^2 + y b + z
		forint(i, 1, num) {
			LL x=lucks[i];
			if(x*(x+1)*(x+1)>n) break;
			forint(j, 1, num) {
				LL y=lucks[j];
				if(x*(y+1)*(y+1)>n) break;
				forint(k, 1, num) {
					LL z=lucks[k];
					if(x*(z+1)*(z+1)>n) break;
					LL b=solve(x, y, z, n);
					if(x*b*b+y*b+z==n && x<b && y<b && z<b && b>B1)
						++ans;
				}
			}
		}
		return ans;
	}
	long long find(long long n) {
		num=0;
		dfs(0);
		sort(lucks+1, lucks+num+1);
		printf("num = %d\n", num);

		if(isLuck(n))
			return -1;
		LL ans=0;
		forint(b, 2, B1)
			if(isLuck(n, b))
				++ans;
		ans+=goTwoDigits(n);
		ans+=goThreeDigits(n);

		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long long Arg0 = 255LL; long long Arg1 = 2LL; verify_case(0, Arg1, find(Arg0)); }
	void test_case_1() { long long Arg0 = 474LL; long long Arg1 = -1LL; verify_case(1, Arg1, find(Arg0)); }
	void test_case_2() { long long Arg0 = 13LL; long long Arg1 = 0LL; verify_case(2, Arg1, find(Arg0)); }
	void test_case_3() { long long Arg0 = 4748LL; long long Arg1 = 5LL; verify_case(3, Arg1, find(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	TheLuckyBasesDivOne ___test;
	/*
	___test.run_test(0);
	/*/
	___test.run_test(-1);
	//*/
	return 0;
}
// END CUT HERE
