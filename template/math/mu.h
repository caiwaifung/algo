VI compute_mu(int n) {
    VI mu(n + 1);
    mu[1] = 1;
    rep(i, 1, n) for(int j = i * 2; j <= n; j += i) mu[j] -= mu[i];
    return mu;
}
