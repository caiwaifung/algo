VI compute_phi(int n) {
    VI phi(n + 1), primes;
    phi[1] = 1;
    rep(i, 2, n) {
        if(phi[i] == 0) {
            phi[i] = i - 1;
            primes.pb(i);
        }
        for(int p : primes) {
            if(p * i > n) break;
            if(i % p == 0) {
                phi[p * i] = phi[i] * p;
            } else {
                phi[p * i] = phi[i] * (p - 1);
            }
        }
    }
    return phi;
}
