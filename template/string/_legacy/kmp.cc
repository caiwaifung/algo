char a[1000100]; int la;
char b[10010]; int lb;
int pre[10010];
int main() {
	scanf("%s%s", b+1, a+1);
	la=strlen(a+1), lb=strlen(b+1);
	pre[1]=0;
	for(int i=2, j=0; i<=lb; ++i) {
		while(j>0 && b[j+1]!=b[i]) j=pre[j];
		if(b[j+1]==b[i]) ++j;
		pre[i]=j;
	}
	int cnt=0;
	for(int i=1, j=0; i<=la; ++i) {
		while(j>0 && b[j+1]!=a[i]) j=pre[j];
		if(b[j+1]==a[i]) ++j;
		if(j==lb) {
			++cnt; j=pre[j];
		}
	}
	printf("%d\n", cnt);
	return 0;
}
