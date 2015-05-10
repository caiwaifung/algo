#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

long long gao(long long x){
    if(!x) return 0;
       long long ret=0;
	    int flag[64]={};
	        for(int i=2;i<64;i++){
		        int u=1-flag[i];
			        for(int j=i;j<64;j+=i) flag[j]+=u;
				        for(int j=1;j<64;j++){
					            long long lo=1ll<<(j-1),c=1;
						                for(int k=1;k<i;k++) c=(c<<j)+1;
								            long long hi=min((1ll<<j)-1,x/c);
									                if(lo<=hi) ret+=(hi-lo+1)*u;
											        }
												    }
												        return ret;
													}
int main() {
	long long l, r; cin>>l>>r; cout<<gao(r)-gao(l-1)<<endl; return 0;
}
