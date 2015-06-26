#include <algorithm>
#include <complex>
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

int nnn=0;

namespace FFT {
    typedef complex<double> Complex;
    typedef double Real;
    const int N=66666;

    /*
    void fft(Complex *a, Complex *b, int n, bool inv) {//int n, cplx a[], bool inv=false) {
        static bool visited=false;
        static Complex uroot[N];
        if(!visited) {
            visited=true;
            for(int i=0; i<N; i++) uroot[i] = exp(2 * acos(-1) * i / N * Complex(0,1));
        }
        // double theta = 2 * PI / n;
        int lv = N / n;
        for (int m = n; m >= 2; m >>= 1) {
            int mh = m >> 1;
            for (int i = 0; i < mh; i++) {
                Complex w = uroot[i * lv];
                if(inv) w = conj(w);
                for (int j = i; j < n; j += m) {
                    int k = j + mh;
                    Complex x = a[j] - a[k];
                    a[j] += a[k];
                    a[k] = w * x;
                }
            }
            // theta *= 2;
            lv *= 2;
        }
        int i = 0;
        for (int j = 1; j < n - 1; j++) {
            for (int k = n >> 1; k > (i ^= k); k >>= 1);
            if (j < i) swap(a[i], a[j]);
        }
        memmove(b, a, sizeof(double)*n);
    }
    */

    static void fft(Complex *a, Complex *b, int n, bool inv) {
        double arg=acos(-1.0);
        for(int t=n/2; t>=1; t/=2) {
            Complex w(cos(arg), (inv?sin(arg):-sin(arg)));
            Complex p(1.0, 0.0);
            for(int j=0; j<n/2; j+=t, p*=w)
                for(int i=0; i<t; ++i) {
                    Complex u=a[i+j*2];
                    Complex v=p*a[i+t+j*2];
                    b[i+j]=u+v;
                    b[i+j+n/2]=u-v;
                }
            memcpy(a, b, sizeof(Complex)*n);
            arg/=2;
        }
    }
    static void convolve(const Real *a, int na, const Real *b, int nb, Real *c, int nc) {
        na=min(na, nc);
        nb=min(nb, nc);
        if(na*nb<100) {
            for(int i=0; i<na; ++i)
                for(int j=0; j<nb; ++j) {
                    if(i+j>=nc) break;
                    c[i+j]+=a[i]*b[j];
                }
            return;
        }
        int n=1; 
        while(n<na+nb) n*=2;
        static Complex x[N], y[N], z[N], t[N];
        for(int i=0; i<n; ++i) x[i]=Complex(i<na?a[i]:0., 0.);
        for(int i=0; i<n; ++i) y[i]=Complex(i<nb?b[i]:0., 0.);
        fft(x, z, n, false);
        fft(y, t, n, false);
        for(int i=0; i<n; ++i) t[i]=t[i]*z[i];
        fft(t, z, n, true);
        for(int i=0; i<min(nc, n); ++i) c[i]+=(Real)real(z[i])/(Real)n;
    }
    static Complex *pre_calc(const Real *b, int nb, int n) {
        static Complex x[N];
        Complex *y=new Complex[n];
        for(int i=0; i<n; ++i) x[i]=Complex(i<nb?b[i]:0., 0.);
        fft(x, y, n, false);
        return y;
    }
    static void fast_convolve(const Real *a, int na, const Real *b, int nb, const Complex *bdata, Real *c, int nc, int n) {
        na=min(na, nc);
        nb=min(nb, nc);
        if(na*nb<100) {
            for(int i=0; i<na; ++i)
                for(int j=0; j<nb; ++j) {
                    if(i+j>=nc) break;
                    c[i+j]+=a[i]*b[j];
                }
            return;
        }
        assert(n>=na+nb);
        static Complex x[N], y[N];
        for(int i=0; i<n; ++i) x[i]=Complex(i<na?a[i]:0., 0.);
        fft(x, y, n, false);
        for(int i=0; i<n; ++i) y[i]=y[i]*bdata[i];
        fft(y, x, n, true);
        for(int i=0; i<min(nc, n); ++i) c[i]+=(Real)real(x[i])/(Real)n;
    }
};

template<size_t N> class OnlineConv {
    // function: 
    //   compute c = conv(a, b), length = n
    //   give a[i+1] after return c[i]
    double a[N], b[N], c[N];
    FFT::Complex *bdata[N];
    int n, cur_index;
public:
    void init(double *p, int _n) {
        n=_n; cur_index=0;
        memmove(b, p, sizeof(double)*n);
        fillchar(a, 0); fillchar(c, 0);
        for(int k=1; k<=n; k<<=1) {
            int pos=k-1, len=min(k, n-pos);
            bdata[k-1]=FFT::pre_calc(b+pos, len, k*2);
        }
    }
    double push(double cur) { // given a[i], return c[i]
        int i=cur_index++; 
        a[i]=cur;
        for(int k=1; (i+1)%k==0; k<<=1) {
            int p1=i-k+1, l1=k;
            int p2=k-1, l2=min(k, n-p2);
            if(p1+p2<n) {
                FFT::fast_convolve(a+p1, l1, b+p2, l2, bdata[p2], c+p1+p2, n-(p1+p2), k*2);
            }
                //FFT::convolve(a+x1, y1-x1+1, b+x2, y2-x2+1, c+x1+x2, n-(x1+x2));
        }
        return c[i];
    }
};

const int MAXN=52;
const int MAXM=102;
const int MAXT=20010;

int ea[MAXM], eb[MAXM], ec[MAXM];
double p[MAXM][MAXT], sp[MAXM][MAXT];
int mincost[MAXN];
int n, m, t, x;

void init() {
    scanf("%d%d%d%d", &n,&m,&t,&x);
    static int g[MAXN][MAXN];
    fillchar(g, 50);
    rep(i, 1, n) g[i][i]=0;
    rep(i, 1, m) {
        scanf("%d%d%d", &ea[i],&eb[i],&ec[i]);
        rep(j, 1, t) {
            int tmp; scanf("%d", &tmp);
            p[i][j]=double(tmp)/100000.;
        }
        sp[i][t+1]=0;
        irep(j, t, 1) sp[i][j]=p[i][j]+sp[i][j+1];
        setmin(g[ea[i]][eb[i]], ec[i]);
    }
    rep(k, 1, n) rep(i, 1, n) rep(j, 1, n)
        setmin(g[i][j], g[i][k]+g[k][j]);
    rep(i, 1, n) mincost[i]=g[i][n];
}

OnlineConv<MAXT> conv[MAXM];
double f[MAXN][MAXT];

void solve() {
    rep(i, 1, m) {
        conv[i].init(p[i]+1, t);
    }
    rep(i, 1, n) {
        f[i][0]=mincost[i]+(i!=n?x:0);
        rep(j, 1, t) f[i][j]=1e50;
    }
    rep(cur, 1, t) {
        rep(i, 1, n) setmin(f[i][cur], f[i][cur-1]);
        rep(i, 1, m) {
            int u=ea[i], v=eb[i], w=ec[i];
            double tmp=0;
            //rep(k, 1, cur) tmp+=p[i][k]*f[v][cur-k];
            tmp+=conv[i].push(f[v][cur-1]);
            tmp+=sp[i][cur+1]*(mincost[v]+x);
            tmp+=w;
            setmin(f[u][cur], tmp);
        }
    }
    double ans=f[1][t];
    //rep(i, 0, t) setmin(ans, f[1][i]);
    //rep(j, 1, n) rep(i, 0, t) printf("f[%d][%d]=%.9lf\n",j,i,f[j][i]);
    printf("%.9lf\n", ans);
}

int main() {
    init();
    solve();
    return 0;
}
