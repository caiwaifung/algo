#include <algorithm>
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

struct Node {
    bool bad=false;
    int succ[26];
    Node() { fillchar(succ, 0xff); }
};

vector<Node> build(VS words) {
    vector<Node> tr(1);
    for(const string& s: words) {
        int x=0;
        for(char ch: s) {
            int c=ch-'a';
            if(tr[x].succ[c]<0) {
                tr[x].succ[c]=sz(tr);
                tr.pb(Node());
            }
            x=tr[x].succ[c];
        }
        tr[x].bad=true;
    }

    VI suffix(sz(tr));
    queue<int> que;
    repn(c, 26) {
        if(tr[0].succ[c]>=0) {
            que.push(tr[0].succ[c]);
        } else {
            tr[0].succ[c]=0;
        }
    }
    while(!que.empty()) {
        const int x=que.front();
        if(tr[suffix[x]].bad) {
            tr[x].bad=true;
        }
        //printf("x=%d\n",x);
        que.pop();
        repn(c, 26) {
            const int y=tr[x].succ[c];
            if(y>=0) {
                suffix[y]=tr[suffix[x]].succ[c];
                que.push(y);
            } else {
                tr[x].succ[c]=tr[suffix[x]].succ[c];
            }
        }
    }
    return tr;
}

int main() {
    int len1, len2, num; scanf("%d%d%d", &len1,&len2,&num);
    VS words;
    repn(i, num) {
        static char buf[22];
        scanf("%s", buf);
        words.pb(string(buf));
    }
    vector<Node> tr=build(words);

    string alphabet;
    for(char c='a'; c<='z'; ++c) alphabet+=c;
    for(char c='A'; c<='Z'; ++c) alphabet+=c;
    for(char c='0'; c<='9'; ++c) alphabet+=c;

    const int MOD=1000003;
    //const int MOD=1000000000;
    static int f[22][2][2][2][1010];
    fillchar(f, 0);
    f[0][0][0][0][0]=1;
    int ans=0;
    rep(len, 0, len2) repn(upp, 2) repn(low, 2) repn(dig, 2) repn(state, sz(tr)) {
        if(tr[state].bad) {
            continue;
        }
        const int val=f[len][upp][low][dig][state];
        if(len>=len1 && len<=len2 && upp && low && dig) {
            (ans+=val)%=MOD;
        }
        for(char ch: alphabet) {
            int u2=upp, l2=low, d2=dig;
            int c=-1;
            if(ch>='a' && ch<='z') { c=ch-'a'; l2=1; }
            else if(ch>='A' && ch<='Z') { c=ch-'A'; u2=1; }
            else {
                d2=1;
                if(ch=='0') c='o'-'a';
                else if(ch=='1') c='i'-'a';
                else if(ch=='3') c='e'-'a';
                else if(ch=='5') c='s'-'a';
                else if(ch=='7') c='t'-'a';
            }
            int s2=(c>=0 ? tr[state].succ[c] : 0);
            (f[len+1][u2][l2][d2][s2]+=val)%=MOD;
        }
    }
    printf("%d\n", ans);

    return 0;
}
