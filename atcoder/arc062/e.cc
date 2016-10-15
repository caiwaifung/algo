#include <algorithm>
#include <unordered_map>
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

LL encode(const VI& x) {
    return (LL(x[0])<<30)+(LL(x[1])<<20)+(x[2]<<10)+x[3];
}

VL extend(LL x) {
    VL r;
    repn(i, 4) {
        r.pb(x);
        LL low=x&((1<<10)-1);
        x=(x>>10)+(low<<30);
    }
    return r;
}

int main() {
    int n; scanf("%d", &n);
    vector<VI> a(n, VI(4));
    vector<LL> code(n);
    unordered_map<LL, int> count;
    repn(i, n) {
        repn(j, 4) scanf("%d", &a[i][j]);
        code[i]=encode(a[i]);
        count[code[i]]++;
    }

    LL ans=0;
    repn(i, n) {
        count[code[i]]--;
        replr(j, i+1, n) {
            count[code[j]]--;
            VI tmp=a[j];
            repn(__, 4) {
                VL ws=extend(encode(VI{tmp[0], tmp[3], a[i][3], a[i][2]}));
                VL xs=extend(encode(VI{tmp[3], tmp[2], a[i][0], a[i][3]}));
                VL ys=extend(encode(VI{tmp[2], tmp[1], a[i][1], a[i][0]}));
                VL zs=extend(encode(VI{tmp[1], tmp[0], a[i][2], a[i][1]}));
                //cout<<i<<" "<<j<<" "<<ws<<" "<<xs<<" "<<ys<<" "<<zs<<endl;
                for(LL w: ws) if(count[w]>0) {
                    LL vw=count[w]--;
                    for(LL x: xs) if(count[x]>0) {
                        LL vx=vw*count[x]--;
                        for(LL y: ys) if(count[y]>0) {
                            LL vy=vx*count[y]--;
                            for(LL z: zs) ans+=vy*count[z];
                            count[y]++;
                        }
                        count[x]++;
                    }
                    count[w]++;
                }
                int first=tmp[0]; tmp[0]=tmp[1]; tmp[1]=tmp[2]; tmp[2]=tmp[3]; tmp[3]=first;
            }
            count[code[j]]++;
        }
    }
    cout<<ans<<endl;

    return 0;
}
