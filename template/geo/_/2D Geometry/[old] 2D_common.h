const double EPSI = 1E-8;

double sqr(double x) { return x * x; }

int sgn(double x) {
	if (x > EPSI) return 1;
	if (x < -EPSI) return -1;
	return 0;
}

struct Point {
	double x, y;
	Point() { }
	Point(double _x, double _y) : x(_x), y(_y) { }
	void read() { scanf("%lf%lf", &x, &y); }
	Point operator +(Point p) const { return Point(x+p.x, y+p.y); }
	Point operator -(Point p) const { return Point(x-p.x, y-p.y); }
	Point operator *(double c) const { return Point(x*c, y*c); }
	Point operator /(double c) const { return Point(x/c, y/c); }
	bool operator ==(Point p) const {
		return sgn(x-p.x) == 0 && sgn(y-p.y) == 0;
	}
	bool operator <(const Point &p) const {
		return sgn(x-p.x) < 0 || (sgn(x-p.x) == 0 && sgn(y-p.y) < 0);
	}
};

struct Line {
	double a, b, c;
	Line() { }
	Line(double _a, double _b, double _c) : a(_a), b(_b), c(_c) { }
};

// Point -> Line  |  Line -> Point
void points_make_line(Point w, Point z, Line *line) {
	line->a = z.y - w.y;
	line->b = w.x - z.x;
	line->c = -(line->a * w.x + line->b * w.y);
}
bool lines_make_point(Line w, Line z, Point *point) {
	double tmp = (w.a * z.b - w.b * z.a);
	if (sgn(tmp) == 0) return false;
	point->x = (w.b * z.c - w.c * z.b) / tmp;
	point->y = (w.c * z.a - w.a * z.c) / tmp;
	return true;
}

// Calculate the distance between two points
double sqr_dist(Point a, Point b) {	return sqr(a.x-b.x) + sqr(a.y-b.y); }
double dist(Point a, Point b) {	return sqrt(sqr(a.x-b.x) + sqr(a.y-b.y)); }

// Calculate the det/dot of two vector
double mult(Point a, Point b) { return a.x*b.y - a.y*b.x; }
double mult(Point z, Point a, Point b) { return mult(a-z, b-z); }
double dot(Point a, Point b) { return a.x*b.x + a.y*b.y; }
double dot(Point z, Point a, Point b) { return dot(a-z, b-z); }

// Rotate a vector
Point rotate(Point p, double sinA, double cosA) {
	return Point(p.x*cosA - p.y*sinA, p.x*sinA + p.y*cosA);
}
Point rotate(Point p, double angle) {
	return rotate(p, sin(angle), cos(angle));
}
