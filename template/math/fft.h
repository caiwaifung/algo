template <class Field, class RandomIt>
void fft(RandomIt a, RandomIt a_end, bool is_inv = false) {
    typedef typename Field::value_t value_t;
    const int n = a_end - a;
    static vector<value_t> b;
    if(sz(b) < n) b.resize(n);

    for(int t = n / 2; t >= 1; t /= 2) {
        value_t w = Field::root_of_unity(n / t, is_inv);
        value_t p = 1;
        for(int j = 0; j < n / 2; j += t, p = Field::mul(p, w)) {
            for(int i = 0; i < t; ++i) {
                value_t u = a[i + j * 2];
                value_t v = Field::mul(p, a[i + t + j * 2]);
                b[i + j] = Field::add(u, v);
                b[i + j + n / 2] = Field::sub(u, v);
            }
        }
        copy(b.begin(), b.begin() + n, a);
    }
    if(is_inv) {
        repn(i, n) a[i] = Field::div(a[i], n);
    }
}
