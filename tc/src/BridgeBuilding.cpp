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
#ifdef DEBUG
    #define _debug(args...) { fprintf(stderr, args); fflush(stderr); }
#else
    #define _debug(args...) {}
#endif
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

class BridgeBuilding {
    int cal(VI a, int lim) {
        int ans=0;
        VI p(a.size()+1);
        p[0]=0;
        forn(i, a.size()) p[i+1]=p[i]+a[i];
        int i=0;
        forn(j, p.size()) {
            while(p[j]-p[i]>lim) ++i;
            setmax(ans, p[j]-p[i]);
        }
        return ans;
    }

    int va[220], vb[220];
    int sa[220], sb[220];
    int n;
    int d[220][220], m[220][220], l[220][220], r[220][220];
    void pre(int i, int j) {
        if(i>0 && j<=n) {
            int len1=sa[j]-sa[i];
            int len2=sb[j]-sb[i];
            d[i][j]=min(len1, len2);
            l[i][j]=r[i][j]=0;
            forint(k, i, j) {
                setmax(l[i][j], min(sa[k]-sa[i], len2+sa[j]-sa[k]));
                setmax(l[i][j], min(sb[k]-sb[i], len1+sb[j]-sb[k]));
                setmax(r[i][j], min(sa[j]-sa[k], len2+sa[k]-sa[i]));
                setmax(r[i][j], min(sb[j]-sb[k], len1+sb[k]-sb[i]));
            }
            VI tmp;
            forint(k, i, j-1) tmp.PB(va[k]);
            forintdown(k, j-1, i) tmp.PB(vb[k]);
            VI tmp2=tmp;
            tmp.insert(tmp.end(), all(tmp2));
            m[i][j]=cal(tmp, (len1+len2)/2);
            return;
        }
        if(i==0) {
            r[i][j]=0;
            forint(k, 1, j) {
                setmax(r[i][j], sa[j]-sa[k]);
                setmax(r[i][j], sb[j]-sb[k]);
            }
            VI tmp;
            forint(k, 1, j-1) tmp.PB(va[k]);
            forintdown(k, j-1, 1) tmp.PB(vb[k]);
            m[i][j]=cal(tmp, 1<<30);
            return;
        }
        if(j==n+1) {
            l[i][j]=0;
            forint(k, i, n) {
                setmax(l[i][j], sa[k]-sa[i]);
                setmax(l[i][j], sb[k]-sb[i]);
            }
            VI tmp;
            forintdown(k, n-1, i) tmp.PB(vb[k]);
            forint(k, i, n-1) tmp.PB(va[k]);
            m[i][j]=cal(tmp, 1<<30);
            return;
        }
        assert(false);
    }

    bool ok(int lim, int k) {
        static int f[220][220];
        fillchar(f, 50);
        forint(i, 1, n) {
            if(m[0][i]>lim) continue;
            setmin(f[i][1], r[0][i]);
        }
        forint(i, 1, n) forint(c, 1, k-1) {
            forint(j, i+1, n) {
                if(m[i][j]>lim) continue;
                if(f[i][c]+l[i][j]>lim) continue;
                int val=max(f[i][c]+d[i][j], r[i][j]);
                setmin(f[j][c+1], val);
            }
        }
        forint(i, 1, n) {
            if(m[i][n+1]>lim) continue;
            if(f[i][k]+l[i][n+1]>lim) continue;
            return true;
        }
        return false;
    }
public:
    int minDiameter(vector <int> a, vector <int> b, int K) {
        n=(int)a.size()+1;
        forint(i, 1, n-1) {
            va[i]=a[i-1];
            vb[i]=b[i-1];
        }
        sa[1]=sb[1]=0;
        forint(i, 2, n) {
            sa[i]=sa[i-1]+va[i-1];
            sb[i]=sb[i-1]+vb[i-1];
        }

        forint(i, 1, n) forint(j, i+1, n)
            pre(i, j);
        forint(i, 1, n) {
            pre(0, i);
            pre(i, n+1);
        }

        int le=0, ri=99999;
        while(le<ri) {
            int mid=(le+ri)/2;
            if(ok(mid, K)) ri=mid;
                else le=mid+1;
        }
        return (int)(le);
    }
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {2,1,1,1,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,9,1,9,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 4; int Arg3 = 6; verify_case(0, Arg3, minDiameter(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1,50,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 43; int Arg3 = 42; verify_case(1, Arg3, minDiameter(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {50,10,15,31,20,23,7,48,5,50}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,5,1,8,3,2,16,11,9,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; int Arg3 = 124; verify_case(2, Arg3, minDiameter(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {50,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,50}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 4; int Arg3 = 17; verify_case(3, Arg3, minDiameter(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arr0[] = {2,4,10,2,2,22,30,7,28,14,17,6,32,41,1,3,16,20,40,39,6,4,18,3,3,7,
 3,2,2,14,10,6,38,6,13,3,6,1,23,26,9,17,1,38,1,21,2,12,3,13,28,6,4,
10,3,1,1,43,15,11,18,6,41,1,2,5,6,26,43,9,5,13,1,27,1,33,12,16,1,12,
1,37,34,6,20,3,21,3,1,17,3,10,2,1,8,25,2,6,7,1,7,22,11,8,49,9,1,7,1,
13,17,20,27,31,43,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {5,26,1,2,6,2,16,3,15,1,1,38,2,4,6,1,2,3,11,2,2,2,25,16,2,15,45,3,10,
4,17,5,6,1,16,13,29,3,1,2,4,47,4,10,1,2,23,3,29,20,4,21,1,28,7,25,6,6,
10,1,2,1,17,6,1,28,2,2,12,2,3,42,39,11,18,3,15,4,1,15,3,9,4,26,4,13,41,
1,27,1,14,1,2,14,5,33,1,34,5,17,23,3,33,14,23,2,29,18,3,41,1,45,5,4,6,2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 5; int Arg3 = 1184; verify_case(4, Arg3, minDiameter(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
    BridgeBuilding ___test;
    /*
       ___test.run_test(0);
    /*/
      ___test.run_test(-1);
    //*/
    return 0;
}
// END CUT HERE
