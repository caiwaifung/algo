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

const int MAXN=200010;
const int MAXNodes1=5900000;
const int MAXNodes2=8300000/3;
const int MAXNodes=MAXNodes1+MAXNodes2;

PII a[MAXN];
int n, m;

typedef unsigned long long ULL;
typedef unsigned short US;

struct FunctionalSegmentTree {
    ULL tr1[MAXNodes1];
    US tr2[MAXNodes2*3];
    int num1, num2;

    int roots[MAXN];
    int curtime;

    // return timestamp
    int init() {
        curtime=0;
        roots[0]=0;
        num1=num2=0;
        tr1[0]=0;
        return 0;
    }

    int make_delta(int x, int v) {
        assert(num2+5<MAXNodes2*3);
        num2+=3; int y=num2;
        ULL tmp=ULL(x)*MAXN+ULL(v);
        tr2[y]=US(tmp>>32), tr2[y+1]=US((tmp>>16)&((1<<16)-1)), tr2[y+2]=US(tmp&((1<<16)-1));
        return MAXNodes1+y/3;
    }
    void get_delta(int x, int &y, int &v) {
        x-=MAXNodes1; x*=3;
        ULL tmp=(ULL(tr2[x])<<32)+(ULL(tr2[x+1])<<16)+ULL(tr2[x+2]);
        y=int(tmp/MAXN), v=int(tmp%MAXN);
    }
    void get_node(int x, int &l, int &r, int &v) {
        int delta=0;
        if(x>=MAXNodes1)
            get_delta(x, x, delta);
        l=int(tr1[x]/MAXN/MAXNodes), r=int(tr1[x]/MAXN%MAXNodes);
        v=int(tr1[x]%MAXN)+delta;
    }
    void set_node(int x, int l, int r, int v) {
        tr1[x]=ULL(l)*MAXN*MAXNodes+ULL(r)*MAXN+v;
    }
    int minv(int x) {
        int delta=0;
        if(x>=MAXNodes1) {
            get_delta(x, x, delta);
            //printf("got %d %d\n",x,delta);
        }
        return int(tr1[x]%MAXN)+delta;
    }

    int add(int x, int s, int t, int st, int en, int val) {
        //printf("add %d [%d,%d] %d\n",x,s,t,val);fflush(stdout);
        if(st<=s && t<=en) {
            if(x>=MAXNodes1) {
                int delta;
                get_delta(x, x, delta);
                val+=delta;
            }
            x=make_delta(x, val);
            return x;
        }
        int l, r, v; get_node(x, l, r, v);
        //printf("   l=%d r=%d v=%d\n",l,r,v);fflush(stdout);
        x=++num1;
        assert(x+5<MAXNodes1);

        //printf("!_!\n"); fflush(stdout);
        int dv=v-min(minv(l), minv(r));
        //printf("!!\n"); fflush(stdout);

        int mid=(s+t)/2;
        if(st<=mid)
            l=add(l, s, mid, st, en, val);
        if(mid<en)
            r=add(r, mid+1, t, st, en, val);
        //printf("!.!\n"); fflush(stdout);

        v=min(minv(l), minv(r))+dv;
        set_node(x, l, r, v);
        return x;
    }
    int getmin(int x, int s, int t, int st, int en) {
        if(x==0)
            return 0;

        int l, r, v; get_node(x, l, r, v);
        int dv=v-min(minv(l), minv(r));
        if(st<=s && t<=en)
            return v;

        int mid=(s+t)/2, ans=1<<30;
        if(st<=mid)
            setmin(ans, getmin(l, s, mid, st, en));
        if(mid<en)
            setmin(ans, getmin(r, mid+1, t, st, en));
        ans+=dv;
        return ans;
    }

    // return timestamp
    int add(int l, int r, int v) {
        ++curtime;
        roots[curtime]=add(roots[curtime-1], 1, n, l, r, v);
        return curtime;
    }

    int getmin(int timestamp, int l, int r) {
        assert(0<=timestamp && timestamp<=curtime);
        int ans=getmin(roots[timestamp], 1, n, l, r);
        return ans;
    }
} tree;

int m1=0, m2=0;

void preprocess() {
    sort(a+1, a+n+1);

    int t0=tree.init();
    assert(t0==0);
    forint(i, 1, n) {
        int pos=a[i].se;
        int l=max(pos-m+1, 1), r=pos;
        //printf("p=%d l=%d r=%d\n",pos,l,r);
        int timestamp=tree.add(l, r, 1);
        assert(timestamp==i);
    }

    /*
    printf("  %d %d\n", tree.num1, tree.num2);
    if(m1<tree.num1 || m2<tree.num2) {
    setmax(m1, tree.num1);
    setmax(m2, tree.num2);
    printf("%d (%d) %d (%d)\n", m1, MAXNodes1,m2,MAXNodes2*3);
    printf(" -> %d %d\n", m1/MAXN+1, m2/3/MAXN+1);
    }
    */
}

int query(int l, int r, int q) {
    int i=int(lower_bound(a+1, a+n+1, MP(q,0))-a);
    assert(i>=1 && i<=n+1);
    //printf("q=%d i=%d\n",q,i);
    int ans=tree.getmin(i-1, l, r);
    return ans;
}

int main() {
    //*
    scanf("%d%d", &n,&m);
    forint(i, 1, n) scanf("%d", &a[i].fi), a[i].se=i;
    preprocess();
    /*/
    printf("%.4lf\n", (sizeof(tree)+sizeof(a))/1024.);
    printf("%.4lf\n", (sizeof(tree)+sizeof(a))/1000.);
    while(1) {
    n=200000; m=(rand()%10000*10000+rand())%(n+1);; 
    forint(i,1, n) a[i].fi=rand(), a[i].se=i;

    preprocess();
    }
    //*/

    int cs; scanf("%d", &cs);
    int preans=0;
    while(cs--) {
        int l, r, x;
        scanf("%d%d%d", &l,&r,&x);
        int q=x^preans;

        int ans=query(l, r, q);
        printf("%d\n", ans);
        preans=ans;
    }

    return 0;
}
