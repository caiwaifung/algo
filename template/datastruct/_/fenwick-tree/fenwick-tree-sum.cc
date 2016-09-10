template<class T> class FenwickTree {
    std::vector<T> a;
    int n; T v0;
public:
    FenwickTree() { }
    FenwickTree(int _n, T _v) : a(size_t(_n+1), _v), n(_n), v0(_v) { }
    void add(int x, T v) { for(; x<=n; x+=(x&-x)) a[(size_t)x]+=v; }
    T get(int x) const { T r=v0; for(; x>=1; x-=(x&-x)) r+=a[(size_t)x]; return r; }
};
