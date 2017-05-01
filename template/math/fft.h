void fft(Complex *a, int n, bool inv) {
    static VI b;
    if(sz(b) < n) b.resize(n);
    double arg = acos(-1.0);
    for(int t = n / 2; t >= 1; t /= 2) {
        Complex w(cos(arg), (inv ? sin(arg) : -sin(arg)));
        Complex p(1.0, 0.0);
        for(int j = 0; j < n / 2; j += t, p *= w)
            for(int i = 0; i < t; ++i) {
                Complex u = a[i + j * 2];
                Complex v = p * a[i + t + j * 2];
                b[i + j] = u + v;
                b[i + j + n / 2] = u - v;
            }
        memcpy(a, &b[0], sizeof(Complex) * n);
        arg /= 2;
    }
}
