template <class T, T T_ZERO> class TreeArray {
private:
	vector<T> t;
public:
	void initialize(int N) { // Maintain array A[1..N]
		t.resize(N+1);
		forall (x, t) *x = T_ZERO;
	}
	void add(int x, T val) { // A[x] += val
		for (; x < t.size(); x += (x&-x))
			t[x] += val;
	}
	T get(int x) { // return (A[1]+..+A[x])
		T v = T_ZERO;
		for (; x >= 1; x -= (x&-x))
			v += t[x];
		return v;
	}
};
