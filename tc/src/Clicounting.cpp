#include <algorithm>
#include <numeric>
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

class Clicounting {
public:
    int count(vector<string> g) {
        const int n=sz(g);
        vector<VI> id(n, VI(n));
        int m=0; repn(i, n) replr(j, i+1, n) if(g[i][j]=='?') id[i][j]=id[j][i]=m++;
        VI log(1<<20), cnt(1<<20);
        repn(i, 20) log[1<<i]=i;
        cnt[0]=0; replr(i, 1, 1<<20) cnt[i]=cnt[i&(i-1)]+1;

        vector<bool> left(n, false);
        repn(i, n) repn(j, n) if(g[i][j]=='?') left[i]=left[j]=true;
        while(accumulate(all(left), 0)<n/2) *find(all(left), false)=true;
        VI a, b;
        repn(i, n) (left[i]?a:b).pb(i);

        VI f(1<<sz(b));
        f[0]=0;
        replr(s, 1, 1<<sz(b)) {
            const int i=log[s&-s];
            int t=0; repn(j, sz(b)) if(s&(1<<j) && g[b[i]][b[j]]=='1') t|=1<<j;
            f[s]=max(f[s^(1<<i)], 1+f[t]);
        }

        VI needs(1<<sz(a));
        needs[0]=0;
        replr(s, 1, 1<<sz(a)) {
            const int i=log[s&-s];
            bool ok=true; int more=0;
            repn(j, sz(a)) if(j!=i && s&(1<<j)) {
                if(g[a[i]][a[j]]=='0') ok=false;
                if(g[a[i]][a[j]]=='?') more|=1<<id[a[i]][a[j]];
            }
            if(ok && needs[s&s-1]>=0) {
                needs[s]=needs[s&s-1]|more;
            } else {
                needs[s]=-1;
            }
        }

        VI gr(1<<sz(a));
        gr[0]=(1<<sz(b))-1;
        replr(s, 1, 1<<sz(a)) {
            const int i=log[s&-s];
            gr[s]=0;
            repn(j, sz(b)) if(gr[s&s-1]&(1<<j) && g[a[i]][b[j]]=='1') gr[s]|=1<<j;
        }
        VI best(1<<m);
        repn(s, 1<<sz(a)) if(needs[s]>=0) {
            setmax(best[needs[s]], cnt[s]+f[gr[s]]);
        }
        int ans=0;
        repn(s, 1<<m) {
            ans+=best[s];
            repn(i, m) if((s&(1<<i))==0) setmax(best[s|(1<<i)], best[s]);
        }
        return ans;
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
