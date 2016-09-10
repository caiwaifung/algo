// function:
//   compute c = conv(a, b), length = n
//   give a[i+1] after return c[i]
template<size_t N> class OnlineConv {
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
            if(p1+p2<n)
                FFT::fast_convolve(a+p1, l1, b+p2, l2, bdata[p2], c+p1+p2, n-(p1+p2), k*2);
        }
        return c[i];
    }
};