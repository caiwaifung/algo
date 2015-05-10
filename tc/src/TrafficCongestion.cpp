#include <vector>
using namespace std;
#define forint(i, a, b) for(int i=(int)(a); i<=(int)(b); ++i)

const int MOD=(int)1E9+7;

class TrafficCongestion {
public:
	int theMinCars(int treeHeight) {
		vector<int> m2;
		m2.resize(1100000);
		m2[0]=1;
		forint(i, 1, (int)m2.size()-1) m2[i]=(m2[i-1]*2)%MOD;
		int ans=0;
		int n=treeHeight;
		while(n>1) {
			(ans+=m2[n-1])%=MOD;
			n-=2;
		}
		ans++;
		return ans;
	}

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 1; verify_case(0, Arg1, theMinCars(Arg0)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 3; verify_case(1, Arg1, theMinCars(Arg0)); }
	void test_case_2() { int Arg0 = 3; int Arg1 = 5; verify_case(2, Arg1, theMinCars(Arg0)); }
	void test_case_3() { int Arg0 = 585858; int Arg1 = 548973404; verify_case(3, Arg1, theMinCars(Arg0)); }

// END CUT HERE

};
// BEGIN CUT HERE
int main(){
	TrafficCongestion ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
