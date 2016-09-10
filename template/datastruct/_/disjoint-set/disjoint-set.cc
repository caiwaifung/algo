class DisjointSet {
	std::vector<int> f;
public:
	DisjointSet() { }
	DisjointSet(int n) : f(n, -1) { }
	int find(int x) { return f[x]<0 ? x : f[x]=find(f[x]); }
	void unite(int x, int y) { x=find(x), y=find(y); if(x!=y) f[x]=y; }
};
