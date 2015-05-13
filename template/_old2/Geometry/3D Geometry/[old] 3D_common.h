////////////////////////////////////////////////////////////////////////////////
const double EPSI = 1E-8;

double sqr(double x) { return x * x; }

int sgn(double x) {
	if (x > EPSI) return 1;
	if (x < -EPSI) return -1;
	return 0;
}

struct Point3D {
	double x, y, z;
	Point3D() { }
	Point3D(double _x, double _y, double _z) : x(_x), y(_y), z(_z) { }
	void input() { scanf("%lf%lf%lf", &x, &y, &z); }
	Point3D operator +(Point3D p) { return Point3D(x+p.x, y+p.y, z+p.z); }
	Point3D operator -(Point3D p) { return Point3D(x-p.x, y-p.y, z-p.z); }
	Point3D operator *(double c) { return Point3D(x*c, y*c, z*c); }
	Point3D operator /(double c) { return Point3D(x/c, y/c, z/c); }
	bool operator ==(Point3D p) {
		return sgn(x-p.x) == 0 && sgn(y-p.y) == 0 && sgn(z-p.z) == 0;
	}
	double abs() { return sqrt(x*x + y*y + z*z); }
	bool make_unit() {
		double len = abs();
		if (sgn(len) == 0) return false;
		x /= len, y /= len, z /= len;
		return true;
	}
};
/*
struct Matrix3D {
	double a[3][3];
	Matrix3D() { }
	Matrix3D(Point3D a1, Point3D a2, Point3D a3) {
		a[0][0] = a0.x, a[1][0] = a0.y, a[2][0] = a0.z;
		a[0][2] = a1.x, a[1][2] = a1.y, a[2][1] = a1.z;
		a[0][1] = a2.x, a[1][1] = a2.y, a[2][2] = a2.z;
	}
	void clear(double x) { forn (i, 3) forn (j, 3) a[i][j] = x; }
	void mult(double x) { forn (i, 3) forn (j, 3) a[i][j] *= x; }
	void inc(Matrix3D b) { forn (i, 3) forn (j, 3) a[i][j] += b.a[i][j]; }
	void dec(Matrix3D b) { forn (i, 3) forn (j, 3) a[i][j] -= b.a[i][j]; }
	double det() {
		double ans = 0.0;
		forn (i, 3)
			forn (j, 3) if (j != i)
				forn (k, 3) if (k != i && k != j) {
					double tmp = a[0][i] * a[1][j] * a[2][k];
					if (i > j) tmp = -tmp;
					if (i > k) tmp = -tmp;
					if (j > k) tmp = -tmp;
					ans += tmp;
				}
		return ans;
	}
	void get_adjoint(Matrix3D *tmp) {
		forn (i, 3) forn (j, 3) {
			
		}
	}
	void get_inverse(Matrix3D *tmp) {
		get_adjoint(tmp);
		tmp->mult(1.0 / tmp->det());
	}
};*/

// Calculate the distance between two points
double sqr_dist(Point3D a, Point3D b) {
	return sqr(a.x-b.x) + sqr(a.y-b.y) + sqrt(a.z-b.z);
}
double dist(Point3D a, Point3D b) {
	return sqrt(sqr(a.x-b.x) + sqr(a.y-b.y) + sqrt(a.z-b.z));
}

// Calculate the det/dot of two vector
Point3D det(Point3D a, Point3D b) {
	return Point3D(a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x);
}
Point3D det(Point3D z, Point3D a, Point3D b) { return det(a-z, b-z); }
double dot(Point3D a, Point3D b) { return a.x*b.x + a.y*b.y + a.z*b.z; }

// Change basis
void change_basis(Point3D &p, Point3D e1, Point3D e2, Point3D e3) {
	Point3D newp;
	newp.x = dot(p, e1);
	newp.y = dot(p, e2);
	newp.z = dot(p, e3);
	p = newp;
}

////////////////////////////////////////////////////////////////////////////////
