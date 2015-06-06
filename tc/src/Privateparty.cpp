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
    int n, a[55];
    double f[55]; bool bf[55];

    void go_circle(int x) {
        int p[55], s[55]; fillchar(p, 0);
        int len=0;
        for(int cur=1; ; ++cur) {
            if(p[x]>0) {
                len=0;
                forint(i, p[x], cur-1)
                    p[++len]=s[i];
                break;
            }
            p[x]=cur; s[cur]=x;
            if(a[x]==x) return;
            x=a[x];
        }

        forint(i, 1, len) {
            assert(bf[p[i]]==false);
            bf[p[i]]=true;
            f[p[i]]=0.0;
        }
        forint(k, 1, len) {
            double cur=1.; bool o=true;
            f[p[k]]+=cur/len;
            for(int i=k%len+1; i!=k; i=i%len+1) {
                if(o) { cur=0; o=false; }
                else cur=.5+.5*(1-cur);
                f[p[i]]=cur;
            }
        }
    }

    double cal_f(int i) {
        double &ans=f[i];
        if(bf[i]) return ans;

        go_circle(i);
        if(bf[i]) return ans;

        if(a[i]==i) ans=1;
        else ans=(1-cal_f(a[i]))*.5+.5;
        return ans;
    }

    double getexp(vector <int> _a) {
        n=(int)_a.size();
        forint(i, 1, n) a[i]=_a[i-1]+1;

        fillchar(bf, false);
        double ans=0;
        forint(i, 1, n) ans+=cal_f(i);

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


    Privateparty ___test;
    /*
       ___test.run_test(0);
    /*/
      ___test.run_test(-1);
    //*/
    return 0;
}
// END CUT HERE
