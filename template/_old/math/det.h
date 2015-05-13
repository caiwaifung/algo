int det(int a[][]) {
	int ans=1;
	for(int i=1; i<=num; i++) {
		for(int j=i+1; j<=num; j++)
			while(a[j][i]!=0) {
				int tmp=a[i][i]/a[j][i];
				for(int k=i; k<=num; k++) {
					a[i][k]=(a[i][k]-tmp*a[j][k])%modnum;
					swap(a[i][k], a[j][k]);
				}
				ans=-ans;
			}
		ans=(ans*a[i][i])%MOD;
	}
	return (ans%MOD+MOD)%MOD;
}
