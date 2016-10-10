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
    int here, cnt[26];
    Node* child[26];
};

Node* insert(Node* x, const char* c, int id) {
    if(x==nullptr) {
        x=new Node();
        memset(x, 0, sizeof(Node));
        x->here=-1;
    }
    if(*c=='\0') {
        x->here=id;
    } else {
        int cur=int(*c-'a');
        ++x->cnt[cur];
        x->child[cur]=insert(x->child[cur], c+1, id);
    }
    return x;
}

int main() {
    int n; scanf("%d", &n);
    Node* root=nullptr;
    repn(i, n) {
        static char s[400010];
        scanf("%s", s);
        root=insert(root, s, i);
    }

    vector<vector<pair<int, string>>> qs(n);
    int q; scanf("%d", &q);
    repn(i, q) {
        static char buf[99]; int k; 
        scanf("%d%s", &k, buf);
        --k;
        qs[k].pb(mp(i, string(buf)));
    }

    VI ans(q);
    int cnt[26][26], base=1; fillchar(cnt, 0);
    const function<void(Node*)> dfs=[&](Node* x) {
        if(x==nullptr) return;
        if(x->here>=0) {
            for(const auto& t: qs[x->here]) {
                int r=base;
                //printf("here=%d q=%d\n",x->here,t.fi);
                repn(i, 26) replr(j, i+1, 26) {
                    //if(cnt[t.se[i]-'a'][t.se[j]-'a']) printf("cnt[%c,%c]=%d\n",t.se[i],t.se[j], cnt[t.se[i]-'a'][t.se[j]-'a']);
                    r+=cnt[t.se[i]-'a'][t.se[j]-'a'];
                }
                ans[t.fi]=r;
            }
        }
        if(x->here>=0) ++base;
        repn(i, 26) if(x->child[i]!=nullptr) {
            repn(j, 26) if(j!=i) cnt[j][i]+=x->cnt[j];
            dfs(x->child[i]);
            repn(j, 26) if(j!=i) cnt[j][i]-=x->cnt[j];
        }
        if(x->here>=0) --base;
    };
    dfs(root);

    repn(i, q) printf("%d\n", ans[i]);


    return 0;
}
