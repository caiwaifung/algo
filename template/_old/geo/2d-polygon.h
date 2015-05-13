Point rotate(Point p, double sinA, double cosA) {
	return Point(p.x*cosA-p.y*sinA, p.x*sinA+p.y*cosA);
}
Point project_point(Point p, Point p1, Point p2) { //投影点
	double d=dot(p1-p2, p1-p2);    // !!!! ???????????
	double s=mult(p1, p2, p);
	return p + Point(p2.y-p1.y, p1.x-p2.x)*s/d;
}
Point reflect_point(Point p, Point p1, Point p2) { //对面点
	Point p3=project_point(p, p1, p2);
	return p3+p3-p;
}
Line move_d(Line l, double d) { //线段平移d的长度
	return Line(l.a, l.b, l.c+d*sqrt(l.a*l.a+l.b*l.b));
}
bool in_polygon(Point p, VP a) {
	int wn=0;
	forn(i, a.size()) {
		Point p1=a[i], p2=a[(i+1)%a.size()];
		if(on_segment(p, p1, p2)) return true;
		int k=sgn(mult(p1, p2, p));
		int d1=sgn(p1.y-p.y), d2=sgn(p2.y-p.y);
		if(k>0 && d1<=0 && d2>0) ++wn;
		if(k<0 && d2<=0 && d1>0) --wn;
	}
	return wn!=0;
}
bool check(HalfPlane u, v, w); //check if cross_point(u,v) in w
void half_plane_cross(vector<HalfPlane> planes) { //半平面交
	int ss=1, tt=0;
	forn(i, planes.size()) {
		while(ss<tt && !check(q[tt-1], q[tt], planes[i])) --tt;
		while(ss<tt && !check(q[ss+1], q[ss], planes[i])) ++ss;
		q[++tt]=planes[i];
	}
	while(ss+1<tt && !check(q[tt-1], q[tt], planes[i])) --tt;
	while(ss+1<tt && !check(q[ss+1], q[ss], planes[i])) ++ss;
	//convex: {cross_point(q[i],q[i+1])}
}
bool adjust_tangent(const VP &a, int &i, Point p, int t) { //调整切线
	bool flag=false;   //a[]为凸包；希望forall k, mult(a[i],p,a[k])*t>=0
	while(1) {
		int t1=sgn(mult(a[i], p, a[(i+1)%a.size()]));
		int t2=sgn(mult(a[i], p, a[(i+a.size()-1)%a.size()]));
		if(t1*t>=0 && t2*t>=0) break;
		flag=true; i=(i+1)%a.size();
	}
	return flag;
}
PII find_tangent(const VP &a, const VP &b, int t) { //两凸包的内切线
	int i=0, j=0;
	for(bool flag=true; flag; ) {
		flag=false;
		if(adjust_tangent(a, i, b[j], t)) flag=true;
		if(adjust_tangent(b, j, a[i], t)) flag=true;
	}
	return MP(i, j);
}
void cut_convex(const VP &a, Point p1, Point p2) { //直线切凸包 O(n)
	VP b;        //保留 {p | mult(p1,p2,p)>=0} 的部分
	forn(i, a.size()) {
		Point a1=a[i], a2=a[(i+1)%a.size()];
		double m1=mult(p1, p2, a1);
		double m2=mult(p1, p2, a2);
		if(sgn(m1)*sgn(m2)<0) {
			Point tmp;
			tmp.x=(a1.x*m2-a2.x*m1)/(m2-m1);
			tmp.y=(a1.y*m2-a2.y*m1)/(m2-m1);
			b.push_back(tmp);
		}
		if(sgn(m2)>=0) b.push_back(a2);
	}
	a=b;
}
VP convex_cross(const VP &a, const VP &b) { //凸包交 O(n^2)
	double s=0;
	forn(i, b.size()) s+=mult(b[i], b[(i+1)%b.size()], b[(i+2)%b.size()]);
	VP c=a;
	forn(i, b.size()) {
		P2 p1=b[i], p2=b[(i+1)%b.size()];
		if(s<0) swap(p1, p2);
		cut_convex(c, p1, p2);
	}
	return c;
}
double get_lambda(Point p, Point s, Point t) { //返回c: p=s+(t-s)*c
	return dot(s, t, p)/dot(s, t, t);
}
void poly_cut(const VP &p, Point s, t, vector<PDD> &cuts) { //线段切多边形
	vector<double> c; c.PB(0); c.PB(1);
	forn(i, p.size()) {
		Point p1=p[i], p2=p[(i+1)%p.size()], cp;
		if(get_cross(p1, p2, s, t, cp))
			c.PB(get_lambda(cp, s, t)); //c: cp=s+(t-s)*c
	}
	sort(c.begin(), c.end());
	forint(i, 1, c.size()-1) {
		double lambda=(c[i-1]+c[i])/2.;
		Point lp=t*lambda+s*(1.-lambda);
		if(in_poly(p, lp)) cuts.PB(MP(c[i-1], c[i]));
	}
}
