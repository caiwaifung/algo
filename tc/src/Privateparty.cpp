#include <algorithm>
#include <iostream>
#include <sstream>
#include <cassert>
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

class Privateparty {
public:
    double f[55][55], g[55];
    int n, a[55];

    double getexp(vector <int> _a) {
        n=(int)_a.size();
        forint(i, 1, n) a[i]=_a[i-1]+1;

        f[1][1]=1; g[1]=1;
        forint(i, 2, n) {
            g[i]=0;
            forint(j, 1, i) {
                f[i][j]=1;
                forint(k, 1, j-1)
                    f[i][j]-=f[i-1][k];
                f[i][j]/=i;
                g[i]+=f[i][j];
            }
        }

        double ans=0;
        forint(i, 1, n) {
            int vis[55]; fillchar(vis, 0);
            int len=0, y=0;
            for(int cur=i, id=1; ; ++id) {
                if(vis[cur]>0) {
                    y=vis[cur];
                    len=id-1;
                    break;
                }
                vis[cur]=id, cur=a[cur];
            }
            printf("%d %d\n",y,len);
            double v[55];
            v[1]=1; v[2]=0; forint(k, 3, len) v[k]=g[k-2];

            double s=0;
            forint(k, 1, len) s+=v[k];
            s/=len;
            ans+=s;
        }

        return double(ans);
    }
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 2.0; verify_case(0, Arg1, getexp(Arg0)); }
	void test_case_1() { int Arr0[] = {0,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 1.5; verify_case(1, Arg1, getexp(Arg0)); }
	void test_case_2() { int Arr0[] = {0,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 2.5; verify_case(2, Arg1, getexp(Arg0)); }
	void test_case_3() { int Arr0[] = {0,1,1,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 3.166666666666667; verify_case(3, Arg1, getexp(Arg0)); }
	void test_case_4() { int Arr0[] = {3,2,1,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 2.0; verify_case(4, Arg1, getexp(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
    /*
    int p[99]; const int n=4;
    forint(i, 1, n) p[i]=i;
    int ans[99]; fillchar(ans, 0);
    int c=0;
    do {
        ++c;
        int v[99]; fillchar(v, 0);
        forint(i, 1, n) if(v[p[i]-1]==0) v[p[i]]=1;
        forint(i, 1, n) if(v[i]) ++ans[i];
    } while(next_permutation(p+1, p+n+1));
    forint(i, 1, n) {
        int a=ans[i], b=c, g=gcd(a,b);
        a/=g, b/=g;
        printf("%d: %d/%d\n",i,a,b);
    }
    return 0;

    */

    Privateparty ___test;
    /*
       ___test.run_test(0);
    /*/
      ___test.run_test(-1);
    //*/
    return 0;
}
// END CUT HERE
