#include <map>
#include <cassert>
#include <functional>
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

const int N=200010;

int a[N], n;
VI es[N]; int fa[N];
int st[N], en[N], seq[N];

int gt[N], dgt[N];

struct Node {
    int rcnt=0;
    Node *c[2]={nullptr,nullptr};
}* root[N];

Node* insert(Node* x, int v, int b) {
    if(b<0) return x;
    Node* tmp=x; x=new Node(); if(tmp) *x=*tmp;
    if(v&(1<<b)) {
        ++x->rcnt;
        x->c[1]=insert(x->c[1], v, b-1);
    } else {
        x->c[0]=insert(x->c[0], v, b-1);
    }
    //cout<<"insert end"<<endl;
    return x;
}

int go(Node* x, int v, int b) {
    if(!x || b<0) return 0;
    if(v&(1<<b)) return go(x->c[1], v, b-1);
    else return x->rcnt+go(x->c[0], v, b-1);
}

void init() {
    scanf("%d", &n);
    rep(i, 1, n) scanf("%d", &a[i]);
    rep(i, 1, n-1) {
        int x, y; scanf("%d%d", &x,&y);
        es[x].pb(y), es[y].pb(x);
    }
    int tot=0;
    function<void(int,int)> dfs=[&](int x, int f) {
        fa[x]=f;
        seq[++tot]=x; st[x]=tot;
        for(int y: es[x]) if(y!=f) dfs(y, x);
        en[x]=tot;
    };
    dfs(1, 0);

    root[0]=nullptr;
    rep(i, 1, n) {
        root[i]=insert(root[i-1], a[seq[i]], 20);
    }
}
LL query_subtree(int x, int v) {
    return go(root[en[x]], v, 20)-go(root[st[x]-1], v, 20);
}

LL tr[N];
void add(int x, LL v) {
    for(; x<=n; x+=x&-x) tr[x]+=v;
}
void add(int l, int r, LL v) {
    add(l, v);
    add(r+1, -v);
}
LL get(int x) {
    LL r=0;
    for(; x>0; x-=x&-x) r+=tr[x];
    return r;
}

void solve() {
    fillchar(tr, 0);
    rep(x, 1, n) {
        add(st[x], en[x], query_subtree(1, a[x])-query_subtree(x, a[x]));
        for(int y: es[x]) if(y!=fa[x]) {
            LL v=query_subtree(y, a[x]);
            add(1, n, v);
            add(st[y], en[y], -v);
        }
    }

    pair<LL, int> ans=mp(1LL<<60, 0);
    rep(x, 1, n) {
        setmin(ans, mp(get(st[x]), x));
    }
    cout<<ans.se<<" "<<ans.fi<<endl;
}

int main() {
    init();
    solve();
    return 0;
}
