#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

#define _ (int)
#define all(a) a.begin(), a.end()
#define rep(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define irep(i, a, b) for(int i=int(a); i>=int(b); --i)
#define repn(i, n) rep(i, 0, (n)-1)
#define irepn(i, n) irep(i, (n)-1, 0)
#define fillchar(a, x) memset(a, x, sizeof(a))
#define fi first
#define se second
#define pb push_back
#define mp make_pair
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef pair<int,int> PII;
typedef pair<double,double> PDD;
typedef vector<LL> VL;
typedef vector<int> VI;
typedef vector<PII> VPI;
typedef vector<string> VS;
template<class T> bool setmax(T &_a, T _b) { if(_b>_a) { _a=_b; return true; } return false; }
template<class T> bool setmin(T &_a, T _b) { if(_b<_a) { _a=_b; return true; } return false; }
template<class T> T gcd(T _a, T _b) { return _b==0?_a:gcd(_b,_a%_b); }

class AllGraphCuts {
public:
    int n, g[55][55];
    VI ans;

    void add(int x, int y, int w) {
        ans.pb(w*n*n+x*n+y);
    }

    bool solve(VI xs) {
        if(xs.size()<=1) return true;
        int mv=-1;
        for(int x: xs) for(int y: xs) setmax(mv, g[x][y]);
        vector<bool> bs(n, false);
        for(int x: xs) for(int y: xs) if(g[x][y]==mv) bs[x]=bs[y]=true;
        for(int x: xs) for(int y: xs) if(x!=y) {
            bool z1=(g[x][y]==mv);
            bool z2=(bs[x] && bs[y]);
            if(z1!=z2) return false;
        }
        VI ys, zs;
        for(int x: xs) if(bs[x]) ys.pb(x); else zs.pb(x);
        rep(i, 1, ys.size()-1) add(ys[0], ys[i], mv);
        zs.pb(ys[0]);
        return solve(zs);
    }

    vector <int> findGraph(vector <int> input) {
        n=1; while(n*n!=_ input.size()) ++n;
        repn(i, n) repn(j, n) g[i][j]=input[i*n+j];

        repn(i, n) if(g[i][i]!=0) return VI{-1};
        repn(i, n) repn(j, n) if(g[i][j]!=g[j][i]) return VI{-1};
        ans.clear();

        VI xs; repn(i, n) xs.pb(i);
        if(!solve(xs)) return VI{-1};
        return ans;
    }
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arr0[] = {0,1,
 1,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {6 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, findGraph(Arg0)); }
	void test_case_1() { int Arr0[] = {0,1,
 1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-1 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, findGraph(Arg0)); }
	void test_case_2() { int Arr0[] = {0,2,2,
 2,0,2,
 2,2,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {10, 11, 14 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, findGraph(Arg0)); }
	void test_case_3() { int Arr0[] = {0,1,2,3,4,
 1,0,2,3,4,
 1,2,0,3,4,
 1,2,3,0,4,
 1,2,3,4,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-1 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, findGraph(Arg0)); }
	void test_case_4() { int Arr0[] = {0,0,0,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(4, Arg1, findGraph(Arg0)); }
	void test_case_5() { int Arr0[] = {
0, 2545, 2348, 2993, 2606, 2623, 2013, 3001, 2626, 2440, 2495, 2262, 2342, 2617, 2773, 2662, 2736, 2827, 3044, 3082,
2545, 0, 2348, 2545, 2545, 2545, 2013, 2545, 2545, 2440, 2495, 2262, 2342, 2545, 2545, 2545, 2545, 2545, 2545, 2545,
2348, 2348, 0, 2348, 2348, 2348, 2013, 2348, 2348, 2348, 2348, 2262, 2342, 2348, 2348, 2348, 2348, 2348, 2348, 2348,
2993, 2545, 2348, 0, 2606, 2623, 2013, 2993, 2626, 2440, 2495, 2262, 2342, 2617, 2773, 2662, 2736, 2827, 2993, 2993,
2606, 2545, 2348, 2606, 0, 2606, 2013, 2606, 2606, 2440, 2495, 2262, 2342, 2606, 2606, 2606, 2606, 2606, 2606, 2606,
2623, 2545, 2348, 2623, 2606, 0, 2013, 2623, 2623, 2440, 2495, 2262, 2342, 2617, 2623, 2623, 2623, 2623, 2623, 2623,
2013, 2013, 2013, 2013, 2013, 2013, 0, 2013, 2013, 2013, 2013, 2013, 2013, 2013, 2013, 2013, 2013, 2013, 2013, 2013,
3001, 2545, 2348, 2993, 2606, 2623, 2013, 0, 2626, 2440, 2495, 2262, 2342, 2617, 2773, 2662, 2736, 2827, 3001, 3001,
2626, 2545, 2348, 2626, 2606, 2623, 2013, 2626, 0, 2440, 2495, 2262, 2342, 2617, 2626, 2626, 2626, 2626, 2626, 2626,
2440, 2440, 2348, 2440, 2440, 2440, 2013, 2440, 2440, 0, 2440, 2262, 2342, 2440, 2440, 2440, 2440, 2440, 2440, 2440,
2495, 2495, 2348, 2495, 2495, 2495, 2013, 2495, 2495, 2440, 0, 2262, 2342, 2495, 2495, 2495, 2495, 2495, 2495, 2495,
2262, 2262, 2262, 2262, 2262, 2262, 2013, 2262, 2262, 2262, 2262, 0, 2262, 2262, 2262, 2262, 2262, 2262, 2262, 2262,
2342, 2342, 2342, 2342, 2342, 2342, 2013, 2342, 2342, 2342, 2342, 2262, 0, 2342, 2342, 2342, 2342, 2342, 2342, 2342,
2617, 2545, 2348, 2617, 2606, 2617, 2013, 2617, 2617, 2440, 2495, 2262, 2342, 0, 2617, 2617, 2617, 2617, 2617, 2617,
2773, 2545, 2348, 2773, 2606, 2623, 2013, 2773, 2626, 2440, 2495, 2262, 2342, 2617, 0, 2662, 2736, 2773, 2773, 2773,
2662, 2545, 2348, 2662, 2606, 2623, 2013, 2662, 2626, 2440, 2495, 2262, 2342, 2617, 2662, 0, 2662, 2662, 2662, 2662,
2736, 2545, 2348, 2736, 2606, 2623, 2013, 2736, 2626, 2440, 2495, 2262, 2342, 2617, 2736, 2662, 0, 2736, 2736, 2736,
2827, 2545, 2348, 2827, 2606, 2623, 2013, 2827, 2626, 2440, 2495, 2262, 2342, 2617, 2773, 2662, 2736, 0, 2827, 2827,
3044, 2545, 2348, 2993, 2606, 2623, 2013, 3001, 2626, 2440, 2495, 2262, 2342, 2617, 2773, 2662, 2736, 2827, 0, 3044,
3082, 2545, 2348, 2993, 2606, 2623, 2013, 3001, 2626, 2440, 2495, 2262, 2342, 2617, 2773, 2662, 2736, 2827, 3044, 0
}
; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {76801, 87602, 76403, 15604, 14005, 14406, 95607, 14408, 45609, 54010, 113211, 102812, 53613, 72414, 10015, 90416, 110417, 108818, 76819, 20022, 5223, 16824, 14025, 20426, 37227, 115628, 118829, 105230, 39631, 114032, 70833, 2434, 9235, 71636, 3637, 108438, 68439, 16443, 24444, 37245, 54046, 118447, 46048, 13249, 38450, 27651, 23652, 105253, 76054, 22455, 112056, 5657, 82458, 28859, 31264, 117665, 73666, 91667, 11268, 67269, 110870, 18471, 114872, 119673, 22074, 86075, 44876, 22477, 74478, 93679, 96085, 8486, 59687, 110088, 1689, 107290, 56091, 56092, 74893, 61294, 109295, 109296, 18097, 66498, 20899, 12506, 98907, 82908, 77309, 51710, 110111, 108112, 22513, 66514, 43315, 36516, 19717, 15318, 26519, 34127, 70128, 8929, 20930, 131, 81732, 80133, 29334, 68935, 53336, 81737, 36538, 57739, 35348, 96149, 25750, 19351, 15752, 4153, 80554, 107355, 96556, 70557, 66958, 48559, 33769, 81370, 55771, 15372, 61373, 72574, 11375, 2976, 66577, 108178, 57779, 590, 78991, 14992, 10593, 69794, 47395, 33796, 113397, 77398, 68999, 77811, 28212, 12613, 64614, 80215, 9816, 27017, 30618, 73819, 46632, 66633, 7834, 100635, 636, 7437, 4238, 76639, 87453, 16254, 10255, 31856, 50257, 18258, 3459, 73474, 69475, 63876, 41077, 3878, 28679, 13495, 56696, 109497, 101098, 116699, 60316, 107517, 12318, 98719, 51137, 91138, 81139, 108358, 119959, 106379 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(5, Arg1, findGraph(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
    AllGraphCuts ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
