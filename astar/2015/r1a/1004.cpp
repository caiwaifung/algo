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

struct Tree {
    struct Node {
        int val, rkey;
        int l, r, size;
    } tr[10010];
    int num, root;

    void update(int x) {
        tr[x].size=tr[tr[x].l].size+tr[tr[x].r].size+1;
    }
    int lrotate(int x) {
        int y=tr[x].l; tr[x].l=tr[y].r; tr[y].r=x;
        update(x); update(y);
        return y;
    }
    int rrotate(int x) {
        int y=tr[x].r; tr[x].r=tr[y].l; tr[y].l=x;
        update(x); update(y);
        return y;
    }
    int insert(int x, int y) {
        if(x==0) return y;
        if(tr[y].val<tr[x].val) {
            tr[x].l=insert(tr[x].l, y);
            if(tr[tr[x].l].rkey>tr[x].rkey)
                x=lrotate(x);
        }
        else {
            tr[x].r=insert(tr[x].r, y);
            if(tr[tr[x].r].rkey>tr[x].rkey)
                x=rrotate(x);
        }
        update(x);
        return x;
    }
    int remove(int x, int val) {
        if(tr[x].val==val) {
            if(tr[x].l==0 && tr[x].r==0)
                return 0;
            if(tr[tr[x].l].rkey>tr[tr[x].r].rkey) {
                x=lrotate(x);
                tr[x].r=remove(tr[x].r, val);
            }
            else {
                x=rrotate(x);
                tr[x].l=remove(tr[x].l, val);
            }
        }
        else {
            if(val<tr[x].val)
                tr[x].l=remove(tr[x].l, val);
            else
                tr[x].r=remove(tr[x].r, val);
        }
        update(x);
        return x;
    }
    int ask(int x, int ind) {
        assert(ind<=tr[x].size);
        int ls=tr[tr[x].l].size;
        if(ind<=ls)
            return ask(tr[x].l, ind);
        if(ind==ls+1)
            return tr[x].val;
        return ask(tr[x].r, ind-ls-1);
    }

    void init() {
        num=root=0;
        tr[0].rkey=-1;
        tr[0].size=0;
    }
    void add(int val) {
        int x=++num;
        tr[x].val=val, tr[x].rkey=rand();
        tr[x].l=tr[x].r=0, tr[x].size=1;
        root=insert(root, x);
    }
    void del(int val) {
        root=remove(root, val);
    }
    int query(int ind) {
        return ask(root, ind);
    }
};

bool solve(int cs) {
    int n; if(scanf("%d", &n)<1) return false;
    printf("Case #%d:\n", cs);
    static Tree tr;
    static int que[10010];
    int ss=1, tt=0;
    tr.init();
    forint(i, 1, n) {
        char cmd[9]; scanf("%s", cmd);
        if(cmd[0]=='i') {
            int x; scanf("%d", &x);
            tr.add(x);
            que[++tt]=x;
        }
        else if(cmd[0]=='o') {
            tr.del(que[ss++]);
        }
        else if(cmd[0]=='q') {
            int num=tt-ss+1;
            int ind=num/2+1;
            int ans=tr.query(ind);
            printf("%d\n", ans);
        }
        else {
            assert(false);
        }
    }
    return true;
}

int main() {
    int cs=0;
    while(1) {
        if(!solve(++cs)) break;
    }
    return 0;
}
