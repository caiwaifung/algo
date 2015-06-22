#include <algorithm>
#include <ctime>
#include <random>
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
#ifdef DEBUG
    #define _debug(args...) { fprintf(stderr, args); fflush(stderr); }
#else
    #define _debug(args...) {}
#endif
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

int data[888][1024];
int ans[1024];
int n;
LL penalty;

void load() {
    FILE *f = fopen("ans.txt", "r");
    assert(f != nullptr);
    repn(j, 1024) fscanf(f, "%d", &ans[j]);
    fclose(f);
}

void save() {
    FILE *f = fopen("ans.txt", "w");
    assert(f != nullptr);
    repn(j, 1024) fprintf(f, "%d ", ans[j]);
    fprintf(f, "\n");
    fclose(f);
}

LL cal_penalty() {
    LL p=0;
    repn(cur, n) {
        static int img[32][32];
        repn(i, 32) repn(j, 32)
            img[i][j]=data[cur][ans[i*32+j]];
        repn(i, 32) repn(j, 32) {
            repn(k, 4) {
                int i2=i+(k&1?1:-1), j2=j+(k&2?1:-1);
                if(i2>=0 && j2>=0 && i2<32 && j2<32)
                    p+=abs(img[i][j]-img[i2][j2]);
            }
        }
    }
    return p;
}

void swap_pixels(int x1, int y1, int x2, int y2) {
    repn(times, 2) {
        repn(k, 4) {
            int x3=x1+(k&1?1:-1), y3=y1+(k&2?1:-1);
            if(x3==x1 && y3==y1) continue;
            if(x3==x2 && y3==y2) continue;
            if(x3<0 || x3>=32 || y3<0 || y3>=32) continue;
            repn(cur, n) {
                int pixel1=data[cur][ans[x1*32+y1]];
                int pixel2=data[cur][ans[x2*32+y2]];
                int pixel3=data[cur][ans[x3*32+y3]];
                penalty-=abs(pixel1-pixel3)*2;
                penalty+=abs(pixel2-pixel3)*2;
            }
        }
        swap(x1, x2);
        swap(y1, y2);
    }
    swap(ans[x1*32+y1], ans[x2*32+y2]);
}


void go() {
    mt19937 gen;
    penalty=cal_penalty();
    uniform_int_distribution<int> pos_distr(0, 31);
    irep(num, 1, 1) irep(delta, 5, 1) {
        cout<<"num="<<num<<" delta="<<delta<<" penalty="<<penalty<<endl;
        uniform_int_distribution<int> distr(-delta, delta);
        int cnt=0, tot=0;

        assert(penalty==cal_penalty());
        
        repn(times, 10000) {
            if(times%1000==0) cout<<"   penalty="<<penalty<<endl;
            LL penalty_1=penalty;
            VPI p1, p2;
            repn(i, num) {
                int x=pos_distr(gen), y=pos_distr(gen);
                int x2=x+distr(gen), y2=y+distr(gen);
                x2=max(0, min(31, x2));
                y2=max(0, min(31, y2));
                p1.pb(mp(x, y));
                p2.pb(mp(x2, y2));
            }

            repn(i, num) 
                swap_pixels(p1[i].fi, p1[i].se, p2[i].fi, p2[i].se);
            if(penalty>penalty_1) {
                irepn(i, num) 
                    swap_pixels(p1[i].fi, p1[i].se, p2[i].fi, p2[i].se);
            }
            else ++cnt;
            ++tot;
        }
        cout<<"    finish. successful: "<<cnt<<" / "<<tot<<endl;
        save();
    }
}

void go1() {
    mt19937 gen((unsigned)time(0));
    penalty=cal_penalty();
    uniform_int_distribution<int> pos_distr(0, 31);

        //cout<<"delta="<<delta<<" penalty="<<penalty<<endl;
        //uniform_int_distribution<int> distr(-delta, delta);
        int cnt=0, tot=0;

        assert(penalty==cal_penalty());
        
        repn(times, 10000) {
            if(times%1000==0) cout<<"   penalty="<<penalty<<endl;
            LL penalty_1=penalty;

            int x=pos_distr(gen), y=pos_distr(gen);
            int x2=pos_distr(gen), y2=pos_distr(gen);
            //int x2=x+distr(gen), y2=y+distr(gen);
            //x2=max(0, min(31, x2));
            //y2=max(0, min(31, y2));
            if(x==x2 && y==y2) continue;

            swap_pixels(x, y, x2, y2);

            if(penalty>penalty_1) {
                swap_pixels(x, y, x2, y2);
            }
            else ++cnt;
            ++tot;
        }
        cout<<"    finish. successful: "<<cnt<<" / "<<tot<<endl;
        save();
    //}
}

void go2() {
    penalty=cal_penalty();

    vector<pair<PII,PII>> pairs;
    repn(x, 32) repn(y, 32) repn(x2, 32) repn(y2, 32)
        if(x!=x2 || y!=y2)
            pairs.pb(mp(mp(x,y), mp(x2,y2)));
    mt19937 gen((unsigned)time(0));
    repn(i, pairs.size()) {
        uniform_int_distribution<int> distr(0, i);
        swap(pairs[i], pairs[distr(gen)]);
    }

    int cnt=0, tot=0;
    for(auto pair: pairs) {
    //repn(x, 32) repn(y, 32) repn(x2, 32) repn(y2, 32) {
        if(tot%3000==0) {
            assert(cal_penalty()==penalty);
            cout<<"   penalty="<<penalty<<" ok="<<cnt<<"/"<<tot<<endl;
            cnt=tot=0;
            save();
        }

        int x=pair.fi.fi, y=pair.fi.se;
        int x2=pair.se.fi, y2=pair.se.se;
        //int x2=x+dx, y2=y+dy;
        //if(x2<0 || x2>=32 || y2<0 || y2>=32 || (x2==x && y2==y))
            //continue;
        LL p0=penalty;
        swap_pixels(x, y, x2, y2);
        if(penalty>p0) {
            swap_pixels(x, y, x2, y2);
        }
        else ++cnt;
        ++tot;
    }
    cout<<"    finish. successful: "<<cnt<<" / "<<tot<<endl;
}

void go3() {
    mt19937 gen((unsigned)time(0));
    penalty=cal_penalty();
    uniform_int_distribution<int> distr(0, 1023);

    int tot=0, cnt=0;
    while(1) {
        //assert(penalty==cal_penalty());

        int i=distr(gen), j=distr(gen);
        if(i==j) continue;

        static int tmp[1024];
        memcpy(tmp, ans, sizeof(ans));
        if(i<j) {
            int ai=ans[i];
            memmove(ans, ans+1, sizeof(ans[0])*(j-i));
            ans[j]=ai;
        } else {
            int ai=ans[i];
            memmove(ans+1, ans, sizeof(ans[0])*(i-j));
            ans[j]=ai;
        }

        LL p2=cal_penalty();
        if(p2<=penalty) {
            ++cnt;
            penalty=p2;
        }
        else {
            memcpy(ans, tmp, sizeof(ans));
        }
        ++tot;
        
        if(tot%100==0) {
            cout<<"   penalty="<<penalty<<" ok="<<cnt<<"/"<<tot<<endl;
            save();
            tot=cnt=0;
        }
    }
}

int main() {
    FILE *f = fopen("i2.in", "r");
    assert(f != nullptr);
    fscanf(f, "%d", &n);
    repn(i, n) {
        repn(j, 1024) fscanf(f, "%d", &data[i][j]);
    }
    fclose(f);

    load();

    bool vis[1024]; fillchar(vis, false);
    repn(i, 1024) {
        assert(!vis[ans[i]]);
        vis[ans[i]]=true;
    }

    while(1)
        go3();

    return 0;
}
