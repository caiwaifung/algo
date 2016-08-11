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

#define sz(a) static_cast<int>(a.size())
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

class Clicounting {
    VI bc;
    int bitcnt(LL s) {
        return bc[s>>20]+bc[s&((1<<20)-1)];
    }
    void pre() {
        bc.resize(1<<20);
        bc[0]=0;
        rep(i, 1, (1<<20)-1) bc[i]=1+bc[i^(i&-i)];
    }

    VL g; int n, ans;
    void dfs(int i, LL s, int cnt) {
        //printf("%d %d %d\n",i,int(s),cnt);
        setmax(ans, cnt);
        if(cnt+bitcnt(s)<=ans) return;
        for(; i<n; ++i) if(s&(1LL<<i)) {
            dfs(i+1, s&g[i], cnt+1);
            s^=1LL<<i;
        }
    }
    int solve(vector<string> t) {
        g.resize(n);
        repn(i, n) {
            g[i]=0; repn(j, n) if(t[i][j]=='1') g[i]|=1LL<<j;
        }
        ans=1; 
        dfs(0, (1LL<<n)-1, 0);
        //printf("ans=%d\n",ans);
        return ans;
    }
public:
    int count(vector<string> p) {
        pre();

        n=sz(p); int m=0;
        repn(i, n) repn(j, i) if(p[i][j]=='?') ++m;
        int r=0;
        repn(s, 1<<m) {
            vector<string> t=p; int cur=0;
            repn(i, n) repn(j, i) if(t[i][j]=='?') {
                if(s&(1<<cur)) t[i][j]='1'; else t[i][j]='0';
                t[j][i]=t[i][j];
                ++cur;
            }
            r+=solve(t);
        }
        return r;
    }
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"011","101","110"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(0, Arg1, count(Arg0)); }
	void test_case_1() { string Arr0[] = {"01?","101","?10"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(1, Arg1, count(Arg0)); }
	void test_case_2() { string Arr0[] = {"0?","?0"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(2, Arg1, count(Arg0)); }
	void test_case_3() { string Arr0[] = {"0??","?0?","??0"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 16; verify_case(3, Arg1, count(Arg0)); }
	void test_case_4() { string Arr0[] = {"0???","?0??","??0?","???0"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 151; verify_case(4, Arg1, count(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
    Clicounting ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
