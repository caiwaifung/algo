template<size_t N, size_t LogN> class PartitionTree {
	pair<int, int> tmp[N];
	int ind[LogN][N];
	int cl[LogN][N];
	void merge(int d, int le, int ri) {
		if(le==ri) {
			ind[d][le]=tmp[ri].second;
			return;
		}
		int mid=(le+ri)/2;
		merge(d+1, le, mid);
		merge(d+1, mid+1, ri);
		for(int k=le, i=le, j=mid+1, cnt=0; k<=ri; ++k) {
			if(j>ri || (i<=mid && ind[d+1][i]<ind[d+1][j]))
				ind[d][k]=ind[d+1][i++], ++cnt;
			else
				ind[d][k]=ind[d+1][j++];
			cl[d][k]=cnt;
		}
	}
public:
	int a[N];
	int n;
	void build() {
		for(int i=1; i<=n; ++i)
			tmp[i]=make_pair(a[i], i);
		sort(tmp+1, tmp+n+1);
		merge(0, 1, n);
	}
	// return k-th smallest in [x,y]
	int query(int x, int y, int k) { 
		int le=1, ri=n;
		for(int d=0; ; ++d) {
			if(x==y) return ind[d][x];
			int mid=(le+ri)/2;
			int a=(x==le ? 0 : cl[d][x-1]);
			int b=cl[d][y];
			if(k<=b-a) {
				x=le+a, y=le+b-1;
				ri=mid;
			} else {
				x=mid+x-le-a+1, y=mid+y-le-b+1;
				k-=b-a;
				le=mid+1;
			}
		}
	}
};

// Query(x,y,k):
//   return sum{|a_i-x|, x<=i<=y}
//   x is the k-th smallest number in [x,y]
template<size_t N, size_t LogN> class PartitionTree {
	pair<int, int> tmp[N];
	LL sum[LogN][N];
	int ind[LogN][N];
	int cl[LogN][N];
	void merge(int d, int le, int ri) {
		if(le==ri) {
			sum[d][le]=tmp[ri].first;
			ind[d][le]=tmp[ri].second;
			return;
		}
		int mid=(le+ri)/2;
		merge(d+1, le, mid);
		merge(d+1, mid+1, ri);
		for(int k=le, i=le, j=mid+1, cnt=0; k<=ri; ++k) {
			if(j>ri || (i<=mid && ind[d+1][i]<ind[d+1][j]))
				ind[d][k]=ind[d+1][i++], ++cnt;
			else
				ind[d][k]=ind[d+1][j++];
			cl[d][k]=cnt;
			sum[d][k]=(k==le?0:sum[d][k-1])+a[ind[d][k]];
		}
	}
public:
	int a[N];
	int n;
	void build() {
		for(int i=1; i<=n; ++i)
			tmp[i]=make_pair(a[i], i);
		sort(tmp+1, tmp+n+1);
		merge(0, 1, n);
	}
	LL query(int x, int y, int k) { 
		int le=1, ri=n;
		LL c=(k-1)-(y-x+1-k);
		LL ans=0;
		for(int d=0; ; ++d) {
			if(x==y) return ans+c*a[ind[d][x]];
			int mid=(le+ri)/2;
			int l_x=le+(x==le?0:cl[d][x-1]);
			int l_y=le+cl[d][y]-1;
			int r_x=mid+x-l_x+1;
			int r_y=mid+y-l_y;
			if(k<=l_y-l_x+1) {
				if(r_x<=r_y)
					ans+=sum[d+1][r_y]-(r_x==mid+1?0:sum[d+1][r_x-1]);
				x=l_x, y=l_y;
				ri=mid;
			} else {
				if(l_x<=l_y)
					ans-=sum[d+1][l_y]-(l_x==le?0:sum[d+1][l_x-1]);
				x=r_x, y=r_y, k-=l_y-l_x+1;
				le=mid+1;
			}
		}
	}
};
