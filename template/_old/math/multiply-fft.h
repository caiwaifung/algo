typedef long long LL;
typedef complex<long double> CD;
class FFTMul {
	void FFT(CD *a, CD *b, int n, bool inv) {
		double arg=acos(-1.0);
		for(int t=n/2; t>=1; t/=2) {
			CD w(cos(arg), (inv?sin(arg):-sin(arg)));
			CD p(1.0, 0.0);
			for(int j=0; j<n/2; j+=t, p*=w)
				for(int i=0; i<t; ++i) {
					CD u=a[i+j*2];
					CD v=p*a[i+t+j*2];
					b[i+j]=u+v;
					b[i+j+n/2]=u-v;
				}
			memmove(a, b, sizeof(CD)*n);
			arg/=2;
		}
	}
public:
	void multiply(LL *a, LL *b, LL *c) {
		int n=1;
		while(n<a[0]+b[0]) n*=2;
		CD *x=(CD*)malloc(sizeof(CD)*n);
		CD *y=(CD*)malloc(sizeof(CD)*n);
		CD *z=(CD*)malloc(sizeof(CD)*n);
		CD *t=(CD*)malloc(sizeof(CD)*n);
		for(int i=0; i<n; ++i) x[i]=CD((double)(i<a[0]?a[i+1]:0),0.0);
		for(int i=0; i<n; ++i) y[i]=CD((double)(i<b[0]?b[i+1]:0),0.0);
		FFT(x, z, n, false);
		FFT(y, t, n, false);
		for(int i=0; i<n; ++i) t[i]=t[i]*z[i];
		FFT(t, z, n, true);
		c[0]=n;
		for(int i=1; i<=c[0]; ++i) c[i]=(LL)(0.5+real(z[i-1])/(double)n);
		for(int i=1; i<=c[0]; ++i) c[i+1]+=c[i]/MAXBit, c[i]%=MAXBit;
		while(c[0]>0 && c[c[0]]==0) --c[0];
		free(x), free(y), free(z), free(t);
	}
};
