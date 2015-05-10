#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;

int N, R;

bool check_enough(int a, int b, int n) {
	while(n<N) {
		++n; a+=b;
		if(a>=R) return true;
		swap(a, b);
	}
	return b>=R;
}

bool check_x(int a, int b, int n, int x) {
	int t=min(N-n, x);
	b+=a*t; n-=t;
	while(n<N) {
		++n; a+=b;
		if(a>R) return false;
		swap(a, b);
	}
	return b<=R;
}

bool check(int a, int b, int n, int x) {
	if(!check_enough(a, b, n)) return false;
	return check_x(a, b, n, x) || check_x(b, a, n, x+1);
}
/*
bool check(int ca, int cb, int cn, int cx) {
	if(!check_enough(ca, cb, cn)) return false;
	int t=min(N-cn, cx);
	if(t==0) return cb==R;
	if(ca>(R-cb)/t) return false;
	cb+=ca*t; cn+=t;
	while(cn<N) {
		++cn;
		ca+=cb; if(ca>R) return false;
		swap(ca, cb);
	}
	return true;
}*/

const int MAXQ=1000*1000+10;

int qa[MAXQ], qb[MAXQ], qn[MAXQ], qt[MAXQ], qx[MAXQ], pre[MAXQ];
int ss, tt;

bool add(int a, int b, int n, int t, int x, int p) {
	if(x<0) return false;
	
	bool flag;
	if(t==0) flag=check(b, a, n, x);
	else flag=check(a, b, n, x);
	if(!flag) return false;
	
	++tt;
	qa[tt]=a, qb[tt]=b; qn[tt]=n; qt[tt]=t; qx[tt]=x; pre[tt]=p;
	if(n==N) return (t==0?a:b)==R;
	return false;
}

bool solve(int limit) {
	ss=tt=0;
	if(add(1, 1, 1, 0, limit, 0)) return true;
	while(ss<tt) {
		++ss;
		int a=qa[ss], b=qb[ss];
		int n=qn[ss], t=qt[ss], x=qx[ss];
		if(add(a+b, b, n+1, 0, x-(t==0), ss)) return true;
		if(add(a, b+a, n+1, 1, x-(t==1), ss)) return true;
	}
	return false;
}

int main() {
	cin>>N>>R;
	int le=0, ri=N, mid;
	while(le<ri)
		if(solve(mid=(le+ri)/2))
			ri=mid;
		else
			le=mid+1;
	if(solve(le)) {
		string s="";
		for(int i=tt; i>0; i=pre[i]) s=(qt[i]==0?'T':'B')+s;
		cout<<le<<endl<<s<<endl;
	} else
		cout<<"IMPOSSIBLE"<<endl;
	return 0;
}
