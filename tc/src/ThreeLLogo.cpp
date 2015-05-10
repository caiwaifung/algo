// 16:20 - 16:35 - fail sample
// - 16:38 - pass sample - pass
#include <cctype>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
using namespace std;

#define forint(i, a, b) for(int i=(int)(a); i<=(int)(b); ++i)
#define forintdown(i, a, b) for(int i=(int)(a); i>=(int)(b); --i)
#define forn(i, n) forint(i, 0, (n)-1)
#define forndown(i, n) forintdown(i, (n)-1, 0)
#define fillchar(a, x) memset(a, x, sizeof(a))
typedef long long LL;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef vector<LL> VL;
typedef vector<PII> VPI;
#define MP make_pair
#define PB push_back
#define fi first
#define se second

class ThreeLLogo
{
public:
	int bit(int s, int i) {
		return (s>>i)&1;
	}
	long long countWays(vector <string> grid) {
		map<PII, LL> f[2];
		int o1=0, o2=1;

		f[o1].clear();
		f[o1][MP(0,0)]=1;
		forn(i, grid.size()) {
			forn(j, grid[i].size()) {
				//printf("i=%d j=%d\n",i,j);
				f[o2].clear();
				for(map<PII,LL>::iterator it=f[o1].begin(); it!=f[o1].end(); ++it) {
					int s=it->fi.fi;
					int c=it->fi.se;
					LL val=it->se;
					int a=bit(s, j);
					int b=bit(s, j+1);
					s^=(a<<j)|(b<<(j+1));

					if(a==0 && b==0)
						f[o2][MP(s,c)]+=val;
					if(grid[i][j]=='.') {
						if(a==1 && b==0)
							f[o2][MP(s,c)]+=val;
						if(a==0 && b==0 && c<3) {
							int s2=s|(1<<j);
							f[o2][MP(s2,c+1)]+=val;
						}
						if(a==0 && b==1) {
							int s2=s|(1<<j);
							f[o2][MP(s2,c)]+=val;
						}
						if(a==1 && b==0) {
							int s2=s|(1<<(j+1));
							f[o2][MP(s2,c)]+=val;
						}
						if(a==0 && b==1) {
							int s2=s|(1<<(j+1));
							f[o2][MP(s2,c)]+=val;
						}
					}
				}
				swap(o1, o2);
			}
			f[o2].clear();
			for(map<PII,LL>::iterator it=f[o1].begin(); it!=f[o1].end(); ++it) {
				int s=it->fi.fi;
				int c=it->fi.se;
				LL val=it->se;
				//printf("i=%d s=%d c=%d val=%I64d\n",i,s,c,val);
				if((s&(1<<grid[i].size()))==0)
					f[o2][MP(s<<1,c)]+=val;
			}
			swap(o1, o2);
		}
		return f[o1][MP(0,3)];
	}

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); if ((Case == -1) || (Case == 7)) test_case_7(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"......",
 "......"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 1LL; verify_case(0, Arg1, countWays(Arg0)); }
	void test_case_1() { string Arr0[] = {".##..",
 ".....",
 ".#.#.",
 "#...#"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 3LL; verify_case(1, Arg1, countWays(Arg0)); }
	void test_case_2() { string Arr0[] = {"....",
 "#...",
 "....",
 "..#."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 4LL; verify_case(2, Arg1, countWays(Arg0)); }
	void test_case_3() { string Arr0[] = {"..",
 ".."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 0LL; verify_case(3, Arg1, countWays(Arg0)); }
	void test_case_4() { string Arr0[] = {".#.#",
 "....",
 ".#.#",
 "...."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 12LL; verify_case(4, Arg1, countWays(Arg0)); }
	void test_case_5() { string Arr0[] = {"######.#######",
 "######.#######",
 "#.####.#######",
 "#.####.#######",
 "#.####........",
 "#.############",
 "#.############",
 "#.############",
 "#.#####.######",
 "#.#####.######",
 "#.#####.######",
 "#....##.######",
 "#######.######",
 "#######.######",
 "#######.######",
 "#######.######",
 "#######.######",
 "#######.######",
 "#######......#",
 "##############"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 37800LL; verify_case(5, Arg1, countWays(Arg0)); }
	void test_case_6() { string Arr0[] = {"#......",
 ".#....#",
 ".#.#...",
 "#....#.",
 ".##..#.",
 ".#.....",
 ".....#.",
 ".#.#...",
 ".#...#.",
 "..##..."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 27750LL; verify_case(6, Arg1, countWays(Arg0)); }
	void test_case_7() { string Arr0[] = {"...#..........................",
 "............#..#........#.....",
 ".#............................",
 "...#..........#...#..##.......",
 ".........#....#...#...#.....#.",
 "#...#......#...........#..#...",
 "#...##..#..#..#.....#.........",
 ".............##...............",
 ".....#..#..#..#...............",
 "......#................#......",
 "...#....#.........#.....#...#.",
 ".........#....................",
 ".........#.........##......#..",
 ".#.#..#.....#.#....#.#........",
 "....#.........#...#...........",
 "..##.....#.............#......",
 ".#............................",
 "......................#.......",
 "......#..............#.......#",
 "##..#.........#........#.....#",
 "......#.......#.....#.........",
 ".....#...#...#.#............#.",
 "......#..##....#..............",
 "....#....................#....",
 ".#..........................#.",
 ".............#..........#.....",
 ".#.........#..................",
 "................#.........##..",
 ".......................#.....#",
 ".............#...............#"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 2178497179123LL; verify_case(7, Arg1, countWays(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
	ThreeLLogo ___test;
	___test.run_test(-1);
	//___test.run_test(0);
	return 0;
}
// END CUT HERE
