#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <set>
#include <map>
using namespace std;

#define _ (size_t)
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
typedef pair<LL,LL> PLL;
typedef pair<int,int> PII;
typedef pair<double,double> PDD;
typedef vector<LL> VL;
typedef vector<int> VI;
typedef vector<PII> VPI;
typedef vector<string> VS;
template<class T> void setmax(T &a, T b) { if(b>a) a=b; }
template<class T> void setmin(T &a, T b) { if(b<a) a=b; }
template<class T> T gcd(T a, T b) { return b==0?a:gcd(b,a%b); }

// ------------------------ template ends here ------------------------ //

const int MOD=int(1e9)+7;

class CampLunch {
public:
    int n, m, a[22][22], pos[22][22];
    int count(int N, int M, vector <string> A) {
        n=N, m=M;
        forn(i, n) forn(j, m) {
            a[i][j]=int(A[i][j]-'A');
            pos[i][a[i][j]]=j;
        }

        int f[2][1<<16]; int o1=0, o2=1, full=(1<<m);
        fillchar(f, 0);
        f[o1][0]=1;
        forn(i, n) {
            forn(j, m-1) {
                fillchar(f[o2], 0);
                forn(s, full) {
                    (f[o2][s]+=f[o1][s])%=MOD;
                    int b1=1<<a[i][j], b2=1<<a[i][j+1];
                    if((s&b1)==0 && (s&b2)==0)
                        (f[o2][s^b1^b2] += f[o1][s])%=MOD;
                }
                swap(o1, o2);
            }
            forn(j, m) {
                fillchar(f[o2], 0);
                forn(s, full)
                    if (s&(1<<j)) {
                        (f[o2][s^(1<<j)] +=f[o1][s])%=MOD;
                    } else {
                        (f[o2][s] +=f[o1][s])%=MOD;
                        (f[o2][s^(1<<j)] +=f[o1][s])%=MOD;
                    }
                swap(o1, o2);
            }
        }

        int ans=f[o1][0];
        return int(ans);
    }
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 2; string Arr2[] = {"AB","AB"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 7; verify_case(0, Arg3, count(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 3; string Arr2[] = {"ABC","ABC"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 22; verify_case(1, Arg3, count(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 2; int Arg1 = 3; string Arr2[] = {"ABC","BAC"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 21; verify_case(2, Arg3, count(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 1; int Arg1 = 1; string Arr2[] = {"A"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 1; verify_case(3, Arg3, count(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 1; int Arg1 = 10; string Arr2[] = {"ABDEFHIGJC"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 89; verify_case(4, Arg3, count(Arg0, Arg1, Arg2)); }
	void test_case_5() { int Arg0 = 16; int Arg1 = 16; string Arr2[] = {"ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 950052677; verify_case(5, Arg3, count(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
    CampLunch ___test;
    /*
       ___test.run_test(0);
    /*/
      ___test.run_test(-1);
    //*/
    return 0;
}
// END CUT HERE
