// Compute K^h(N) % modnum
// h(N)=Catalan(N)=C(2n,n)/(n+1)
#include <iostream>
using namespace std;

const int modnum=1000000123;

class StairsColoring
{
public:
    int p[10], a[10], n;
    
    int mul(int a, int b, int p)
    { 
        return (int)((long long)a*(long long)b%(long long)p);
    }
    
    int pow(int x, int b, int p)
    {
        int ret=1;
        while (b)
        {
            if (b&1) ret=mul(ret, x, p);
            x=mul(x, x, p);
            b/=2;
        }
        return ret;    
    }   
    
    void reduce(int x)
    {
        n=0;
        for (int i=2; i*i<=x; i++)
            while (x%i==0)
            {
                p[++n]=i;
                x/=i;
            }
        if (x>1) p[++n]=x;
    } 
    
    int get(int x, int y) //compute how many y in (x!)
    {
        int ans=0;
        while (x) ans+=(x/=y); 
        return ans;
    }
    
    int fact(int n, int p) //compute (x!)%p ignoring factor p
    {
        if (n==0) return 1;
        int ans=1;
        for (int i=1; i<p; i++) ans=mul(ans, i, p); //(p-1)! 
        ans=pow(ans, n/p, p); //1*..*(p-1)*(p+1)*..*(2p-1)*(2p+1)*..*((n/p)p-1) 
        for (int i=1; i<=n%p; i++) ans=mul(ans, i, p); //((n/p)p+1)*..*n  
        ans=mul(ans, fact(n/p, p), p); //p*2p*3p*...*(n/p)p=(n/p)! (ignoring p)
        return ans;
    }
    
    int inverse(int x, int p) //find y: x*y%p==1
    {
        for (int y=1; ; y++)
            if (mul(x, y, p)==1)
                return y;
    }
    
    int catalan(int n, int p) //Catalan(n)%p
    {
        if (get(2*n, p)-get(n+1, p)-get(n, p)>0) return 0; //if Catalan(n) has p 
        int ans=fact(2*n, p); //(2n)! 
        ans=mul(ans, inverse(fact(n+1, p), p), p); //divided by (n+1)! 
        ans=mul(ans, inverse(fact(n, p), p), p); //divided by n!
        return ans;
    }
    
    int count() //solve the equations
    {
        int ans=0, add=1;
        for (int i=1; i<=n; add*=p[i++])
            while (ans%p[i]!=a[i])
                ans+=add;
        return ans;
    }
    
    int coloringCount(int N, int K)
    {
        reduce(modnum-1);
        for (int i=1; i<=n; i++)
            a[i]=catalan(N, p[i]); 
        int ans=count();
        return pow(K, ans, modnum);
    }    
};
