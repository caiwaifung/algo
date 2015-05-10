// 13:59 - 15:08 wa
// 15:25 -> ac
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <string>
using namespace std;

#define forint(i, a, b) for(int i=int(a); i<=int(b); ++i)

typedef long long LL;
const int MAXLen=1010;
const int MAXN=15;

int s_to_i(string s) {
	int x=0;
	for(size_t i=0; i<s.size(); ++i)
		x=x*10+(s[i]-'0');
	return x;
}


char cmd[MAXLen]; int para[MAXLen];
int matched[MAXLen], stack[MAXLen], top;
int len;

int bnum, bsize, n;

bool init() {
	if(EOF==scanf("%d%d", &bnum,&bsize)) return false;
	--bnum;
	static char buf[9999];
	gets(buf);
	gets(buf);

	vector<string> t;
	len=strlen(buf);
	while(buf[len-1]=='\n' || buf[len-1]=='\r') --len;
	for(int i=0; i<len; ) {
		while(i<len && buf[i]==' ') ++i;
		if(i>=len) break;
		int j=i;
		string s="";
		while(j<len && buf[j]!=' ') s+=buf[j++];
		t.push_back(s);
		i=j;
	}

	len=(int)t.size();
	top=0;
	for(int i=1; i<=len; ++i) {
		cmd[i]=t[i-1][0];
		para[i]=s_to_i(t[i-1].substr(1));
		if(cmd[i]=='R') stack[++top]=i;
		if(cmd[i]=='E') {
			matched[i]=stack[top];
			matched[stack[top]]=i;
			--top;
		}
	}

	//printf("len=%d cmd[1]=%c\n",len,cmd[1]);

	n=0;
	forint(i, 1, len)
		if(cmd[i]=='V')
			n=max(n, para[i]);

	return true;
}

bool ignored[MAXN];
int rn, id[MAXN];

struct Mat {
	int le, ri;
	LL c[MAXN][MAXN];
	Mat() {
		le=ri=-1;
	}
	void append(int i) {
		if(le<0) {
			le=ri=i;
			memset(c, 0, sizeof(c));
		} else {
			++c[i][ri];
			++c[ri][i];
			ri=i;
		}
	}
	friend Mat combine(Mat a, Mat b) {
		if(a.le<0) return b;
		if(b.le<0) return a;
		Mat c;
		forint(i, 1, rn) forint(j, 1, rn)
			c.c[i][j]=a.c[i][j]+b.c[i][j];
		c.c[a.ri][b.le]++;
		c.c[b.le][a.ri]++;
		c.le=a.le, c.ri=b.ri;
		return c;
	}
	friend Mat pow(Mat a, int b) {
		if(a.le<0) return a;
		Mat c;
		forint(i, 1, rn) forint(j, 1, rn)
			c.c[i][j]=a.c[i][j]*b;
		c.c[a.le][a.ri]+=b-1;
		c.c[a.ri][a.le]+=b-1;
		c.le=a.le, c.ri=a.ri;
		return c;
	}
};

Mat get_mat(int le, int ri) {
	Mat m; int _le=le;
	while(le<=ri) {
		if(cmd[le]=='V') {
			if(id[para[le]]>0)
				m.append(id[para[le]]);
			++le;
		} else if(cmd[le]=='R') {
			int s=le+1, t=matched[le]-1;
			Mat b=pow(get_mat(s, t), para[le]);
			m=combine(m, b);
			le=matched[le]+1;
		}
	}
	//printf("m[%d,%d]:\n",_le,ri);
	//forint(i, 1, rn) forint(j, 1, rn) printf("m[%d,%d]=%I64d\n",i,j,m.c[i][j]);
	return m;
}

LL get_base(int le, int ri) {
	LL ans=0;
	while(le<=ri) {
		if(cmd[le]=='V') {
			++ans;
			++le;
		} else if(cmd[le]=='R') {
			int s=le+1, t=matched[le]-1;
			ans+=get_base(s, t)*para[le];
			le=matched[le]+1;
		}
	}
	//printf("base[%d,%d]=%I64d\n",le,ri,ans);
	return ans;
}

LL f[14][1<<13];
int bitcnt[1<<13];

LL dp(Mat m) {
	bitcnt[0]=0;
	forint(i, 1, (1<<rn)-1)
		bitcnt[i]=bitcnt[i-(i&-i)]+1;

	//printf("rn=%d\n", rn);
	//printf("#1 bnum=%d rn=%d\n",bnum,rn);

	memset(f, 50, sizeof(f));
	LL maxval=f[0][0];
	f[0][0]=0;
	forint(cnt, 0, bnum-1) forint(s, 0, (1<<rn)-1) {
		if(f[cnt][s]==maxval) continue;
		int mask=((1<<rn)-1)^s;
		for(int tmp=mask; tmp>0; tmp=(tmp-1)&mask) {
			if(bitcnt[tmp]>bsize) continue;
			//printf("#a\n");
			//printf("cnt=%d s=%d tmp=%d\n",cnt,s,tmp);
			LL cost=0;
			forint(i, 1, rn) if(tmp&(1<<(i-1)))
				forint(j, 1, rn) if(s&(1<<(j-1)))
					cost+=m.c[i][j];
			//printf("#x cnt=%d s=%d tmp=%d\n",cnt,s,tmp);
			f[cnt+1][s|tmp]=min(f[cnt+1][s|tmp], f[cnt][s]+cost);
			//printf("#b\n");
		}
	}
	//printf("#2\n");
	LL ans=1LL<<60;
	forint(i, 0, bnum) ans=min(ans, f[i][(1<<rn)-1]);
	if(m.le>0) ++ans;
	//cout<<ans<<endl;
	return ans;
}

void solve() {
	LL base=get_base(1, len);
	//cout<<"base="<<base<<endl;
	LL ans=1LL<<60;
	forint(st, 0, (1<<n)-1) {
		int cnt=0;
		rn=0;
		forint(i, 1, n) if(st&(1<<(i-1))) {
			id[i]=-1;
			++cnt;
		} else {
			id[i]=++rn;
		}
		if(cnt!=min(n, bsize))
			continue;
		Mat m=get_mat(1, len);
	//printf("-------------------------st=%d\n",st);
		ans=min(ans, dp(m));
	}
	ans+=base;
	cout<<ans<<endl;
}

int main() {
	while(init()) solve();
	return 0;
}
