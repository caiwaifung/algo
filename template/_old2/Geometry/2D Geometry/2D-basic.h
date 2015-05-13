// Rotate a vector
Point rotate(Point p, double sinA, double cosA) {
	return Point(p.x*cosA-p.y*sinA, p.x*sinA+p.y*cosA);
}
// Distance between point and segment
double dis_ps(Point p, Point s, Point t) {
	if(dot(s,p,t)>0 && dot(t,p,s)>0)
		return fabs(mult(p,s,t)) / dis(s,t);
	return min(dis(p,s), dis(p,t));
}
// Projective point & reflected point
Point project_point(Point p, Point p1, Point p2) {
	double d=dis(p1, p2);
	double s=mult(p1, p2, p);
	return p + Point(p2.y-p1.y, p1.x-p2.x)*s/d;
}
Point reflect_point(Point p, Point p1, Point p2) {
	Point p3=project_point(p, p1, p2);
	return p3+p3-p;
}
// Segments
bool on_segment(Point p, Point s, Point t) {
	return sgn(mult(p,s,t))==0 && sgn(dot(p,s,t))<=0;

}
bool seg_cross_seg(Point a, Point b, Point p, Point q) {
	if(sgn(mult(a,b,p))*sgn(mult(a,b,q))>0) return false;
	if(sgn(mult(p,q,a))*sgn(mult(p,q,b))>0) return false;
	return true;
}
// Lines
Line move_line(Line l, double d) {
	return Line(l.a, l.b, l.c+d*sqrt(l.a*l.a+l.b*l.b));
}
Line parallel(Line a, Line b) {
	return sgn(a.b*b.a-a.a*b.b)==0;
}
// Convex
VP compute_convex(VP a) {
	sort(a.begin(), a.end()); // sort as x then y
	VP b;
	forn(i, a.size()) {
		while(b.size()>=2 && sgn(mult(b[b.size()-2],b.back(),a[i]))<=0)
			b.pop_back();
		b.PB(a[i]);
	}
	unsigned t=b.size();
	forndown(i, a.size()) {
		while(b.size()>t && sgn(mult(b[b.size()-2],b.back(),a[i]))<=0)
			b.pop_back();
		b.PB(a[i]);
	}
	b.pop_back();
	return b;
}
bool point_in_convex_S(Point a, VP p) { // strictly inside
	int s=sgn(mult(a, p.back(), p[0]));
	if(s==0) return false;
	forint(i, 1, p.size()-1)
		if(sgn(mult(a, p[i-1], p[i]))!=s)
			return false;
	return true;
}
bool segment_cross_convex_S(Point a, Point b, VP p) { // strictly
	if(point_in_convex_S(a, p)) return true;
	if(point_in_convex_S(b, p)) return true;
	if(point_in_convex_S((a+b)/2, p)) return true;
	forn(i, p.size())
		if(seg_cross_seg_S(a, b, p[i], p[(i+1)%p.size()]))
			return true;
	forn(i, p.size())
		if(point_on_segment_S(p[i], a, b))
			return true;
	return false;
}

