template <class Field> class OnlineConvolution {
public:
    typedef typename Field::value_t value_t;

    template <class Iter>
    OnlineConvolution(Iter a, Iter a_end)
        : n(int(a_end - a)), prep(n), r(n * 2) {
        assert((n & (n - 1)) == 0);
        for(int i = 0, j = 1; i < n; i = j, j <<= 1) {
            prep[i].resize((j - i) * 2);
            copy(a + i, a + j, prep[i].begin());
            if(sz(prep[i]) > S) fft<Field>(all(prep[i]));
        }
    }

    value_t add(value_t bi) {
        b.pb(bi);
        while(sz(r) < sz(b) + n) r.resize(sz(r) * 2);
        for(int i = 0, j = 1; i < n; i = j, j <<= 1) {
            const int len = j - i;
            if(len > sz(b)) break;
            if(sz(b) % len == 0) {
                convolute(i, b.end() - len, b.end(),
                          r.begin() + i + sz(b) - len);
            }
        }
        return r[sz(b) - 1];
    }

private:
    template <class Iter, class OutIter>
    void convolute(int i, Iter arr, Iter arr_end, OutIter out) {
        const int len = int(arr_end - arr);
        if(sz(prep[i]) > S) {
            vector<value_t> tmp(sz(prep[i]));
            copy(arr, arr_end, tmp.begin());
            fft<Field>(all(tmp));
            repn(k, sz(tmp)) tmp[k] = Field::mul(tmp[k], prep[i][k]);
            fft<Field>(all(tmp), true);
            repn(k, sz(tmp)) out[k] = Field::add(out[k], tmp[k]);
        } else {
            repn(k, len) repn(j, sz(prep[i]) - k) {
                out[j + k] =
                    Field::add(out[j + k], Field::mul(prep[i][j], arr[k]));
            }
        }
    }

    static constexpr int S = 128;
    const int n;
    vector<vector<value_t>> prep;
    vector<value_t> b, r;
};
