#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
using namespace std;

typedef long long int64;
typedef unsigned long long qword;
template <class T> T abs_val(T x) { return x > 0 ? x : -x; }
template <class T> T sqr(T x) { return x*x; }
template <class T> T gcd(T a, T b) { return b == 0 ? a : gcd(b, a%b); }
template <class T> void set_max(T &a, T b) { if (a < b) a = b; }
template <class T> void set_min(T &a, T b) { if (a > b) a = b; }
#define fillchar(a, x) memset(a, x, sizeof(a))
#define movechar(a, b) memmove(b, a, sizeof(a))
#define forn(i, n) for (int i = 0; i < (int)(n); ++ i)
#define forint(i, s, t) for (int i = (int)(s); i <= (int)(t); ++ i)
#define forintdown(i, s, t) for (int i = (int)(s); i >= (int)(t); -- i)
#define forall(it, a) for (typeof(a.begin()) it = a.begin(); it != a.end(); ++ it)

int check(string s) {
	// 1: check
	// 2: Check
	// 0: cHeCk
	if (s.size() == 0)
		return 0;
	int x = (s[0]>='a' && s[0]<='z') ? 1 : 2;
	forint (i, 1, s.size()-1)
		if (s[i]<'a' || s[i]>'z')
			x = 0;
	return x;
}

string solve() {
	string s;
	cin >> s;/*
	
	vector<string> a;
	string cur = "";
	forn (i, s.size())
		if (s[i] == '_')
			a.push_back(cur), cur = "";
		else
			cur += s[i];
	a.push_back(cur);*/
	if (s.find("_") != string::npos) { // C++
		vector<string> a;
		string cur = "";
		forn (i, s.size())
			if (s[i] == '_')
				a.push_back(cur), cur = "";
			else
				cur += s[i];
		a.push_back(cur);
		forn (i, a.size())
			if (check(a[i]) != 1)
				return "Error!";
		cur = a[0];
		forint (i, 1, a.size()-1) {
			a[i][0] = a[i][0] - 'a' + 'A';
			cur += a[i];
		}
		return cur;
	} else {
		vector<string> a;
		string cur = "";
		forn (i, s.size()) {
			if (s[i]>='A' && s[i]<='Z')
				a.push_back(cur), cur = "";
			cur += s[i];
		}
		a.push_back(cur);
		if (check(a[0]) != 1) return "Error!";
		forint (i, 1, a.size()-1) {
			if (check(a[i]) != 2) return "Error!";
			a[i][0] = a[i][0] - 'A' + 'a';
		}
		cur = a[0];
		forint (i, 1, a.size()-1)
			cur += "_" + a[i];
		return cur;
	}
}

int main() {
	cout << solve() << endl;
	return 0;
}
