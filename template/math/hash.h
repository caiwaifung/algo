class Hash {
public:
    static void init(int n) {
        const auto pow = [](LL a, LL b, LL mod) {
            LL r = 1;
            for(; b > 0; b >>= 1, a = a * a % mod) {
                if(b & 1) r = r * a % mod;
            }
            return r;
        };
        p1.resize(n + 1), ip1.resize(n + 1);
        p2.resize(n + 1), ip2.resize(n + 1);
        p1[0] = p2[0] = 1;
        rep(i, 1, n) {
            p1[i] = p1[i - 1] * P1 % M1;
            p2[i] = p2[i - 1] * P2 % M2;
        }
        ip1[n] = pow(p1[n], M1 - 2, M1);
        ip2[n] = pow(p2[n], M2 - 2, M2);
        irep(i, n, 1) {
            ip1[i - 1] = ip1[i] * P1 % M1;
            ip2[i - 1] = ip2[i] * P2 % M2;
        }
    }

    Hash() : Hash(0, 0, 0) {}
    explicit Hash(int ch) : Hash(ch + 1, ch + 1, 1) {}

    bool operator==(const Hash& b) const { return h1 == b.h1 && h2 == b.h2; }
    Hash operator+(const Hash& b) const {
        return Hash(h1 * p1[b.size] + b.h1, h2 * p2[b.size] + b.h2,
                    size + b.size);
    }
    Hash remove_l(const Hash& b) const {
        return Hash(h1 - b.h1 * p1[size - b.size],
                    h2 - b.h2 * p2[size - b.size], size - b.size);
    }
    Hash remove_r(const Hash& b) const {
        return Hash((h1 - b.h1) * ip1[b.size], (h2 - b.h2) * ip2[b.size],
                    size - b.size);
    }

private:
    friend struct hash<Hash>;
    static constexpr LL P1 = 911, M1 = LL(1e9) + 7;
    static constexpr LL P2 = 127, M2 = LL(1e9) + 9;

    Hash(LL h1, LL h2, int size)
        : h1((h1 % M1 + M1) % M1), h2((h2 % M2 + M2) % M2), size(size) {}

    static VL p1, p2, ip1, ip2;
    LL h1, h2;
    int size;
};
VL Hash::p1, Hash::p2, Hash::ip1, Hash::ip2;
namespace std {
template <> struct hash<Hash> {
    size_t operator()(const Hash& h) const { return h.h1 ^ h.h2; }
};
}
