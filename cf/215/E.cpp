#include <iostream>
#include <cstdio>
using namespace std;

long long m2[99];

bool check(string s, int k) {
	for(int i=0; i+k<s.size(); ++i)
		if(s[i]!=s[i+k])
			return false;
	return true;
}

long long ca(string s, int len) {
	long long ans=0;
	if(s=="") s="1";
	if(s[0]!='1') return 0;
	for(int k=1; k<len; ++k) if(len%k==0)
		if(k<=s.size())
			ans+=check(s, k)-ca(s, k);
		else
			ans+=(m2[k-s.size()])-ca(s, k);
	return ans;
}

long long cal(long long n) {
	if(n==0) return 0;
	string s="";
	while(n>0) {
		s=(char)('0'+n%2)+s;
		n/=2;
	}
	long long ans=0;
	for(int len=1; len<s.size(); ++len) ans+=ca("", len);
	string t="";
	for(int i=0; i<s.size(); ++i) {
		if(s[i]=='1') ans+=ca(t+'0', s.size());
		t+=s[i];
	}
	ans+=ca(s, s.size());
	return ans;
}

int main() {
	m2[0]=1; for(int i=1; i<99; ++i) m2[i]=m2[i-1]*2;
	long long le, ri; cin>>le>>ri;
	long long ans=cal(ri)-cal(le-1); cout<<ans<<endl;
	return 0;
}
