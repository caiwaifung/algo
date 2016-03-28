#include<bits/stdc++.h>
using namespace std;
const int MAX=3e4+9;
int n,a[MAX];
bool b[MAX];
vector<int> v;
bool ch()
{
    v.clear();
    for (int i=0;i<n;i++) if (!b[i]) v.push_back(a[i]);
    if (v.size()==0) b[n-1]=0;
    if (v.size()<=1) return true;
    for (int j=1;j<v.size();j++) if (v[j]-v[j-1]!=v[1]-v[0]) return false;
    return true;
}
bool check(int i,int j)
{
    memset(b,0,sizeof b);
    int d=a[j]-a[i],p=i;
    b[p]=true;
    for (int pp=p+1;pp<n;pp++)
        if (a[pp]==a[p]+d) 
            p=pp,b[p]=true;
    if (ch()) return true;
    int x=n-1;
    while (!b[x]) x--;
    b[x]=0;
    return ch();
}
void print(){for (int i=0;i<n;i++) if (b[i]) cout<<a[i]<<' '; cout<<'\n'; for (int i=0;i<n;i++) if (!b[i]) cout<<a[i]<<' ';}
int main()
{
    cin>>n;
    for (int i=0;i<n;i++) cin>>a[i];
    if (n==2) cout<<a[0]<<'\n'<<a[1]; else
        if (check(0,1)) print(); else
            if (check(0,2)) print(); else
                if (check(1,2)) print(); else
                    cout<<"No solution\n";
}
