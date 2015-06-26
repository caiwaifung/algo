namespace FFT {
    typedef complex<double> Complex;
    typedef double Real;
    const int N=66666;
    void fft(Complex *a, Complex *b, int n, bool inv) {
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
    void convolve(const Real *a, int na, const Real *b, int nb, Real *c, int nc) {
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
    Complex *pre_calc(const Real *b, int nb, int n) {
        static Complex x[N];
        Complex *y=new Complex[n];
        for(int i=0; i<n; ++i) x[i]=Complex(i<nb?b[i]:0., 0.);
        fft(x, y, n, false);
        return y;
    }
    void fast_convolve(const Real *a, int na, const Real *b, int nb, const Complex *bdata, Real *c, int nc, int n) {
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