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

const int N=1010;

double pr[N], p[N], s[N];
double f[N], fp[N];
int n;

class AToughGame {
public:
    int ran() {
        double r=rand()%10000/10000.;
        rep(i, 0, n) {
            if(r<=p[i]) return i;
            r-=p[i];
        }
        assert(false);
        return n;
    }
    double e0() {
        double ans=0; int cnt=99999;
        repn(t, cnt) {
            double cur=0; int la=0;
            while(la!=n) {
                int i=ran();
                if(i<la) cur=0;
                la=i, cur+=s[i];
            }
            ans+=cur;
        }
        return ans/cnt;
    }
    double e1() {
        double tmp[N]; memcpy(tmp, p, sizeof(p));
        double ans=0; int cnt=999999;
        repn(t, cnt) {
            double cur=0; int la=0;
            //printf("start\n");
            while(la!=n) {
                //rep(k, 0, n) printf("p[%d]=%.5lf\n",k,p[k]);
                int i=ran();
                //printf("i=%d\n", i);
                la=i, cur+=s[i];
                double rest=accumulate(p+i, p+n+1, 0.);
                rep(k, 0, i-1) p[k]=0;
                rep(k, i, n) p[k]/=rest;
            }
            ans+=cur;
            memcpy(p, tmp, sizeof(p));
            if(t%99999==0) printf("   %.9lf\n",ans/(t+1));
        }
        return ans/cnt;
    }
    double expectedGain(vector <int> prob, vector <int> value) {
        n=(int)prob.size();
        {
            rep(i, 1, n) pr[i]=(double)prob[i-1]/1000.;
            double p0=1;
            rep(i, 1, n) {
                p[i-1]=(1-pr[i])*p0;
                p0*=pr[i];
            }
            p[n]=p0;
            s[0]=0;
            rep(i, 1, n) s[i]=s[i-1]+(double)value[i-1];
        }

        fillchar(f, 0);
        rep(i, 1, n) {
            rep(j, 0, i-1) f[i]+=p[j]*f[j];
            f[i]+=s[i];
            if(i<n) f[i]/=1-p[i];
        }
        double ans=f[n];

        return (double)(ans);
    }
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1000,500}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3,4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 10.0; verify_case(0, Arg2, expectedGain(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {1000,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3,4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 3003.9999999999977; verify_case(1, Arg2, expectedGain(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {500,500,500,500,500}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,2,3,4,5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 16.626830517153095; verify_case(2, Arg2, expectedGain(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {250,750}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1000,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 1067.6666666666667; verify_case(3, Arg2, expectedGain(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {916,932,927,988,958,996,944,968,917,939,960,965,960,998,920,990,915,972,995,916,902,
968,970,962,922,959,994,915,996,996,994,986,945,947,912,946,972,951,973,965,921,910,
938,975,942,950,900,983,960,998,982,980,902,974,952,938,900,962,920,931,964,974,953,
995,946,946,903,921,923,985,919,996,930,915,991,967,996,911,999,936,1000,962,970,929,
966,960,930,920,958,926,983}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {583,428,396,17,163,815,31,536,175,165,532,781,29,963,331,987,599,497,380,180,780,25,
931,607,784,613,468,140,488,604,401,912,204,785,697,173,451,849,714,914,650,652,338,
336,177,147,22,652,901,548,370,9,118,487,779,567,818,440,10,868,316,666,690,714,623,
269,501,649,324,773,173,54,391,745,504,578,81,627,319,301,16,899,658,586,604,83,520,
81,181,943,157}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 54204.93356505282; verify_case(4, Arg2, expectedGain(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
    AToughGame ___test;
    /*
       ___test.run_test(2);
    /*/
      ___test.run_test(-1);
    //*/
    return 0;
}
// END CUT HERE
