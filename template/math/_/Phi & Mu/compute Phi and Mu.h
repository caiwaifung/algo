// n = p1^k1 * p2^k2 * ... * pm^km
// mu(n)	= (-1)^m		max(ki)=1
// mu(n)	= 0			max(ki)>1
// phi(n)	= (p1-1)p1^(k1-1) * (p2-1)p2^(k2-1) * ...
//		= n*(1-1/p1)*(1-1/p2) ...
int mu[MAXN], phi[MAXN];
int prime[MAXN], prime_cnt;
void precount_mu_phi(int n) {
	memset(phi, 0, sizeof(phi));
	phi[1]=mu[1]=1;
	prime_cnt=0;
	for(int i=2; i<=n; ++i) {
		if(phi[i]==0) {
			prime[++prime_cnt]=i;
			mu[i]=-1;
			phi[i]=i-1;
		}
		for(int k=1; k<=prime_cnt && prime[k]*i<=n; ++k) {
			int j=i*prime[k];
			if(i%prime[k]==0)
				mu[j]=0, phi[j]=phi[i]*prime[k];
			else
				mu[j]=-mu[i], phi[j]=phi[i]*(prime[k]-1);
		}
	}
}
