#include <algorithm>
#include <map>
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

void solve() {
}

int main() {
    map<VI, int> cnt;
    int tot=1; repn(i, 6) tot*=3;
    repn(s, tot) {
        VI scores(4);
        int cur=s;
        repn(i, 4) replr(j, i+1, 4) {
            if(cur%3==0) {
                scores[i]+=3;
            } else if(cur%3==1) {
                scores[j]+=3;
            } else {
                scores[i]++, scores[j]++;
            }
            cur/=3;
        }
        cnt[scores]++;
    }

    int cs; scanf("%d", &cs);
    rep(i, 1, cs) {
        printf("Case #%d: ", i);
        VI a(4); repn(k, 4) scanf("%d", &a[k]);
        if(cnt[a]>1) printf("No\n");
        else if(cnt[a]==1) printf("Yes\n");
        else printf("Wrong Scoreboard\n");
    }
    return 0;
}
