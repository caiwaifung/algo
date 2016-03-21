#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

#define _ (int)
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

const int K=20;

VI a; int n;

void read_input() {
    scanf("%d", &n);
    VI p(n+1), q(n+1);
    rep(i, 1, n) scanf("%d", &p[i]);
    rep(i, 1, n) scanf("%d", &q[i]);
    VI rq(n+1); rep(i, 1, n) rq[q[i]]=i;
    a.resize(n+1);
    rep(i, 1, n) a[i]=rq[p[i]];
}

struct Node {
    int cnt;
    Node* child[2];
    explicit Node(Node* from) {
        if(from==nullptr) {
            cnt=0; child[0]=child[1]=nullptr;
        } else {
            memcpy(this, from, sizeof(Node));
        }
    }
};
vector<Node*> root;

Node* ins(Node* x, int v, int b) {
    x=new Node(x); ++x->cnt;
    if(b==0) return x;
    int c=(v&b)?1:0;
    x->child[c]=ins(x->child[c], v, b>>1);
    return x;
}

void build_tree() {
    root.resize(n+1);
    root[0]=nullptr;
    rep(i, 1, n) root[i]=ins(root[i-1], a[i], 1<<K);
}

int get(const Node* x, int v, int b) {
    if(x==nullptr) return 0;
    if(b==0) return x->cnt;
    int c=(v&b)?1:0; 
    int ans=get(x->child[c], v, b>>1);
    if(c==1 && x->child[0]!=nullptr) ans+=x->child[0]->cnt;
    return ans;
}

int G(int t, int z) { return get(root[t], z, 1<<K); }
int F(int t, int l, int r) { return G(t, r)-G(t, l-1); }

void answer() {
    int ans=-1;
    int m; scanf("%d", &m);
    while(m--) {
        ++ans;
        int l1, r1, l2, r2;
        scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
        int _n=n; auto f=[_n,ans](int z) { return (z-1+ans)%_n+1; };
        l1=f(l1), r1=f(r1), l2=f(l2), r2=f(r2);
        //printf("%d %d %d %d\n",l1,r1,l2,r2);
        if(l1>r1) swap(l1, r1);
        if(l2>r2) swap(l2, r2);
        ans=F(r1, l2, r2)-F(l1-1, l2, r2);
        printf("%d\n", ans);
    }
}

int main() {
    read_input();
    build_tree();
    answer();
    return 0;
}