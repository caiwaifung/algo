#include<stdio.h>
#include<string.h>

int g[200][200],lx[200],ly[200],lnk[200];
bool x[200],y[200];
int n;

void init()
{
    int i,j;
    scanf("%d",&n);
    for (i=1;i<=n;i++)
        for (j=1;j<=n;j++)
            scanf("%d",&g[i][j]);
}    

bool find(int u)
{
    int i;
    x[u]=true;
    for (i=1;i<=n;i++)
        if ((lx[u]+ly[i]==g[u][i])&&(!y[i]))
        {
            y[i]=true;
            if ((lnk[i]==0)||(find(lnk[i])))
            {
                lnk[i]=u;return true;
            }    
        }    
    return false;
}    

void solve()
{
    int i,j,k,minv;
    memset(lnk,0,sizeof(lnk));
    for (i=1;i<=n;i++)
    {
        lx[i]=0;ly[i]=0;
        for (j=1;j<=n;j++)
            if (g[i][j]>lx[i])lx[i]=g[i][j];
    }   
    for (k=1;k<=n;k++) while (1)
    {
        memset(x,0,sizeof(x));memset(y,0,sizeof(y));
        if (find(k))break;
        minv=2147483647;
        for (i=1;i<=n;i++)if(x[i])
            for (j=1;j<=n;j++)if(!y[j])
                if (lx[i]+ly[j]-g[i][j]<minv)
                    minv=lx[i]+ly[j]-g[i][j];
        for (i=1;i<=n;i++)
            if (x[i])
                lx[i]-=minv;
        for (i=0;i<=n;i++)
            if (y[i])
                ly[i]+=minv;
    }    
    int ans=0;
    for (i=1;i<=n;i++)
        for (j=1;j<=n;j++)
           if (i!=lnk[j])
             ans+=g[i][j];
    printf("%d",ans); 
}   

int main()
{
    init();
    solve();
    return 0;
}    
 
