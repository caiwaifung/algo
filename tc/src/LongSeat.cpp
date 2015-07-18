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

struct State {
    VI ei, ej; VPI ek;
    VI p;
};
int L;

PII d[10];

bool check(State s) {
    fillchar(d, 50);
    d[9]=mp(L, 1);
    d[8]=mp(0, 1);

    bool updated=false;
    repn(times, 13) {
        updated=false;
        repn(i, s.ei.size()) {
            int x=s.ei[i], y=s.ej[i], v=s.ek[i].fi, v2=s.ek[i].se;
            PII tmp=d[y];
            tmp.fi+=v; if(v2) tmp.se=0;
            if(setmin(d[x], tmp)) updated=true;
        }
    }
    if(updated) return false;
    return d[8]==mp(0, 1) && d[9]==mp(L, 1);
}

class LongSeat {
public:
    vector <string> canSit(int _L, vector <int> width) {
        L=_L;

        State init;
        init.p.pb(8); init.p.pb(9);
        vector<State> cur;
        cur.pb(init);

        int wn=(int)width.size();
        width.resize(10); width[8]=0; width[9]=0;

        vector<string> ans;
        repn(wi, wn) {
            bool can_sit=false, can_stand=false;
            vector<State> tmp;
            for(const State &s: cur) {
                State t0=s;
                repn(i, s.p.size()-1) {
                    State t=s;
                    t.p.insert(t.p.begin()+i+1, wi);
                    t.ei.pb(s.p[i]); t.ej.pb(wi); t.ek.pb(mp(-width[s.p[i]], 0));
                    t.ei.pb(wi); t.ej.pb(s.p[i+1]); t.ek.pb(mp(-width[wi], 0));
                    if(check(t)) {
                        tmp.pb(t); can_sit=true;
                    }
                    t0.ei.pb(s.p[i+1]); t0.ej.pb(s.p[i]); 
                    t0.ek.pb(mp(width[wi]+width[s.p[i]], 1));
                }
                if(check(t0)) {
                    tmp.pb(t0); can_stand=true;
                }
            }
            cur=tmp;
            if(can_sit && can_stand) ans.pb("Unsure");
            else if(can_sit) ans.pb("Sit");
            else if(can_stand) ans.pb("Stand");
            else assert(false);
        }

        return ans;
    }
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arg0 = 2; int Arr1[] = {1, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"Sit", "Unsure" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, canSit(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 10; int Arr1[] = {100, 2, 4, 2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"Stand", "Sit", "Sit", "Unsure" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(1, Arg2, canSit(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 37; int Arr1[] = {3, 7, 5, 6, 4, 4, 1, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"Sit", "Sit", "Sit", "Unsure", "Unsure", "Unsure", "Sit", "Unsure" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(2, Arg2, canSit(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 400; int Arr1[] = {92, 65, 99, 46, 24, 85, 95, 84}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"Sit", "Sit", "Unsure", "Unsure", "Unsure", "Unsure", "Stand", "Unsure" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(3, Arg2, canSit(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 1000000000; int Arr1[] = {1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"Sit", "Stand", "Stand", "Stand", "Stand", "Stand", "Stand", "Stand" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(4, Arg2, canSit(Arg0, Arg1)); }
	void test_case_5() { int Arg0 = 1; int Arr1[] = {1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"Stand", "Stand", "Stand", "Stand", "Stand", "Stand", "Stand", "Stand" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(5, Arg2, canSit(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
    LongSeat ___test;
    /*
       ___test.run_test(0);
    /*/
      ___test.run_test(-1);
    //*/
    return 0;
}
// END CUT HERE
