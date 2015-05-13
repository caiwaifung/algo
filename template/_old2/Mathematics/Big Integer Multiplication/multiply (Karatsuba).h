class KaratsubaMul {
	LL *mul(LL *a, LL *b, int n) {
		size_t sz=2*n*sizeof(LL);
		LL *c=(LL*)malloc(sz); memset(c, 0, sz);
		if(n<=16) {
			for(int i=0; i<n; ++i)
				for(int j=0; j<n; ++j)
					c[i+j]+=a[i]*b[j];
			return c;
		}
		LL *x=mul(a, b, n/2);
		LL *y=mul(a+n/2, b+n/2, n/2);
		for(int i=0; i<n/2; ++i) a[i]+=a[i+n/2], b[i]+=b[i+n/2];
		LL *t=mul(a, b, n/2);
		for(int i=0; i<n/2; ++i) a[i]-=a[i+n/2], b[i]-=b[i+n/2];
		for(int i=0; i<n; ++i) {
			c[i]+=x[i]; c[i+n]+=y[i];
			c[i+n/2]+=t[i]-x[i]-y[i];
		}
		free(x), free(y), free(t);
		return c;
	}
public:
	void multiply(LL *a, LL *b, LL *c) {
		int n=1;
		while(n<a[0] || n<b[0]) n*=2;
		LL *x=(LL*)malloc(sizeof(LL)*n);
		LL *y=(LL*)malloc(sizeof(LL)*n);
		for(int i=0; i<n; ++i) x[i]=(i<a[0]?a[i+1]:0);
		for(int i=0; i<n; ++i) y[i]=(i<b[0]?b[i+1]:0);
		LL *z=mul(x, y, n);
		c[0]=2*n;
		for(int i=1; i<=c[0]; ++i) c[i]=z[i-1];
		for(int i=1; i<=c[0]; ++i) c[i+1]+=c[i]/MAXBit, c[i]%=MAXBit;
		while(c[0]>0 && c[c[0]]==0) --c[0];
		free(x), free(y), free(z);
	}
};
