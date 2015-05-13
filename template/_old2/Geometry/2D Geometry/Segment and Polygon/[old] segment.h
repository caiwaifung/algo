////////////////////////////////////////////////////////////////////////////////
bool point_on_segment(Point cp, Point s, Point t) {
	return sgn(mult(cp, s, t)) == 0 && sgn(dot(cp, s, t)) <= 0;
}
bool segment_cross_segment(Point a1, Point a2, Point b1, Point b2) {
	return sgn(mult(a1, a2, b1)) * sgn(mult(a1, a2, b2)) <= 0
		&& sgn(mult(b1, b2, a1)) * sgn(mult(b1, b2, a2)) <= 0;
}
////////////////////////////////////////////////////////////////////////////////
