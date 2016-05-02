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

class ThreeProgrammers {
public:
    string validCodeHistory(string code) {
        int c[3]; fillchar(c, 0);
        for(char x: code) c[int(x-'A')]++;

        static int f[55][55][55][3][3];
        fillchar(f, 0xff);
        repn(p, 3) repn(q, 3) f[0][0][0][p][q]=0;
        rep(i, 0, c[0]) rep(j, 0, c[1]) rep(k, 0, c[2]) repn(p, 3) repn(q, 3) {
            if(f[i][j][k][p][q]<0) continue;
            f[i+1][j][k][q][0]=p;
            if(q!=1) f[i][j+1][k][q][1]=p;
            if(q!=2 && p!=2) f[i][j][k+1][q][2]=p;
        }
        int i=c[0], j=c[1], k=c[2], p=0, q=0;
        repn(p0, 3) repn(q0, 3) if(f[i][j][k][p0][q0]>=0) { p=p0, q=q0; break; }
        if(f[i][j][k][p][q]<0) return "impossible";

        string ans(i+j+k, 'a');
        while(i>0 || j>0 || k>0) {
            int z=f[i][j][k][p][q];
            //printf("%d %d %d\n",i,j,k);
            if(q==0) --i, ans[i+j+k]='A';
            if(q==1) --j, ans[i+j+k]='B';
            if(q==2) --k, ans[i+j+k]='C';
            q=p, p=z;
        }
        return ans;
    }
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); if ((Case == -1) || (Case == 7)) test_case_7(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "CAB"; string Arg1 = "BCA"; verify_case(0, Arg1, validCodeHistory(Arg0)); }
	void test_case_1() { string Arg0 = "CBB"; string Arg1 = "BCB"; verify_case(1, Arg1, validCodeHistory(Arg0)); }
	void test_case_2() { string Arg0 = "BB"; string Arg1 = "impossible"; verify_case(2, Arg1, validCodeHistory(Arg0)); }
	void test_case_3() { string Arg0 = "BBA"; string Arg1 = "BAB"; verify_case(3, Arg1, validCodeHistory(Arg0)); }
	void test_case_4() { string Arg0 = "CAC"; string Arg1 = "impossible"; verify_case(4, Arg1, validCodeHistory(Arg0)); }
	void test_case_5() { string Arg0 = "ACAC"; string Arg1 = "CAAC"; verify_case(5, Arg1, validCodeHistory(Arg0)); }
	void test_case_6() { string Arg0 = "ACABC"; string Arg1 = "ACABC"; verify_case(6, Arg1, validCodeHistory(Arg0)); }
	void test_case_7() { string Arg0 = "BAABCABBCCACBAACABAABABBCCAACABCCAACCABCACACCBABAB"; string Arg1 = "BACBABCAACBACABCBACBACABCBACBACABCABCAACBACAACABCA"; verify_case(7, Arg1, validCodeHistory(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
    ThreeProgrammers ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
