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

const int dx[4]={0, 1, 0, -1};
const int dy[4]={1, 0, -1, 0};

class Balance {
    VS str;
    int n, m;
    bool inside(int x, int y) { return x>=0 && x<n && y>=0 && y<m; }

    bool vis[55][55];
    int bid[55][55];
    VPI blocks[2555];
    int num;

    bool touched[2555];
    int fa[2555], l[2555], r[2555];

    void find_fa(VPI start, int id, char ch) {
        queue<PII> que;
        VI sons;
        for(PII cur: start) repn(k, 4) {
            int x=cur.fi+dx[k], y=cur.se+dy[k];
            if(!inside(x, y) || vis[x][y]) continue;
            if(str[x][y]==ch) {
                que.push(mp(x, y));
                vis[x][y]=true;
            }
        }

        while(!que.empty()) {
            PII cur=que.front(); que.pop();
            repn(k, 4) {
                int x=cur.fi+dx[k], y=cur.se+dy[k];
                if(!inside(x, y) || vis[x][y]) continue;
                if(str[x][y]!=ch) {
                    if(!touched[bid[x][y]]) {
                        touched[bid[x][y]]=true;
                        sons.pb(bid[x][y]);
                    }
                }
                else {
                    que.push(mp(x, y));
                    vis[x][y]=true;
                }
            }
        }
        for(int son: sons) {
            //printf("son %d: %d\n", id,son);
            fa[son]=id;
            r[son]=l[id], l[id]=son;
            find_fa(blocks[son], son, ch=='#'?'.':'#');
        }
    }

    string make(int x) {
        VS a;
        for(int y=l[x]; y>=0; y=r[y])
            a.pb(make(y));
        sort(all(a));
        string ans="";
        for(string s: a) ans+=s;
        ans="("+ans+")";
        return ans;
    }

    string go(VS _s) {
        str=_s; 
        str.insert(str.begin(), string(str[0].size(), '#'));
        str.insert(str.end(), string(str[0].size(), '#'));
        for(string &s: str) s="#"+s+"#";
        n=(int)str.size(), m=(int)str[0].size();

        fillchar(vis, false);
        num=0;
        repn(i, n) repn(j, m)
            if(!vis[i][j]) {
                queue<PII> que;
                que.push(mp(i, j));
                vis[i][j]=true;
                int id=++num;
                blocks[id].clear();
                while(!que.empty()) {
                    PII cur=que.front(); que.pop();
                    blocks[id].pb(cur);
                    bid[cur.fi][cur.se]=id;
                    repn(k, 4) {
                        int x=cur.fi+dx[k], y=cur.se+dy[k];
                        if(!inside(x, y) || vis[x][y]) continue;
                        if(str[x][y]!=str[cur.fi][cur.se]) continue;
                        que.push(mp(x, y));
                        vis[x][y]=true;
                    }
                }
            }

        VPI start;
        repn(i, n) start.pb(mp(i, -1)), start.pb(mp(i, m));
        repn(i, m) start.pb(mp(-1, i)), start.pb(mp(n, i));
        fillchar(touched, false);
        fillchar(vis, false);
        fillchar(l, 0xff);
        find_fa(start, 0, '#');

        string ans=make(0);
        //cout<<ans<<endl;
        return ans;
    }
public:
    string canTransform(vector <string> initial, vector <string> target) {
        string s1=go(initial);
        string s2=go(target);
        if(s1==s2) return "Possible";
        else return "Impossible";
    }
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"#"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"."}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "Impossible"; verify_case(0, Arg2, canTransform(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"..",
 ".."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {".#",
 "##"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "Possible"; verify_case(1, Arg2, canTransform(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"...",
 ".#.",
 "..."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"###",
 "#.#",
 "###"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "Impossible"; verify_case(2, Arg2, canTransform(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {".#.#.......",
 "####.###...",
 ".....####..",
 "..##.#.##.#",
 ".##..#.##.#",
 ".#######...",
 ".#....###.#",
 ".##.#.#....",
 "..#...#...#",
 "..#####...#",
 "..........."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"...........",
 ".###....#..",
 ".#.#..#....",
 ".###.......",
 ".#####.....",
 ".#...#####.",
 ".#.#.....#.",
 ".#.#####.#.",
 ".#.......#.",
 ".#########.",
 "..........."}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "Impossible"; verify_case(3, Arg2, canTransform(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {".....",
 ".###.",
 ".....",
 ".###.",
 "....."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {".....",
 ".#.#.",
 ".#.#.",
 ".#.#.",
 "....."}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "Possible"; verify_case(4, Arg2, canTransform(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
    Balance ___test;
    /*
       ___test.run_test(0);
    /*/
      ___test.run_test(-1);
    //*/
    return 0;
}
// END CUT HERE
