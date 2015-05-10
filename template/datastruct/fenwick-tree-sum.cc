template<class T> class FenwickTree {
    std::vector<T> a;
    int n; T v0;
public:
    FenwickTree() { }
    FenwickTree(int n, T v) : a(size_t(n+1), v), n(n), v0(v) { }
    void add(int x, T v) { for(; x<=n; x+=(x&-x)) a[(size_t)x]+=v; }
    T get(int x) const { T r=v0; for(; x>=1; x-=(x&-x)) r+=a[(size_t)x]; return r; }
};
