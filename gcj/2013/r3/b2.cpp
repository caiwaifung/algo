// 21:42 - 22:37 - wa sample
// 23:06 - 00:37 - nearly ok but cannot solve same-line problem - wa small
// 00:52 - 01:00 - pass small - wa large
// 14:13 - 14:24 - pass
// CODING: 55 min
// DEBUG:  91+8+11=110 min
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
typedef pair<int,int> PDD;
typedef vector<LL> VL;
typedef vector<int> VI;
typedef vector<PII> VPI;
typedef vector<string> VS;
template<class T> void setmax(T &a, T b) { if(b>a) a=b; }
template<class T> void setmin(T &a, T b) { if(b<a) a=b; }
template<class T> T gcd(T a, T b) { return b==0?a:gcd(b,a%b); }
template<class T> void print_all(const T &_a) {
    for(auto &x: _a) cout<<x<<" ";
    cout<<endl;
}

struct Point {
    int x, y;
    Point() { }
    Point(int _x, int _y) : x(_x), y(_y) { }
    bool operator <(const Point &p) const {
        return x<p.x || (x==p.x && y<p.y);
    }
    void println() const { printf("(%d,%d)\n",x,y); }
    Point operator +(const Point &p) const { return Point(x+p.x, y+p.y); }
    Point operator -(const Point &p) const { return Point(x-p.x, y-p.y); }
    Point operator *(int b) const { return Point(x*b, y*b); }
    Point operator /(int b) const { return Point(x/b, y/b); }
    void rotate90() { swap(x, y); x=-x; }
    friend LL mult(Point p1, Point p2) { return p1.x*(LL)p2.y-p1.y*(LL)p2.x; }
    friend LL dot(Point p1, Point p2) { return p1.x*(LL)p2.x+p1.y*(LL)p2.y; }
    friend LL mult(Point p0, Point p1, Point p2) { return mult(p1-p0, p2-p0); }
    friend LL dot(Point p0, Point p1, Point p2) { return dot(p1-p0, p2-p0); }
    LL abs() const { return x*(LL)x+y*(LL)y; }
    friend LL dis(Point p1, Point p2) { return (p1-p2).abs(); }
    friend bool on_segment(Point p, Point p1, Point p2) {
        return mult(p,p1,p2)==0 && dot(p,p1,p2)<=0;
    }
};


Point a[1000]; 
int n;

bool is_line(VI x) {
    vector<pair<Point, int> > ts;
    for(int i: x) ts.PB(MP(a[i], i));
    sort(all(ts));
    bool yes=true;
    for(auto &t: ts) if(mult(ts[0].fi, ts[1].fi, t.fi)!=0) yes=false;
    return yes;
}

VI good_convex(VI x) {
    vector<pair<Point, int> > ts;
    for(int i: x) ts.PB(MP(a[i], i));
    sort(all(ts));

    VI b;
    for(auto &t: ts) {
        while(b.size()>1 && mult(a[b[b.size()-2]], a[b.back()], a[t.se])<=0)
            b.pop_back();
        b.PB(t.se);
    }
    auto rts=ts; reverse(all(rts));
    size_t z=b.size();
    for(auto &t: rts) {
        while(b.size()>z && mult(a[b[b.size()-2]], a[b.back()], a[t.se])<=0)
            b.pop_back();
        b.PB(t.se);
    }
    b.pop_back();
    return b;
}

VI convex(VI x) {
    vector<pair<Point, int> > ts;
    for(int i: x) ts.PB(MP(a[i], i));
    sort(all(ts));

    if(is_line(x)) {
        VI b;
        for(auto &t: ts) b.PB(t.se);
        return b;
    }

    VI b;
    for(auto &t: ts) {
        while(b.size()>1 && mult(a[b[b.size()-2]], a[b.back()], a[t.se])<0)
            b.pop_back();
        b.PB(t.se);
    }
    auto rts=ts; reverse(all(rts));
    size_t z=b.size();
    b.pop_back();
    for(auto &t: rts) {
        while(b.size()>z && mult(a[b[b.size()-2]], a[b.back()], a[t.se])<0)
            b.pop_back();
        b.PB(t.se);
    }
    b.pop_back();

    /*
    VI c;
    c.PB(b.back()), b.pop_back();
    for(int i: b) {
        while(1) {
            bool found=false;
            int fk=0;
            for(int k: x) {
                if(k==c.back()) continue;
                if(k==i) continue;
                if(!on_segment(a[k], a[i], a[c.back()])) continue;
                if(!found || dis(a[c.back()], a[fk])>dis(a[c.back()], a[k]))
                    found=true, fk=k;
            }
            printf("fk=%d back=%d i=%d\n",fk,c.back(),i);
            if(found) c.PB(fk);
                else break;
        }
        c.PB(i);
    }
    b=c;
    */

    //printf("b: "); print_all(b);
    assert(set<int>(all(b)).size()==b.size());
    forn(i, b.size()) {
        int i2=int((i+1)%b.size());
        int i3=int((i+2)%b.size());
        assert(mult(a[b[i]], a[b[i2]], a[b[i3]])>=0);
        if(mult(a[b[i]], a[b[i2]], a[b[i3]])==0)
            assert(on_segment(a[b[i2]], a[b[i]], a[b[i3]]));
        assert(!on_segment(a[b[i]], a[b[i2]], a[b[i3]]));
        assert(!on_segment(a[b[i3]], a[b[i2]], a[b[i]]));
    }
    forn(i, b.size()) {
        int i2=int((i+1)%b.size());
        for(int j: x) {
            if(find(all(b), j)!=b.end()) continue;
            assert(mult(a[b[i]], a[b[i2]], a[j])>0);
        }
    }
    return b;
}

LL area(VI x) {
    LL ans=0;
    forn(i, x.size()-1)
        ans+=mult(a[x[0]], a[x[i]], a[x[i+1]]);
    return ans;
}

void init() {
    cin>>n;
    forn(i, n) cin>>a[i].x>>a[i].y;
}

bool cmp_vxy(Point vx, Point vy, Point p1, Point p2) {
    LL cmp=dot(p1,vy)-dot(p2,vy); // want <0
    if(cmp==0) {
        cmp=dot(p1,vx)-dot(p2,vx);
    }
    return cmp<0;
}

PII findpair(int x0, int x1, VI ds) {
    Point vx=a[x1]-a[x0];
    Point vy=vx; vy.rotate90();

    ds=convex(ds);

    int i=0;
    forn(j, ds.size()) if(cmp_vxy(vx, vy, a[ds[j]], a[ds[i]])) i=j;
    int i2=int((i+1)%ds.size());
    int i0=int((i-1+ds.size())%ds.size());
    if(is_line(ds)) {
        if(i>0) i2=i0=i-1;
            else i2=i0=i+1;
    }

    if(mult(a[ds[i]], a[x1], a[ds[i2]])>0)
        return MP(ds[i], ds[i2]);
    else {
        assert(mult(a[ds[i]], a[ds[i0]], a[x0])>0);
        return MP(ds[i0], ds[i]);
    }
}

Point cmp_center;
bool cmp_point(int i, int j) {
    LL d=-mult(cmp_center, a[i], a[j]); // want <0
    if(d==0) d=dis(cmp_center, a[i])-dis(cmp_center, a[j]);
    return d<0;
}

VI make2(int c, VI es) {
    if(es.empty()) return es;
    cmp_center=a[c];
    sort(all(es), cmp_point);
    VI fs;
    fs.PB(es.back()), es.pop_back();
    while(!es.empty()) {
        if(mult(a[c], a[fs.back()], a[es.back()])==0) {
            fs.PB(es.back()), es.pop_back();
        }
        else
            break;
    }
    es.insert(es.end(), all(fs));
    return es;
}

VI make(int u, int v, VI es) {
    es.erase(find(all(es), u));
    es.erase(find(all(es), v));

    //printf("make u=%d v=%d es=",u,v); print_all(es);
    //a[u].println();
    //a[v].println();
    //for(int e:es) a[e].println();

    Point vx=a[v]-a[u];
    Point vy=vx; vy.rotate90();

    VI es1, es2;
    for(int e: es) {
        LL du=dot(a[u], vx);
        LL dv=dot(a[v], vx);
        LL d=dot(a[e], vx);
        if(d*2<du+dv) {
            es1.PB(e); continue;
        }
        if(d*2>du+dv) {
            es2.PB(e); continue;
        }
        du=dot(a[u], vy);
        d=dot(a[e], vy);
        assert(d!=du);
        if(d>du)
            es1.PB(e);
        else
            es2.PB(e);
    }

    es1=make2(u, es1);
    es2=make2(v, es2);

    //printf("es1="); print_all(es1);
    //printf("es2="); print_all(es2);

    VI ans;
    ans.PB(v);
    ans.insert(ans.end(), all(es2));
    ans.insert(ans.end(), all(es1));
    ans.PB(u);

    //printf("ans="); print_all(ans);

    return ans;
}

void check_poly(VI ans) {
    forn(i, ans.size()) forn(j, ans.size()) {
        int i1=ans[i], j1=ans[j];
        int i2=ans[(i+1)%ans.size()], j2=ans[(j+1)%ans.size()];
        if(i1==j1 || i1==j2 || i2==j1 || i2==j2) continue;
        Point a1=a[i1], a2=a[i2];
        Point b1=a[j1], b2=a[j2];
        if(mult(a1, a2, b1)*mult(a1, a2, b2)>=0) continue;
        if(mult(b1, b2, a1)*mult(b1, b2, a2)>=0) continue;
        assert(false);
        //forint(i, 1, n) printf("%d ", p[i]-1); printf(": bad %d %d\n",i,j); break;
    }
    forn(i, ans.size()) forn(j, ans.size()) {
        int i1=ans[i], i2=ans[(i+1)%ans.size()];
        if(ans[j]!=i1 && ans[j]!=i2) {
            Point a1=a[i1], a2=a[i2], b=a[ans[j]];
            assert(!on_segment(b, a1, a2));
        }
    }
}

void check_ans(VI ans) {
    VI full; forn(i, n) full.PB(i);
    VI cs=good_convex(full);
    assert(set<int>(all(ans)).size()==ans.size());
    assert(area(ans)*2>area(cs));
    assert((int)ans.size()==n);

    check_poly(ans);
}

bool solve_simple(VI cs, VI ds) {/*{{{*/
    if(ds.empty()) {
    //printf("!!#T1\n"); fflush(stdout);
        assert(n==(int)cs.size());
        check_ans(cs);
        forn(i, cs.size()) 
            cout<<cs[i]<<" ";
        cout<<endl;
        return true;
    }

    if(ds.size()==1) {
    //printf("!!#T2\n"); fflush(stdout);
        VI best;
        forn(i, cs.size()) {
            VI tmp=cs;
            tmp.insert(tmp.begin()+i, ds[0]);
            if(area(tmp)>area(best))
                best=tmp;
        }

        check_ans(best);
        assert((int)best.size()==n);
        assert(area(best)*2>area(cs));

        forn(i, n) cout<<best[i]<<" ";
        cout<<endl;
        return true;
    }

    if(is_line(ds)) {
    //printf("!!#T3\n"); fflush(stdout);
        vector<pair<Point,int> > ts;
        for(int i: ds) ts.PB(MP(a[i], i));
        sort(all(ts));
        ds.clear(); for(auto &t: ts) ds.PB(t.se);

        VI best;
        forn(i, cs.size()) {
            int i0=int((i+cs.size()-1)%cs.size());
            if(mult(a[cs[i0]], a[ds.front()], a[ds.back()])>0)
                reverse(all(ds));
            if(mult(a[cs[i]], a[ds.front()], a[ds.back()])>0)
                reverse(all(ds));
            VI tmp=cs;
            tmp.insert(tmp.begin()+i, all(ds));
            if(area(tmp)>area(best))
                best=tmp;
        }

        check_ans(best);
        assert((int)best.size()==n);
        assert(area(best)*2>area(cs));

        forn(i, n) cout<<best[i]<<" ";
        cout<<endl;
        return true;
    }
    return false;
}/*}}}*/

void solve(int case_id) {
    printf("Case #%d: ", case_id);

    //printf("!!#1\n"); fflush(stdout);

    VI full; forn(i, n) full.PB(i);
    VI cs=convex(full), ds;
    forn(i, n) if(find(all(cs), i)==cs.end()) ds.PB(i);
    assert(area(cs)==area(good_convex(full)));
    //print_all(cs);
    //printf("!!#2\n"); fflush(stdout);
    //printf("!!#T3\n"); fflush(stdout);
    
    if(solve_simple(cs, ds)) return;

    PII pair=findpair(cs[0], cs[1], ds);
    int u=pair.fi, v=pair.se;

    //printf("!!#x\n"); fflush(stdout);
    VI es=make(u, v, ds);
    assert(es.front()==v);
    assert(es.back()==u);
    //printf("#1: "); fflush(stdout); check_poly(es); printf("done.\n"); fflush(stdout);
    //printf("!!#y es:%d ds:%d u=%d v=%d\n",(int)es.size(),(int)ds.size(),u,v); fflush(stdout);
    //cout<<area(es)<<" "<<es.size()<<" "<<n<<endl;
    es.PB(cs[0]);
    es.PB(cs[1]);

    //a[cs[0]].println();
    //a[cs[1]].println();
    //cout<<area(es)<<" "<<es.size()<<" "<<n<<endl;
    //printf("#2: "); fflush(stdout); check_poly(es); printf("done.\n"); fflush(stdout);

    if(area(es)*2>=area(cs)) { // tiny bug: what if equal?
    //printf("!!#z1\n"); fflush(stdout);
        es=full;
        es.erase(find(all(es), cs[0]));
        es.erase(find(all(es), cs[1]));
        es=make(u, v, es);
        es.PB(cs[0]);
        es.PB(cs[1]);
    }
    else {
        es.pop_back();
        es.pop_back();
        reverse(all(es));
        es.insert(es.end(), cs.begin()+1, cs.end());
        es.insert(es.end(), cs[0]);
    //printf("!!#z2\n"); fflush(stdout); for(int e: es) a[e].println();
    }
    //cout<<area(es)<<" "<<es.size()<<" "<<n<<endl;
    //cout<<area(cs)<<" "<<cs.size()<<endl;

    check_ans(es);
    assert(area(es)*2>area(cs));
    assert(n==(int)es.size());
    assert(set<int>(all(es)).size()==es.size());
    forn(i, n) cout<<es[i]<<" ";
    cout<<endl;
}

int main() {
    int csn; scanf("%d", &csn);
    forint(cs, 1, csn) {
        init();
        solve(cs);
    }
    return 0;
}
