#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
int main() {
    freopen("D-large.in", "r", stdin);
    freopen("D-large.out", "w", stdout);
    int a[1010];
    int b[1010];
    int n;
    int cs;
    scanf("%d", &cs);
    for(int k=1;k<=cs;k++) {
        scanf("%d",&n);
        for(int i=1; i<=n;i++) scanf("%d", &a[i]);
        memmove(b,a,sizeof(b));sort(b+1,b+n+1);
        int ans=0;for(int i =1;i<=n; i ++)if(a[i]!=b[i])ans++;
        printf("Case #%d: %d.000000\n",k,ans);
    }
    return 0;
}
