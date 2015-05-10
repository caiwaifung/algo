// 11:41 - 12:27 - fail sample
// 12:41 - passed
#include <cctype>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
using namespace std;

#define forint(i, a, b) for(int i=(int)(a); i<=(int)(b); ++i)
#define forintdown(i, a, b) for(int i=(int)(a); i>=(int)(b); --i)
#define forn(i, n) forint(i, 0, (n)-1)
#define forndown(i, n) forintdown(i, (n)-1, 0)
#define fillchar(a, x) memset(a, x, sizeof(a))
typedef long long LL;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef vector<LL> VL;
typedef vector<PII> VPI;
#define MP make_pair
#define PB push_back
#define fi first
#define se second

struct Vec;
struct Mat {
	int n;
	double a[110][110];
	Mat() : n(0) {}
	Mat(int n) : n(n) {
		fillchar(a, 0);
	}
	void set_row(int i, const Vec &b);
	void print(string s) {
		printf("Matrix %s\n", s.c_str());
		forint(i, 1, n) {
			forint(j, 1, n) printf("%5.3lf ", a[i][j]);
			printf("\n");
		}
	}
};
struct Vec {
	int n;
	double a[110];
	Vec() : n(0) { }
	Vec(int n) : n(n) {
		fillchar(a, 0);
	}
	void print(string s) {
		printf("Vector %s\n", s.c_str());
		forint(j, 1, n) printf("%5.3lf ", a[j]);
		printf("\n");
	}
	void print() {
		printf("( "); forint(j, 1, n) printf("%5.3lf ", a[j]);
		printf(")");
	}
};

void Mat::set_row(int i, const Vec &b) {
	forint(j, 1, n) a[i][j]=b.a[j];
}
Mat operator /(const Mat &a, double b) {
	Mat c=a;
	forint(i, 1, a.n) forint(j, 1, a.n)
		c.a[i][j]/=b;
	return c;
}
Mat operator *(const Mat &a, double b) {
	Mat c=a;
	forint(i, 1, a.n) forint(j, 1, a.n)
		c.a[i][j]*=b;
	return c;
}
Mat operator *(const Mat &a, const Mat &b) {
	Mat c(a.n);
	forint(i, 1, a.n) forint(j, 1, a.n) forint(k, 1, a.n)
		c.a[i][j]+=a.a[i][k]*b.a[k][j];
	return c;
}
Mat operator +(const Mat &a, const Mat &b) {
	Mat c=a;
	forint(i, 1, a.n) forint(j, 1, a.n)
		c.a[i][j]+=b.a[i][j];
	return c;
}
Mat operator -(const Mat &a, const Mat &b) {
	Mat c=a;
	forint(i, 1, a.n) forint(j, 1, a.n)
		c.a[i][j]-=b.a[i][j];
	return c;
}
Vec operator *(const Mat &a, const Vec &b) {
	Vec c(a.n);
	forint(i, 1, a.n) forint(j, 1, a.n)
		c.a[i]+=a.a[i][j]*b.a[j];
	return c;
}
Mat identity(int n) {
	Mat a(n);
	forint(i, 1, n) a.a[i][i]=1.;
	return a;
}
Vec operator *(const Vec &a, double b) {
	Vec c=a;
	forint(i, 1, a.n) c.a[i]*=b;
	return c;
}
Vec operator /(const Vec &a, double b) {
	Vec c=a;
	forint(i, 1, a.n) c.a[i]/=b;
	return c;
}
Vec operator +(const Vec &a, const Vec &b) {
	Vec c=a;
	forint(i, 1, a.n) c.a[i]+=b.a[i];
	return c;
}

Mat B; Vec b;
Mat C; Vec c;

class TorusSailing {
public:

	void get_BC(int n) {
		Vec e[110];
		double t[110], r[110];
		// xi = ei y + ti x1 + ri
		//printf("getBC @1\n");
		e[2]=Vec(n); e[2].a[2]=0.5; t[2]=0.5; r[2]=1.0;
		forint(i, 3, n) {
			e[i]=e[i-1]/2.; e[i].a[i]+=0.5;
			t[i]=t[i-1]/2.;
			r[i]=r[i-1]/2.+1.0;
		}
		// get C
		//printf("getBC @2\n");
		C=Mat(n); c=Vec(n);
		forint(i, 2, n) {
			C.set_row(i, e[i]);
			c.a[i]=r[i];
		}

		// get B
		//printf("getBC @3\n");
		e[1]=e[n]/2.; e[1].a[1]+=0.5;
		t[1]=t[n]/2.;
		r[1]=r[n]/2.+1.0;
		e[1]=e[1]/(1.-t[1]);
		r[1]=r[1]/(1.-t[1]);
		forint(i, 2, n) {
			e[i]=e[i]+(e[1]*t[i]);
			r[i]=r[i]+(r[1]*t[i]);
		}
		B=Mat(n); b=Vec(n);
		forint(i, 1, n) {
			B.set_row(i, e[i]);
			b.a[i]=r[i];
		}
	}

	void cal(const Mat &A, const Vec &a, int n, Mat &B, Vec &b) {
		// B = A^n
		// b = (A^{n-1}+...+I) a
		B=identity(A.n);
		Mat P(A.n);
		forintdown(i, 10, 0) {
			P=P*B+P;
			B=B*B;
			if(n&(1<<i)) {
				P=P*A+identity(A.n);
				B=B*A;
			}
		}
		b=P*a;
	}

	Vec solve(Mat A, Vec b) {
		// solve A x = b
		int n=A.n;
		forint(i, 1, n) {
			forint(j, i+1, n) if(abs(A.a[j][i])>abs(A.a[i][i])) {
				swap(b.a[j], b.a[i]);
				forint(k, i, n) swap(A.a[j][k], A.a[i][k]);
			}
			if(abs(A.a[i][i])<1e-9) {
				printf("error while solving!\n");
				return Vec();
			}
			forint(j, i+1, n) {
				double t=A.a[j][i]/A.a[i][i];
				forint(k, i, n)
					A.a[j][k]-=A.a[i][k]*t;
				b.a[j]-=b.a[i]*t;
			}
		}
		Vec x(n);
		forintdown(i, n, 1) {
			x.a[i]=b.a[i]/A.a[i][i];
			forint(j, 1, i-1)
				b.a[j]-=A.a[j][i]*x.a[i];
		}
		return x;
	}

	double expectedTime(int N, int M, int goalX, int goalY) {
		get_BC(M);
		//B.print("B"); b.print("b"); printf("\n");
		//C.print("C"); c.print("c"); printf("\n");

		//printf("@1\n");

		Mat P; Vec p;
		cal(B, b, N-1, P, p);
		//P.print("P"); p.print("p"); printf("\n");
		//printf("@2\n");

		Mat Q=identity(P.n)-C*P;
		Vec q=C*p+c;
		//printf("@3\n");

		Vec x=solve(Q, q);
		cal(B, b, goalX, P, p);
		Vec t=P*x+p;
		return t.a[goalY+1];
	}

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 2; int Arg2 = 1; int Arg3 = 1; double Arg4 = 4.0; verify_case(0, Arg4, expectedTime(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 3; int Arg2 = 0; int Arg3 = 2; double Arg4 = 8.0; verify_case(1, Arg4, expectedTime(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 7; int Arg1 = 10; int Arg2 = 3; int Arg3 = 2; double Arg4 = 51.80060107964039; verify_case(2, Arg4, expectedTime(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 100; int Arg1 = 100; int Arg2 = 99; int Arg3 = 99; double Arg4 = 9992.616372325532; verify_case(3, Arg4, expectedTime(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
	TorusSailing ___test;
	//___test.run_test(0); return 0;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
