#include <message.h>
#include <johnny.h>
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

int num, id;
int n;
int pre[20010];


int chain[20010];

void find_chain() {
    int len=1;
    chain[0]=0;
    forint(i, 1, n-1) {
        if(IsBetter(i, chain[0])) {
            memmove(chain+1, chain, sizeof(int)*len);
            chain[0]=i;
            ++len;
            continue;
        }
        if(IsBetter(chain[len-1], i)) {
            chain[len++]=i; continue;
        }
        int le=0, ri=len-1;
        while(le+1<ri) {
            int mid=(le+ri)/2;
            if(IsBetter(chain[mid], i))
                le=mid;
            else
                ri=mid;
        }
        memmove(chain+ri+1, chain+ri, sizeof(int)*(len-ri));
        chain[ri]=i;
        ++len;
    }
}


void find_pre(int s, int t) {
    for(int i=s; i<t; ++i) {
        pre[i]=i;
        forn(j, n) if(IsBetter(chain[i], chain[j]))
            setmin(pre[i], j);
    }
}

bool vis[20010];

void go() {
    fillchar(vis, false);
    queue<int> que;
    vis[n-1]=true, que.push(n-1);
    while(!que.empty()) {
        int i=que.front(); que.pop();
        if(i+1<n && !vis[i+1])
            vis[i+1]=true, que.push(i+1);
        if(pre[i]<i && !vis[pre[i]])
            vis[pre[i]]=true, que.push(pre[i]);
    }
    int ans=0;
    forn(i, n) if(vis[i]) ++ans;
    printf("%d\n", n-ans);
}

void solve() {
    n=(int)NumberOfCards();
    int each=(n-1)/num+1;
    int s=each*id, t=min(each*(id+1), n);

    find_chain();
    find_pre(s, t);
    //

    if(id>0) {
        PutInt(0, t-s);
        for(int i=s; i<t; ++i) {
            PutInt(0, pre[i]);
        }
        Send(0);
        return;
    }
    // now we are 0
    forint(i, 1, num-1) {
        Receive(i);
        int cnt=GetInt(i);
        if(cnt<0) cnt=0;
        forn(i, cnt) {
            pre[t++]=GetInt(i);
        }
    }
    // final
    go();
}

int main() {
    num=NumberOfNodes(), id=MyNodeId();
    solve();
    return 0;
}
