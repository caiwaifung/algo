// Point/segment inside (or cross) polygon
bool point_in_polygon(Point p, Point a[], int n) {
	a[0]=a[n];
	int wn=0;
	forint(i, 1, n) {
		if(on_segment(p, a[i-1], a[i]))
			return true; // or false!!!!
		int k=sgn(mult(a[i-1], a[i], p));
		int d1=sgn(a[i-1].y-p.y);
		int d2=sgn(a[i].y-p.y);
		if(k>0 && d1<=0 && d2>0) ++wn;
		if(k<0 && d2<=0 && d1>0) --wn;
	}
	return wn!=0;
}
Point stack[11000];
bool segment_cross_polygon(Point s, Point t, Point a[], int n) {
	if(point_in_polygon(s, a, n)) return true;
	if(point_in_polygon(t, a, n)) return true;
	a[0]=a[n];
	Line e1=make_line(s, t);
	int top=1; stack[top]=s;
	forint(i, 1, n) {
		Line e2=make_line(a[i-1], a[i]);
		if(!parallel(e1, e2)) {
			Point c;
			if(!cross_ll(e1, e2, &c)) printf("error!");
			if(on_segment(c,s,t) && on_segment(c,a[i-1],a[i]))
				stack[++top]=c;
		}
	}
	stack[++top]=t;
	sort(stack+1, stack+top+1); // sort as x then y
	forint(i, 1, top-1) {
		Point c=(stack[i]+stack[i+1])/2;
		if(point_in_polygon(c, a, n))
			return true;
	}
	return false;
}
