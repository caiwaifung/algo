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

const int N=3010;

struct Node {
    int lcnt=0, rcnt=0;
    Node *l=nullptr, *r=nullptr;
};

int mid[N][N];
int a[N];
int n;

Node* insert(Node* x, int d, int val) {
    {
        Node* tmp=new Node();
        if(x!=nullptr) *tmp=*x;
        x=tmp;
    }
    if(val&(1<<d)) {
        ++x->rcnt;
        if(d>0) x->r=insert(x->r, d-1, val);
    } else {
        ++x->lcnt;
        if(d>0) x->l=insert(x->l, d-1, val);
    }
    return x;
}

void prepare() {
    static Node* roots[N];
    roots[0]=nullptr;
    rep(i, 1, n) roots[i]=insert(roots[i-1], 30, a[i]);

    rep(i, 1, n) rep(j, i, n) {
        int val=0;
        Node *p=roots[i-1], *q=roots[j];
        int l=0, r=0;
        irep(d, 30, 0) {
            int cl=0, cr=0;
            if(p) {
                cl-=p->lcnt;
                cr-=p->rcnt;
            }
            if(q) {
                cl+=q->lcnt;
                cr+=q->rcnt;
            }
            if(l+cl>r+cr) {
                r+=cr;
                if(p) p=p->l;
                if(q) q=q->l;
            } else {
                l+=cl;
                val+=1<<d;
                if(p) p=p->r;
                if(q) q=q->r;
            }
        }
        mid[i][j]=val;
    }
}

int main() {
    ios_base::sync_with_stdio(false);

    cin>>n;
    rep(i, 1, n) { cin>>a[i]; a[i]=a[i]+n-i; }
    prepare();

    VPI st;
    rep(i, 1, n) {
        st.pb(mp(i, i));
        while(sz(st)>=2) {
            const auto x=st[sz(st)-2];
            const auto y=st[sz(st)-1];
            if(mid[x.fi][x.se]>mid[y.fi][y.se]) {
                st.pop_back();
                st.back().se=y.se;
            } else {
                break;
            }
        }
    }
    LL ans=0;
    for(const auto& p: st) {
        rep(i, p.fi, p.se) ans+=abs(mid[p.fi][p.se]-a[i]);
    }
    cout<<ans<<endl;

    return 0;
}
