// Miller-Rabin prime test
bool primetest(LL n) {
	int b[]={2, 3, 5, 7, 11,
		13, 17, 19, 23, 29,
		31, 37};
	bool flag=true;
	for(int i=0; flag && i<12 && b[i]<n; ++i) {
		LL t=n-1; int s=0;
		while(t%2==0) t/=2, ++s;
		LL res=power(b[i], t, n);
		if(res==1 || res==n-1) continue;
		for(flag=false; s>0; --s)
			if((res=mul_mod(res, res, n)) == n-1)
				flag=true;
	}
	return flag;
}

// normal factorize
vector<LL> factorize(LL x) {
	vector<LL> p;
	for(LL i=2; i*i<=x; ++i)
		while(x%i==0)
			p.push_back(i), x/=i;
	if(x>1) p.push_back(x);
	return p;
}

// return factor of n, if fail return n
LL pollard_rho(LL n, LL c) { 
	LL x, y, d, s, t;
	for(x=y=rand()%(n-1)+1, d=1, s=1, t=2; d==1; ) {
		x=(mul_mod(x,x,n)+c)%n;
		d=gcd(absval(x-y), n);
		if(++s==t) y=x, t<<=1;
	}
	return d;
}

// fast factorize
vector<LL> factorize(LL n) {
	vector<LL> p;
	while(n>1)
		if(primetest(n))
			p.push_back(n), n=1;
		else {
			LL d=n; while(d==n) d=pollard_rho(n, rand()%(n-1)+1);
			p.push_back(d), n/=d;
		}
	return p;
}
