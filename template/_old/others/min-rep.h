A[1..n]; A[n+i]=A[i];
i=1, j=2, k=0, t=0;
while(j<=n) {
	k=0;
	while(a[i+k]==a[j+k]) ++k;
	if(a[i+k]>a[j+k])
		i=i+k+1;
	else
		j=j+k+1;
	if(i==j) ++j;
	if(i>j) swap(i, j);
}
