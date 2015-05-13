int mu[MAXN];
void precount_mu(int n) {
	memset(mu, 0, sizeof(mu));
	mu[1]=1;
	for(int i=1; i<=n; ++i)
		for(int j=i*2; j<=n; j+=i)
			mu[j]-=mu[i];
}
