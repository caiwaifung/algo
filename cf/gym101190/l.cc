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

const int L=2100;
const int N=500;

int p[N], pw[N], n;

void list_primes() {
    vector<bool> a(L, true);
    n=0;
    replr(i, 2, L) {
        if(a[i]) {
            p[n++]=i;
            for(int j=i*2; j<L; j+=i) {
                a[j]=false;
            }
        }
    }
    repn(i, n) {
        int w=0;
        for(int y=p[i]; y>0; y/=10) {
            ++w;
        }
        pw[i]=max(1, w);
    }
}

LL f[N][L], cnt[N][L];

void go(int i, int s, VI* cur, LL cur_len, LL l, LL r) {
    //cout<<i<<" "<<s<<" "<<*cur<<" "<<cur_len<<" "<<l<<" "<<r<<endl;
    if(s==0) {
        ostringstream os;
        os<<"[";
        bool first=true;
        for(int x: *cur) {
            if(!first) os<<", ";
            first=false;
            os<<x;
        }
        os<<"], ";
        cout<<os.str().substr(l, r-l);
        return;
    }
    LL num=f[i][s]+cnt[i][s]*cur_len;
    LL num1=f[i+1][s-p[i]]+cnt[i+1][s-p[i]]*(cur_len+pw[i]+2);
    LL num2=f[i+1][s]+cnt[i+1][s]*(cur_len);
    //cout<<i<<" "<<s<<" "<<num<<" "<<num1<<" "<<num2<<endl;
    assert(num==num1+num2);
    assert(l>=0 && l<r && r<=num);

    LL begin=l, end=min(r, num1);
    if(begin<end) {
        cur->pb(p[i]);
        go(i+1, s-p[i], cur, cur_len+pw[i]+2, begin, end);
        cur->pop_back();
    }
    l=max(0ll, l-num1), r-=num1;
    if(l<r) {
        go(i+1, s, cur, cur_len, l, r);
    }
}

int main() {
    freopen("list.in", "r", stdin);
    freopen("list.out", "w", stdout);
    list_primes();

    fillchar(f, 0), fillchar(cnt, 0);
    cnt[n][0]=1;
    irepn(i, n) repn(j, L) {
        f[i][j]+=f[i+1][j];
        cnt[i][j]+=cnt[i+1][j];
        if(j+p[i]<L) {
            f[i][j+p[i]]+=f[i+1][j]+cnt[i+1][j]*(pw[i]+2);
            cnt[i][j+p[i]]+=cnt[i+1][j];
        }
    }

    LL l, r; cin>>l>>r; --l;
    replr(j, 1, L) {
        LL num=f[0][j]+cnt[0][j]*2;
        LL begin=max(0ll, l), end=min(num, r);
        if(begin<end) {
            VI cur;
            go(0, j, &cur, 2, begin, end);
        }
        l-=num, r-=num;
    }
    assert(r<=0);
    cout<<endl;

    return 0;
}
