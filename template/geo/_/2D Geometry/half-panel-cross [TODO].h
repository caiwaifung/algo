struct Segment {
	Point s, t;
	double ang;
	Segment() { }
	Segment(Point _s, Point _t) {
		s=_s, t=_t, ang=atan2(t.y-s.y, t.x-s.x);
	}
	bool operator <(const Segment &b) const {
		int tmp = sgn(ang-b.ang);
		if (tmp!=0) return tmp<0;
		return sgn(mult(s, t, b.s))<0;
	}
};
vector<Segment> a;

Point getc(const Segment &x, const Segment &y) {
	Point p;
	Line lx=make_line(x.s, x.t);
	Line ly=make_line(y.s, y.t);
	if(!cross_ll(lx, ly, &p)) printf("error!");
	return p;
}
bool check(const Segment &x, const Segment &y, const Segment &w) {
	return sgn(mult(w.s, w.t, getc(x, y))) > 0;
}
void initialize(Point ld, Point ru) {
	a.clear();
	a.push_back(Segment(ld, Point(ru.x, ld.y)));
	a.push_back(Segment(Point(ru.x, ld.y), ru));
	a.push_back(Segment(ru, Point(ld.x, ru.y)));
	a.push_back(Segment(Point(ld.x, ru.y), ld));
}
void add(Point s, Point t) {
	a.push_back(Segment(s, t));
}
void compute(vector<Point> *convex) {
	vector<Segment> lt, q = a;
	sort(q.begin(), q.end());
	lt.push_back(q[0]);
	forall (x, q)
		if (sgn(x->ang - lt.back().ang) != 0)
			lt.push_back(*x);
	q.resize(lt.size()+100);
	int ss = 0, tt = -1;
	forall (x, lt) {
		while (ss < tt && !check(q[tt], q[tt-1], *x)) -- tt;
		while (ss < tt && !check(q[ss], q[ss+1], *x)) ++ ss;
		q[++ tt] = *x;
	}
	while (ss < tt && !check(q[ss], q[ss+1], q[tt])) ++ ss;
	while (ss < tt && !check(q[tt], q[tt-1], q[ss])) -- tt;
	convex->clear();
	if (tt-ss+1 < 3) return ;
	forint (i, ss, tt)
		convex->push_back(getc(q[i], q[i<tt?i+1:ss]));
}
