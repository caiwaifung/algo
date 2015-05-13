#include <algorithm>
#include <cassert>
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

template<size_t N, size_t M> class BipartiteGraph {
    bool g[N][M], vis[M]; int n, m;
    bool find(int x) {
        for(int y=1; y<=m; ++y)
            if(g[x][y] && !vis[y]) {
                vis[y]=true;
                if(ly[y]==0 || find(ly[y])) {
                    ly[y]=x; lx[x]=y;
                    return true;
                }
            }
        return false;
    }
    void dfs(int x) {
        for(int y=1; y<=m; ++y)
            if(g[x][y] && !vcy[y]) {
                int x0=ly[y]; assert(x0>0 && vcx[x0]);
                vcx[x0]=false; vcy[y]=true;
                dfs(x0);
            }
    }
public:
    int lx[N], ly[M];
    bool vcx[N], vcy[M];
    BipartiteGraph(int n, int m) : n(n), m(m) {
        assert(n<(int)N && m<(int)M);
        memset(g, false, sizeof(g));
    }
    void addEdge(int i, int j) { g[i][j]=true; }
    void delEdge(int i, int j) { g[i][j]=false; }
    int match() {
        memset(lx, 0, sizeof(lx));
        memset(ly, 0, sizeof(ly));
        int ans=0;
        for(int i=1; i<=n; ++i) {
            memset(vis, false, sizeof(vis));
            if(find(i)) ans++;
        }
        return ans;
    }
    void vc() { // compute vertex cover
        memset(vcx, false, sizeof(vcx));
        memset(vcy, false, sizeof(vcy));
        for(int i=1; i<=n; ++i) if(lx[i]) vcx[i]=true;
        for(int i=1; i<=n; ++i) if(lx[i]==0) dfs(i);
    }
};

// ------------------------ template ends here ------------------------ //

class DancingForever {
public:
    vector<int> getStablePairs(string x) {
        int n=0; while(n*n<(int)x.size()) ++n;
        BipartiteGraph<111,111> *g = new BipartiteGraph<111,111>(n, n);
        forn(i, n) forn(j, n) if(x[_ (i*n+j)]=='Y') g->addEdge(i+1, j+1);
        if(g->match()<n) {
            g->vc();
            forn(i, n) forn(j, n) if(g->vcx[i+1] || !g->vcy[j+1]) g->delEdge(i+1, j+1);
            g->match();
        }
        VI ans;
        forn(i, n) if(g->lx[i+1]>0) {ans.PB(i); ans.PB(g->lx[i+1]-1);}
        delete g;
        return ans;
    }
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arg0 = "YYNNNYYNNNYYYNNY"; int Arr1[] = {0, 0, 1, 1, 2, 2, 3, 3 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, getStablePairs(Arg0)); }
	void test_case_1() { string Arg0 = "YNNNYYNNYYNNNNYY"; int Arr1[] = {1, 0, 2, 1 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, getStablePairs(Arg0)); }
	void test_case_2() { string Arg0 = "YNYYNYYNY"; int Arr1[] = {1, 0, 2, 2 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, getStablePairs(Arg0)); }
	void test_case_3() { string Arg0 = "YYYNNYYYNNNNNYYNNNYYNNNYY"; int Arr1[] = {3, 3, 4, 4 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, getStablePairs(Arg0)); }
	void test_case_4() { string Arg0 = "Y"; int Arr1[] = {0, 0 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(4, Arg1, getStablePairs(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
    DancingForever ___test;
    /*
       ___test.run_test(0);
    /*/
      ___test.run_test(-1);
    //*/
    return 0;
}
// END CUT HERE
