////////////////////////////////////////////////////////////////////////////////
int point_in_polygon(Point cp, const vector<Point> &poly) {
	int n = poly.size();
	int wn = 0;
	forn (i, n) {
		if (point_on_segment(cp, poly[i], poly[(i+1)%n]))
			return 1;
		int k = sgn(mult(poly[i], poly[(i+1)%n], cp));
		int d1 = sgn(poly[i].y - cp.y);
		int d2 = sgn(poly[(i+1)%n].y - cp.y);
		if (k > 0 && d1 <= 0 && d2 > 0) ++ wn;
		if (k < 0 && d1 > 0 && d2 <= 0) -- wn;
	}
	return (0 != wn) ? 2 : 0;
}

bool segment_cross_polygon(Point s, Point t, const vector<Point> &poly) {
	int n = poly.size();
	if (point_in_polygon(s, poly) > 0 || point_in_polygon(t, poly) > 0)
		return true;
	forn (i, n)
		if (segment_cross_segment(s, t, poly[i], poly[(i+1)%n]))
			return true;
	return false;
}

////////////////////////////////////////////////////////////////////////////////
