#include <iostream>
#include <string>
using namespace std;

int main() {
	int n, m, l, r;
	for(int cs=1; cin>>n>>m>>l>>r; ++cs) {
		cout<<"Case "<<cs<<":"<<endl;
		string s="a";
		for(int cur=1; cur<=r; ++cur) {
			if(cur>=l) cout<<s<<endl;
			int t=s.size();
			while(s.size()<n) s+=s[s.size()%t];
			while(s[s.size()-1]==char('a'+m-1)) s.erase(s.size()-1);
			s[s.size()-1]++;
		}
	}
	return 0;
}
