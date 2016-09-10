#include <cstdio>
#include <cstring>

const int modnum=10007;
typedef unsigned int matrix[51][51];
typedef unsigned int arr[51];

int trie[100]['Z'+1];
bool danger[100];
int n, len, num;
matrix trans, tmp;

inline void trie_init()
{
    int q[100], sfx[100], x, i, ss, tt;   
    char str[7];               
    char c;
    num=1;
    memset(trie, 0, sizeof(trie));
    memset(danger, 0, sizeof(danger));
    gets(str);
    while (n--)
    {
        gets(str);
        for (x=1, c=str[i=0]; c!='\0'; x=trie[x][c], c=str[++i])
            if (!trie[x][c]) trie[x][c]=++num;
        danger[x]=true;
    }    
    for (ss=0,tt=0,sfx[1]=1, c='A'; c<='Z'; c++)
    {
        if (!trie[1][c]) {trie[1][c]=1; continue;}
        sfx[trie[1][c]]=1;
        q[++tt]=trie[1][c];
    } 
    while (ss<tt)
    {
        x=q[++ss];
        danger[x]=danger[x]||danger[sfx[x]];
        for (c='A'; c<='Z'; c++)
            if (!trie[x][c]) trie[x][c]=trie[sfx[x]][c];
            else {
                sfx[trie[x][c]]=trie[sfx[x]][c];
                q[++tt]=trie[x][c];
            }    
    }       
}    

inline bool init()
{
    int tmp, x, ind[200];
    char c;
    if (scanf("%d%d", &n, &len)==EOF) return false;
    trie_init();
    
    tmp=num;num=0;
    for (x=1; x<=tmp; x++)
        if (!danger[x]) ind[x]=++num;
    
    memset(trans, 0, sizeof(trans));
    for (x=1; x<=tmp; x++)
        if (!danger[x])
            for (c='A'; c<='Z'; c++)
                if (!danger[trie[x][c]])
                    trans[ind[x]][ind[trie[x][c]]]++;
    return true;
}

inline int pow(int a, int b)
{
    int ret;
    for (ret=1; b; b>>=1)
    {
        if (b&1) (ret*=a)%=modnum;
        (a*=a)%=modnum;
    }    
    return ret;
}    

inline void calmul(matrix &a, matrix &b, matrix &c)
{
    int i, j, k;
    unsigned int tmp;
    for (i=1; i<=num; i++)
        for (j=1; j<=num; j++)
        {
            tmp=0;
            for (k=1; k<=num; k++)
                tmp+=a[i][k]*b[k][j];
            c[i][j]=tmp%modnum;
        }     
}

inline void calmul2(arr &a, matrix &b, arr &c)
{
    int i, j;
    memset(c, 0, sizeof(c));
    for (i=1; i<=num; i++)
        for (j=1; j<=num; j++)
            c[j]=(c[j]+a[i]*b[i][j])%modnum;
} 

inline void calpow(matrix &a, int b, matrix &c)
{
    int i, j, k;
    memset(c, 0, sizeof(c));
    for (i=1; i<=num; i++) c[i][i]=1;
    while (b)
    {
        if (b&1)
        {
            calmul(a, c, tmp);
            memmove(c, tmp, sizeof(c));
        }    
        b>>=1;
        if (b)
        {
            calmul(a, a, tmp);
            memmove(a, tmp, sizeof(a));
        }    
    }    
}       

inline void solve()
{
    arr a, c;
    matrix b;
    int i, ans;
    calpow(trans, len, b);
    memset(a, 0, sizeof(a));
    a[1]=1;
    calmul2(a, b, c);
    for (ans=0, i=1; i<=num; i++) (ans+=c[i])%=modnum;
    ans=(pow(26,len)-ans+modnum*2)%modnum;
    printf("%d\n", ans);
}        

int main()
{
    while (init()) solve();
    return 0;
}    