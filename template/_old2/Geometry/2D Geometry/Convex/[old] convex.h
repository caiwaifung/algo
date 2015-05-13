Point origin;
bool convex_cmp(const Point &a, const Point &b) {
	int ret = sgn(mult(origin, b, a));
	if (ret == 0)
		ret = sgn(dist(a, origin) - dist(b
}
vector<Point> compute_convex(vector<Point> p) {
	forn (i, p.size()) {
		int tmp = sgn(p[i].x-p[0].x);
		if (tmp == 0) tmp = sgn(p[i].y-p[0].y);
		if (tmp < 0) swap(p[0], p[i]);
	}
	origin = p[0];
	// TODO
}
