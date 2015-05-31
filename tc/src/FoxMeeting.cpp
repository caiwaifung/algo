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

class FoxMeeting {
    int g[55][55], n;
    int e[55][55], maxval;
    bool hasfox[55];
    VI fox;

    int D;
    bool lab[55];
    int dep[55], fat[55];

    void dfs(int x, int fa, int d) {
        dep[x]=d; fat[x]=fa;
        if(hasfox[x] && d>D) {
            int y=x; while(d-dep[fat[y]]<=D) y=fat[y];
            lab[y]=true;
        }
        forint(y, 1, n) if(e[x][y]<maxval && y!=fa) {
            dfs(y, x, d+e[x][y]);
            if(lab[y]) lab[x]=true;
        }
    }

    bool ok(int _D, int root) {
        D=_D;
        fillchar(lab, false);
        lab[root]=true;
        dfs(root, -1, 0);
        
        int num=0;
        forint(i, 1, n) if(lab[i]) ++num;

        //printf("D=%d root=%d\n",D,root);

        BipartiteGraph<55,55> graph(num, (int)fox.size());
        int x=0;
        forint(i, 1, n) if(lab[i]) {
            //printf("lab %d\n",i);
            ++x;
            forn(j, fox.size()) {
                int y=j+1;
                if(g[i][fox[j]]<=D)// printf("e: %d - %d\n",i,j),
                    graph.addEdge(x, y);
            }
        }
        return graph.match()==num;
    }
    bool ok(int D) {
        forint(i, 1, n) if(ok(D, i)) return true;
        return false;
    }
public:
    int maxDistance(vector <int> A, vector <int> B, vector <int> L, vector <int> foxes) {
        n=(int)A.size()+1;
        fillchar(g, 50); maxval=g[0][0];
        forn(i, n-1) g[A[i]][B[i]]=g[B[i]][A[i]]=L[i];
        memmove(e, g, sizeof(e));
        forint(i, 1, n) g[i][i]=0;
        forint(k, 1, n) forint(i, 1, n) forint(j, 1, n)
            setmin(g[i][j], g[i][k]+g[k][j]);

        fillchar(hasfox, false);
        for(int i: foxes) hasfox[i]=true;
        fox=foxes;

        int le=0, ri=100000*50*2;
        while(le<ri) {
            int mid=(le+ri)/2;
            if(ok(mid)) ri=mid;
            else le=mid+1;
        }
        return le;
    }
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {5}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1, 2}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 0; verify_case(0, Arg4, maxDistance(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arr0[] = {1, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1, 3}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 1; verify_case(1, Arg4, maxDistance(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arr0[] = {1, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1, 2, 3}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 0; verify_case(2, Arg4, maxDistance(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arr0[] = {10,8,3,7,2,6,9,1,4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {5,5,8,10,5,5,6,10,3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {71846,10951,42265,37832,29439,95676,83661,28186,21216}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1,2,3,4,5,6,7,8,9,10}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 0; verify_case(3, Arg4, maxDistance(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arr0[] = {8,15,22,24,2,25,13,26,18,4,9,29,1,12,3,16,14,21,19,27,17,7,20,10,30,11,6,5,23}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {28,28,8,8,28,28,25,2,13,24,24,22,22,29,4,22,8,4,1,24,21,14,18,16,13,21,14,1,25}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {79374,40629,43195,73589,24200,63937,35339,7598,65109,51764,11142,84017,51078,58051,81387,22035,34883,92710,52283,57337,79309,3383,41904,35839,38242,43208,82062,24676,71838}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {3,5,7,9,10,14,17,19,20,21,24,25,28}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 107013; verify_case(4, Arg4, maxDistance(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_5() { int Arr0[] = {34,14,22,9,24,19,11,37,33,21,5,30,1,43,7,31,45,27,6,12,13,35,23,47,49,50,26,40,16,10,48,25,29,15,28,46,4,20,44,17,39,32,38,2,42,8,36,3,41}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {18,18,18,14,9,34,9,24,34,11,18,14,21,21,43,1,22,7,1,30,14,33,13,18,9,5,1,1,26,19,50,33,50,40,29,48,50,37,16,40,48,14,30,22,47,37,7,50,6}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {22051,11109,85275,6691,43705,47374,27748,5411,62549,84079,89542,38006,82198,24083,16847,66335,3542,72495,37378,73973,85703,51682,68688,94295,31337,
90071,99317,63484,43244,99079,55857,34503,79709,82140,91137,27033,91599,61168,52345,49569,58919,38133,43361,
40718,2115,79278,88841,40966,42023}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {5,12,13,18,23,27,28,29,32,33,34,35,36,37,40,42,43,47,48,49,50}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 89342; verify_case(5, Arg4, maxDistance(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
    FoxMeeting ___test;
    /*
       ___test.run_test(0);
    /*/
      ___test.run_test(-1);
    //*/
    return 0;
}
// END CUT HERE
