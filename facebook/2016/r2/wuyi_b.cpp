F[0][0]=1;
S[0][0]=1;
for(int n=1;n<=N;++n) {
    F[n][0] = q * F[n-1][0];
    F[n][n] = p * F[n-1][n-1];
    for(int k=1;k<n;++k)
        F[n][k] = F[n-1][k-1] * p + q * F[n-1][k];
    S[n][n] = F[n][n];
    for(int k=n-1;k>=0;--k)
        S[n][k] = S[n][k+1]+F[n][k];
}

fill(dp,dp+K-1,0);
for(int i=K;i<=N;++i) {
    dp[i] = 0;
    for(int k=K;k<=i;++k)
        dp[i]=max(dp[i], dp[i-k] + S[k][K]);
}
return dp[N];
