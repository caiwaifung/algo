// 14:27 - 15:15 - wa sample
#include <algorithm>
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

// ------------------------ template ends here ------------------------ //

const int MAXN=2020;

class Cycle {
    VPI tr[MAXN*2];
    int X;

    void init() {
        forn(i, MAXN*2) {
            tr[i].clear();
            tr[i].PB(MP(-1, 1<<28));
        }
    }
    void add(int i, int x, int y) { // i in [-N,N]
        i+=2001;
        for(; i<MAXN*2; i+=i&-i)
            if(tr[i].back().se>y)
                tr[i].PB(MP(x,y));
    }
    void del(int i, int x) {
        i+=2001;
        for(; i<MAXN*2; i+=i&-i)
            if(tr[i].back().fi==x)
                tr[i].pop_back();
    }
    int get(int i) {
        i+=2001;
        i=min(MAXN*2-1, max(i,0));
        int ans=1<<28;
        for(; i>=1; i-=i&-i)
            setmin(ans, tr[i].back().se);
        return ans;
    }

    int a[MAXN], lim[MAXN];
    int b[MAXN], mxb[MAXN];
    int i;

public:
    Cycle(int X) : X(X) {
        init();
        i=0;
        lim[0]=1<<28, mxb[0]=-1;
    }
    void push(int ca, int cb) {
        ++i;
        b[i]=cb, mxb[i]=max(mxb[i-1], cb);
        a[i]=ca;

        int tmp=get(a[i]+i-X-1);
        lim[i]=min(lim[i-1], tmp-a[i]+i);

        add(i-a[i], i, X-a[i]-i+1);
    }
    void pop() {
        del(i-a[i], i);
        --i;
    }
    bool ok() {
        /*
        forint(k, 1, i) if(b[k]>X) return false;
        forint(x, 1, i) forint(y, x+1, i) if(a[x]+a[y]+y-x>X && a[x]+a[y]+i-1-(y-x)>X) return false;
        return true;
        */
        return i<=lim[i] && mxb[i]<=X;
    }
};

class PublicTransitHard {
    VI g[MAXN];
    Cycle *c;
    int ans, root;

    int len[MAXN], diameter[MAXN];

    void prepare(int x, int fa) {
        len[x]=diameter[x]=0;
        for(int y: g[x]) if(y!=fa) {
            prepare(y, x);
            setmax(diameter[x], diameter[y]);
            setmax(diameter[x], len[x]+1+len[y]);
            setmax(len[x], len[y]+1);
        }
    }
    void trim(VI &v, int n) {
        sort(all(v), greater<int>());
        v.resize(n, -1000);
    }
    void dfs(int x, int fa) {
        if(x<=root) {
            c->push(len[x], diameter[x]);
            if(c->ok()) ++ans;
            c->pop();
        }

        VI ls, ds;
        for(int y: g[x]) if(y!=fa) {
            ls.PB(len[y]), ds.PB(diameter[y]);
        }
        trim(ls, 3);
        trim(ds, 2);
        for(int y: g[x]) if(y!=fa) {
            int li=0, lj=1, di=0;
            if(ls[li]==len[y]) ++li, ++lj;
            else if(ls[lj]==len[y]) ++lj;
            if(ds[di]==diameter[y]) ++di;

            int cl=max(0, ls[li]+1);
            int cd=max(0, max(ds[di], ls[li]+ls[lj]+2));
            c->push(cl, cd);
            dfs(y, x);
            c->pop();
        }
    }
public:
    int countValidTeleporters(int n, vector <int> edges, int X) {
        forint(i, 1, n) g[i].clear();
        forn(i, edges.size()) {
            int a=i+2, b=edges[i]+1;
            g[a].PB(b), g[b].PB(a);
        }

        ans=0;
        c=new Cycle(X);
        forint(i, 1, n) {
            root=i;
            prepare(i, 0);
            dfs(i, 0);
        }
        
        return int(ans);
    }
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 4; int Arr1[] = {0, 1, 2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; int Arg3 = 1; verify_case(0, Arg3, countValidTeleporters(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 3; int Arr1[] = {0, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; int Arg3 = 6; verify_case(1, Arg3, countValidTeleporters(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 6; int Arr1[] = {0, 0, 0, 1, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; int Arg3 = 1; verify_case(2, Arg3, countValidTeleporters(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 7; int Arr1[] = {0, 1, 0, 1, 2, 4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; int Arg3 = 0; verify_case(3, Arg3, countValidTeleporters(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 16; int Arr1[] = {0, 1, 0, 2, 0, 0, 4, 5, 8, 9, 10, 11, 8, 4, 6}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 7; int Arg3 = 31; verify_case(4, Arg3, countValidTeleporters(Arg0, Arg1, Arg2)); }
	void test_case_5() { int Arg0 = 56; int Arr1[] = {0, 1, 1, 3, 1, 5, 1, 0, 8, 8, 10, 10, 12, 10, 10, 8, 16, 16, 18, 19, 19, 21, 19, 19, 24, 25, 25, 27, 18, 0, 30, 30, 30, 33, 34, 34, 34, 30, 38, 39, 39, 38, 42, 43, 0, 45, 45, 45, 48, 45, 45, 51, 45, 53, 54}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 12; int Arg3 = 610; verify_case(5, Arg3, countValidTeleporters(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
    PublicTransitHard ___test;
    /*
       ___test.run_test(5);
    /*/
      ___test.run_test(-1);
    //*/
    return 0;
}
// END CUT HERE
