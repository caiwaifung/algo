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
typedef pair<LL,int> PLI;
typedef pair<double,double> PDD;
typedef vector<LL> VL;
typedef vector<int> VI;
typedef vector<PII> VPI;
typedef vector<string> VS;
template<class T> bool setmax(T &_a, T _b) { if(_b>_a) { _a=_b; return true; } return false; }
template<class T> bool setmin(T &_a, T _b) { if(_b<_a) { _a=_b; return true; } return false; }
template<class T> T gcd(T _a, T _b) { return _b==0?_a:gcd(_b,_a%_b); }

const int N=200010;
const int Q=200010;
const int M=int(1e9)+7;
#define time __time

LL pos[N], dir[N];
LL kid[Q], time[Q], answers[Q];

class FindingKids {
    int n, q;

    struct Query {
        LL t, k; int i;
        Query(LL t, LL k, int i) : t(t), k(k), i(i) {}
        bool operator <(const Query &b) const {
            return t<b.t;
        }
    };

    struct Event {
        LL t2; int i, j;
        Event(LL t2, int i, int j) : t2(t2), i(i), j(j) {}
        bool operator <(const Event &b) const {
            return t2<b.t2;
        }
    };

    map<LL,int> lst;
    multiset<Event> events;

    void upt(int i, LL t) {
        if(dir[i]==-1) {
            auto it=lst.find(pos[i]);
            if(it==lst.begin()) return; --it;
            if(dir[it->se]<0) return;
            if(pos[i]-pos[it->se]>t)
                events.insert(Event(pos[i]-pos[it->se], it->se, i));
            //printf("added %d %d\n", it->se,i);
        } else {
            auto it=lst.find(pos[i]);
            ++it; if(it==lst.end()) return;
            if(dir[it->se]>0) return;
            if(pos[it->se]-pos[i]>t)
                events.insert(Event(pos[it->se]-pos[i], i, it->se));
            //printf("added %d %d\n", i,it->se);
        }
    }

    LL solve() {
        repn(i, n) lst[pos[i]]=i;
        events.clear();
        repn(i, n) if(dir[i]==-1) upt(i, 0);

        vector<Query> qs;
        repn(i, q) qs.pb(Query(time[i], kid[i], i));
        sort(all(qs));
        for(const auto &cur: qs) {
            while(!events.empty() && events.begin()->t2<cur.t*2) {
                Event e=*events.begin();
                events.erase(events.begin());
                int i=e.i, j=e.j;
                swap(dir[i], dir[j]); swap(pos[i], pos[j]);
                lst[pos[i]]=i; lst[pos[j]]=j;
                upt(i, e.t2), upt(j, e.t2);
            }
            answers[cur.i]=pos[cur.k]+dir[cur.k]*cur.t;
        }
        //repn(i, q) printf("ans[%d]=%lld\n",i,answers[i]);

    #define absv(x) ((x)>0?(x):-(x))
        LL ans=0; repn(i, q) ans+=absv(answers[i]);
        return ans;
    }
public:
    LL getSum(int _n, int _q, int A, int B, int C) {
        n=_n, q=_q;
        set<LL> pos_set;
        repn(i, n) {
            A=((LL)A*(LL)B+C)%M;
            LL p=A%(M-n+i+1);
            if(pos_set.count(p))
                p=M-n+i;
            pos_set.insert(p);
            pos[i]=p;
            dir[i]=(p%2==0?+1:-1);
        }
        repn(i, q) {
            A=((LL)A*(LL)B+C)%M;
            kid[i]=A%n;
            A=((LL)A*(LL)B+C)%M;
            time[i]=A;
        }

        //repn(i, n) printf("%lld %lld\n", pos[i],dir[i]);

        LL ans=solve();
        return ans;
    }
};

int main() {
    FindingKids t;
    //LL ans=t.getSum(5,4,3,2,1);
    LL ans=t.getSum(5,2,0,1,1);
    cout<<ans<<endl;
    return 0;
}
