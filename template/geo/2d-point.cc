const double EPS=1e-10;
double sgn(double x) { return x<-EPS ? -1 : x>EPS; }
struct Point {
    double x, y;
    Point() { }
    Point(double x, double y) : x(x), y(y) { }
    Point operator +(const Point &p) const { return Point(x+p.x, y+p.y); }
    Point operator -(const Point &p) const { return Point(x-p.x, y-p.y); }
    Point operator *(double b) const { return Point(x*b, y*b); }
    Point operator /(double b) const { return Point(x/b, y/b); }
    void rotate90() { swap(x, y); x=-x; }
    double len() const { return sqrt(x*x+y*y); }
    void normalize() { *this=*this/len(); }
    friend double mult(Point p1, Point p2) { return p1.x*p2.y-p1.y*p2.x; }
    friend double dot(Point p1, Point p2) { return p1.x*p2.x+p1.y*p2.y; }
    friend double mult(Point p0, Point p1, Point p2) { return mult(p1-p0, p2-p0); }
    friend double dot(Point p0, Point p1, Point p2) { return dot(p1-p0, p2-p0); }
    friend double dist(Point p1, Point p2) { return (p1-p2).len(); }
    double lambda(Point s, Point t) const { // return c: p=s+(t-s)*c
        return dot(s, t, *this)/dot(s, t, t);
    }
};
struct Line {
    double a, b, c;
    Line() { }
    Line(double a, double b, double c) : a(a), b(b), c(c) { }
    Line(Point p1, Point p2) { a=p2.y-p1.y, b=p1.x-p2.x; c=-(p1.x*a+p1.y*b); }
};
