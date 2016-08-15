#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <memory>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

#define all(a) (a).begin(), (a).end()
#define sz(a) static_cast<int>((a).size())
#define fillchar(a, x) memset(a, x, sizeof(a))
#define rep(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define irep(i, a, b) for(int i=int(a); i>=int(b); --i)
#define replr(i, a, b) rep(i, a, (b)-1)
#define reprl(i, a, b) irep(i, (b)-1, a)
#define repn(i, n) rep(i, 0, (n)-1)
#define irepn(i, n) irep(i, (n)-1, 0)
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
template<class T, class S> ostream& operator<<(ostream& os, const pair<T, S>& v) { return os<<"("<<v.first<<", "<<v.second<<")"; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& v) { os<<"["; repn(i, sz(v)) { if(i) os<<", "; os<<v[i]; } return os<<"]"; }
template<class T> bool setmax(T &_a, T _b) { if(_b>_a) { _a=_b; return true; } return false; }
template<class T> bool setmin(T &_a, T _b) { if(_b<_a) { _a=_b; return true; } return false; }
template<class T> T gcd(T _a, T _b) { return _b==0?_a:gcd(_b,_a%_b); }

int log_[1<<19], bits_[1<<19];

class Clicounting {

    int solve(const VS& g0) {
        const int n=sz(g0);
        if(n==1) return 1;

        const int m=(n+1)/2;
        static int g[2][19][2]; fillchar(g, 0);
        repn(i, n) repn(j, n) if(g0[i][j]=='1') {
            g[i/m][i%m][j/m]^=1<<(j%m);
        }
        static int size[2][1<<19];
        repn(p, 2) {
            size[p][0]=0;
            replr(s, 1, 1<<m) {
                const int b=s&-s, i=log_[b];
                size[p][s]=max(size[p][s^b], 1+size[p][s&g[p][i][p]]);
            }
        }
        static int cover[1<<19];
        cover[0]=(1<<m)-1;
        replr(s, 1, 1<<m) {
            const int b=s&-s, i=log_[b];
            cover[s]=cover[s^b]&g[0][i][1];
        }

        int ans=0;
        repn(s, 1<<m) if(size[0][s]==bits_[s]) {
            setmax(ans, bits_[s]+size[1][cover[s]]);
        }
        return ans;
    }
public:
    int count(vector<string> graph) {
        bits_[0]=0; replr(s, 1, 1<<19) bits_[s]=bits_[s^(s&-s)]+1;
        repn(i, 19) log_[1<<i]=i;

        const int n=sz(graph);
        int num=0;
        repn(i, n) repn(j, i) if(graph[i][j]=='?') ++num;
        int ans=0;
        repn(s, 1<<num) {
            vector<string> g0=graph;
            int cur=0;
            repn(i, n) repn(j, i) if(graph[i][j]=='?') {
                g0[i][j]=g0[j][i]=((s&(1<<cur))?'1':'0');
                ++cur;
            }
            ans+=solve(g0);
        }
        return (int)(ans);
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
