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

class Coversta {
public:
    int a[110][110], f[110][110];
    int n, m;
    VI dx, dy;
    bool inside(int x, int y) {
        return (x)>=1 && (x)<=n && (y)>=1 && (y)<=m;
    }
    bool vis[110][110], lab[110][110];
    int go1(int x, int y) {
        int ans=0;
        forn(k, dx.size()) {
            int i=x+dx[k], j=y+dy[k];
            if(inside(i,j) && !vis[i][j]) {
                vis[i][j]=true;
                ans+=a[i][j];
            }
        }
        return ans;
    }
    void go2(int x, int y) {
        forn(k, dx.size()) {
            int i=x+dx[k], j=y+dy[k];
            if(inside(i,j))
                vis[i][j]=false;
        }
    }
    int go(int x1, int y1, int x2, int y2) {
        int ans=go1(x1, y1)+go1(x2, y2);
        go2(x1, y1);
        go2(x2, y2);
        return ans;
    }
    int place(vector <string> _a, vector <int> _dx, vector <int> _dy) {
        n=(int)_a.size(), m=(int)_a[0].size();
        dx=_dx, dy=_dy;
        forint(i, 1, n) forint(j, 1, m) a[i][j]=int(_a[i-1][j-1]-'0');

        forint(i, 1, n) forint(j, 1, m) {
            f[i][j]=0;
            forn(k, dx.size()) {
                int x=i+dx[k], y=j+dy[k];
                if(inside(x,y)) f[i][j]+=a[x][y];
            }
                //printf("i=%d j=%d f=%d\n",i,j,f[i][j]);
        }

        multiset<int> all;
        forint(i, 1, n) forint(j, 1, m) {
            all.insert(-f[i][j]);
        }
        fillchar(lab, false);
        fillchar(vis, false);
        int ans=0;
        forint(i, 1, n) forint(j, 1, m) {
            VPI tmp;
            forn(k, dx.size()) forn(k2, dx.size()) {
                int i2=i+dx[k]-dx[k2];
                int j2=j+dy[k]-dy[k2];
                if(inside(i2, j2) && !lab[i2][j2]) {
                    tmp.PB(MP(i2, j2));
                    all.erase(all.find(-f[i2][j2]));
                    lab[i2][j2]=true;
                    setmax(ans, go(i,j,i2,j2));
                }
            }

            if(all.size()>0) {
                //printf("i=%d j=%d all=%d\n",i,j,(int)all.size());
                setmax(ans,f[i][j]-*all.begin());
            }
            

            for(auto t: tmp) {
                all.insert(-f[t.fi][t.se]);
                lab[t.fi][t.se]=false;
            }
        }
        return int(ans);
    }
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"11",
 "11"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0,1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 4; verify_case(0, Arg3, place(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arr0[] = {"11",
 "11"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0,1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 3; verify_case(1, Arg3, place(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arr0[] = {"15",
 "61"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 11; verify_case(2, Arg3, place(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arr0[] = {"151",
 "655",
 "661"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0,-1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0,1,0}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 33; verify_case(3, Arg3, place(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arr0[] = {"303",
 "333",
 "000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-1,-1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {-1,1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 12; verify_case(4, Arg3, place(Arg0, Arg1, Arg2)); }
	void test_case_5() { string Arr0[] = {"0000000",
 "1010101"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-1,-1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {-1,1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 0; verify_case(5, Arg3, place(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
    Coversta ___test;
    /*
       ___test.run_test(0);
    /*/
      ___test.run_test(-1);
    //*/
    return 0;
}
// END CUT HERE
