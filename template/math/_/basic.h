typedef long long LL;

inline LL gcd(LL a, LL b) {
	return b==0 ? a : gcd(b,a%b);
}

inline LL absval(LL x) {
	return x<0 ? -x : x;
}

inline LL mul_mod(LL a, LL b, LL n) {
	LL d=(LL)((long double)a*(long double)b/(long double)n);
	d=a*b-n*d;
	while(d<0) d+=n;
	while(d>=n) d-=n;
	return d;
}

inline LL power(LL a, LL b, LL n) {
	LL x=1;
	for(; b; b>>=1, a=mul_mod(a,a,n))
		if(b&1)	x=mul_mod(x,a,n);
	return x;
}
