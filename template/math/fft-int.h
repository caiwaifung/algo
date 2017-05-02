const int MOD = 998244353;
const int GN = MOD - 1;
const int G = 3;

void fft(VI* ptr_a, bool is_inv = false) {
    VI& a = *ptr_a;
    int n = sz(a);
    static VI b;
    if(sz(b) < n) b.resize(n);

    for(int t = n / 2; t >= 1; t /= 2) {
        LL w = powmod(G, GN / n * t, MOD), p = 1;
        if(is_inv) w = powmod(w, MOD - 2, MOD);
        for(int j = 0; j < n / 2; j += t, (p *= w) %= MOD) {
            for(int i = 0; i < t; ++i) {
                LL u = a[i + j * 2];
                LL v = p * a[i + t + j * 2] % MOD;
                b[i + j] = int(u + v) % MOD;
                b[i + j + n / 2] = int(u + MOD - v) % MOD;
            }
        }
        copy(b.begin(), b.begin() + n, a.begin());
    }
    if(is_inv) {
        LL inv = powmod(n, MOD - 2, MOD);
        repn(i, n) a[i] = int(a[i] * inv % MOD);
    }
}
