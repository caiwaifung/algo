#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define sz(a) static_cast<int>(a.size())
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

bool mem[9][9][9][9][2];
bool has[9][9][9][9][2];

bool win(int wx, int wy, int bx, int by, bool w_turn) {
    int wi=w_turn?1:0;
    bool& ans=mem[wx][wy][bx][by][wi];
    if(has[wx][wy][bx][by][wi]) return ans;
    has[wx][wy][bx][by][wi]=true;

    if(w_turn) {
        const VPI dirs{{-2, -1}, {-1, -2}, {1, -2}, {2, -1},
                      {-2, 1}, {-1, 2}, {1, 2}, {2, 1}};
        ans=false;
        for(PII dir: dirs) {
            int x=wx+dir.fi, y=wy+dir.se;
            if(x<1 || x>8 || y<1 || y>8) continue;
            if(x==bx && y==by) {
                ans=true;
            } else {
                if(win(x, y, bx, by, false)) ans=true;
            }
        }
        return ans;
    } else {
        ans=true;
        if(bx>1) {
            for(int dy: {-1, 1}){
                int x=bx-1, y=by+dy;
                if(y<1 || y>8) continue;
                if(x==wx && y==wy) {
                    int x0=x-1, y0=y+dy;
                    if(x0>=1 && x0<=8 && y0>=1 && y0<=8)
                        ans=false;
                } else if(x==1) {
                    ans=false;
                } else {
                    if(!win(wx, wy, x, y, true)) ans=false;
                }
            }
        }
        return ans;
    }
}

int main() {
    string t, w, b;
    cin>>t>>w>>b;
    auto parse=[](string s, int* x, int* y) {
        *x=int(s[1]-'0');
        *y=int(s[0]-'a'+1);
    };
    int wx, wy; parse(w, &wx, &wy);
    int bx, by; parse(b, &bx, &by);
    bool w_turn=(t[0]=='w');

    fillchar(has, false);
    bool w_win=win(wx, wy, bx, by, w_turn);
    if(w_win) printf("White\n");
        else printf("Black\n");

    return 0;
}
