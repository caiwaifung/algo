int min_representation(int a[], int n) {
	int i=1, j=2, k=0;
	while(i<=n && j<=n && k<n) {
		int xi=i+k; if(xi>n) xi-=n;
		int xj=j+k; if(xj>n) xj-=n;
		int tmp=a[xi]-a[xj];
		if(tmp==0) ++k;
		else {
			if(tmp>0) i+=k+1;
				else j+=k+1;
			if(i==j) ++j;
			k=0;
		}
	}
	return min(i, j);
}
