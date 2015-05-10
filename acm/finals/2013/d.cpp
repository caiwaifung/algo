#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
using namespace std;

#define forint(i, a, b) for(int i=(int)(a); i<=(int)(b); ++i)
#define forintdown(i, a, b) for(int i=(int)(a); i>=(int)(b); --i)
#define forn(i, n) forint(i, 0, (n)-1)
#define forndown(i, n) forintdown(i, (n)-1, 0)
#define fillchar(a, x) memset(a, x, sizeof(a))
typedef long long LL;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef vector<LL> VL;
typedef vector<PII> VPI;
#define MP make_pair
#define PB push_back
#define fi first
#define se second

const LL MAXV=(1ULL<<63)-1;
const int MAXN=66;

vector<LL> primes;
vector<int> p_cnt;

bool is_prime(LL x) {
	for(LL y=2; y*y<=x; ++y)
		if(x%y==0)
			return false;
	return true;
}

map<LL, LL> ans;
//vector<LL> nums;
LL C[MAXN][MAXN];

void make_ans(int cur, LL k) {
	LL n=1;
	int s=0;
	forn(i, cur) {
		s+=p_cnt[i];
		LL tmp=C[s][p_cnt[i]];
		if(n>MAXV/tmp)
			return;
		n*=tmp;
	}
	if(ans.find(n)==ans.end())
		ans[n]=k;
	else if(k<ans[n])
		ans[n]=k;
}

void dfs(int cur, int la, LL val) {
	make_ans(cur, val);
	for(int i=1; i<=la; ++i) {
		if(MAXV/primes[cur]<val)
			break;
		val*=primes[cur];
		p_cnt[cur]=i;
		dfs(cur+1, i, val);
	}
}

int main() {
	primes.clear();
	for(LL x=2; primes.size()<MAXN; ++x)
		if(is_prime(x))
			primes.PB(x);
	p_cnt.resize(primes.size());

	forn(i, MAXN) C[i][0]=C[i][i]=1;
	forn(i, MAXN) forint(j, 1, i-1) {
		if(C[i-1][j-1]>MAXV-C[i-1][j])
			C[i][j]=MAXV;
		else
			C[i][j]=C[i-1][j-1]+C[i-1][j];
	}

	ans.clear();
	dfs(0, 99, 1);
	
	LL n;
	while(cin>>n)
		cout<<n<<" "<<ans[n]<<endl;
	return 0;
}
