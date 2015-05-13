#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
using namespace std;

bool find_cycle(const vector<string> &roads, vector<int> &belong, int x, int fa, int id) {
	belong[x]=id;
	for(int y=0; y<roads.size(); ++y)
		if(y!=fa && roads[x][y]=='8') {
			if(belong[y]!=-1) return true;
			if(find_cycle(roads, belong, y, x, id)) return true;
		}
	return false;
}
double det(vector<vector<double> > a, int n) {
	double ans=1.0;
	for(int i=0; i<n; ++i) {
		for(int j=i+1; j<n; ++j)
			if(fabs(a[j][i])>1E-8) {
				swap(a[i], a[j]);
				ans=-ans;
				break;
			}
		ans*=a[i][i];
		for(int k=n-1; k>=i; --k)
			a[i][k]/=a[i][i];
		for(int j=0; j<n; ++j)
			if(i!=j)
				for(int k=n-1; k>=i; --k)
					a[j][k]-=a[i][k]*a[j][i];
	}
	return ans;
}
double getProbability(vector<string> roads) {
	int n=roads.size();
	vector<int> belong(n, -1);
	int num=0;
	for(int i=0; i<n; ++i)
		if(belong[i]==-1 && find_cycle(roads, belong, i, -1, num++))
			return 0.0;
			
	vector<vector<double> > p1(num, num);
	vector<vector<double> > p0(num, num);
	for(int i=0; i<num; ++i) for(int j=0; j<num; ++j)
		p0[i][j]=1.0, p1[i][j]=0.0;
	double ans=1.0;
	for(int i=0; i<n; ++i)
		for(int j=0; j<n; ++j)
			if(roads[i][j]!='0') {
				double p=(double)(roads[i][j]-'0')/8.0;
				if(belong[i]==belong[j]) {
					if(roads[i][j]!='8' && i<j) ans*=1.0-p;
				} else {
					double &z0=p0[belong[i]][belong[j]];
					double &z1=p1[belong[i]][belong[j]];
					z1=z1*(1.0-p)+z0*p;
					z0=z0*(1.0-p);
				}
			}
	for(int i=0; i<num; ++i)
		for(int j=0; j<num; ++j)
			if(i!=j) {
				double c0=p0[i][j];
				double c1=p1[i][j];
				if(i<j) ans*=c0;
				p1[i][i]+=c1/c0;
				p1[i][j]=-c1/c0;
			}
	return ans*det(p1, num-1);
}
