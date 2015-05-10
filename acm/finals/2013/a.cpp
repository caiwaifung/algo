// 11:03 - 11:13 - ac
#include <cstring>
#include <iostream>
#include <cstdio>
using namespace std;

bool g[26*2][26*2];
int c[26*2];
int n;
bool found;

void dfs(int x) {
	c[x]=-1;
	for(int y=0; y<26*2; ++y) {
		if(!g[x][y]) continue;
		if(c[y]==1) continue;
		if(c[y]<0) found=true;
		if(c[y]==0) dfs(y);
	}
	c[x]=1;
}

int main() {
	while(1) {
	memset(g, false, sizeof(g));
	if(EOF==scanf("%d", &n)) break;
	while(n--) {
		char s[99];
		scanf("%s", s);
		for(int i=0; i<4; ++i)
			for(int j=0; j<4; ++j)
				if(i!=j) {
					if(s[i*2]=='0') continue;
					if(s[j*2]=='0') continue;
					int x=int(s[i*2]-'A')*2+(s[i*2+1]=='+');
					int y=int(s[j*2]-'A')*2+(s[j*2+1]=='-');
					g[x][y]=true;
				}
	}
	found=false;
	memset(c, 0, sizeof(c));
	for(int i=0; i<26*2; ++i)
		if(c[i]==0)
			dfs(i);
	if(found) printf("unbounded\n"); else printf("bounded\n");
	}
	return 0;
}
