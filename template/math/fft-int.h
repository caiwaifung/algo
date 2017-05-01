const int MOD = 998244353;
const int GN = MOD - 1;
const int G = 3;

void fft(int* a, int n, bool is_inv) {
    static VI b;
    if(sz(b) < n) b.resize(n);

    for(int t = n / 2; t >= 1; t /= 2) {
        LL w = powmod(G, GN / n * t, MOD), p = 1;
        if(is_inv) w = powmod(w, MOD - 2, MOD);
        for(int j = 0; j < n / 2; j += t, (p *= w) %= MOD)
            for(int i = 0; i < t; ++i) {
                LL u = a[i + j * 2];
                LL v = p * a[i + t + j * 2] % MOD;
                b[i + j] = int(u + v) % MOD;
                b[i + j + n / 2] = int(u + MOD - v) % MOD;
            }
        memcpy(a, &b[0], sizeof(int) * n);
    }
    if(is_inv) {
        LL inv = powmod(n, MOD - 2, MOD);
        repn(i, n) a[i] = int(a[i] * inv % MOD);
    }
}
