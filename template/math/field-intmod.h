const int MOD = 998244353;

struct IntModField {
    typedef int value_t;
    static value_t root_of_unity(int n, bool is_inv = false) {
        int root = int(powmod(G, GN / n, MOD));
        return is_inv ? inv(root) : root;
    }
    static int add(int a, int b) { return a += b, a < MOD ? a : a - MOD; }
    static int sub(int a, int b) { return a -= b, a >= 0 ? a : a + MOD; }
    static int mul(int a, int b) { return int(a * LL(b) % MOD); }
    static int div(int a, int b) { return mul(a, inv(b)); }

private:
    static constexpr int GN = MOD - 1;
    static constexpr int G = 3;
    static int inv(int a) { return int(powmod(a, MOD - 2, MOD)); }
};
