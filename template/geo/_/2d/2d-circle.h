void circle_center(Point p0, Point p1, Point p2, Point &p) { //外接圆圆心
	double a1=p1.x-p0.x, b1=p1.y-p0.y, c1=(sqr(a1)+sqr(b1))/2.;
	double a2=p2.x-p0.x, b2=p2.y-p0.y, c2=(sqr(a2)+sqr(b2))/2.;
	double d=a1*b2-a2*b1;
	p.x=p0.x+(c1*b2-c2*b1)/d;
	p.y=p0.y+(a1*c2-a2*c1)/d;
}
double incenter(Point A, Point B, Point C, Point &p) { //内接圆圆心
	double a=dist(B,C), b=dist(C,A), c=dist(A,B), p=(a+b+c)/2.;
	double s=sqrt(p*(p-a)*(p-b)*(p-c)), r=s/p;
	p.x=(a*A.x + b*B.x + c*C.x) / (a+b+c);
	p.y=(a*A.y + b*B.y + c*C.y) / (a+b+c);
	return r;
}
void orthocenter(Point A, Point B, Point C, Point &p) { //垂心
	circle_center(A, B, C, p);
	p=A+B+C-p*2.;
}
int cross_lc(Point p, double r, Line l, Point &p1, Point &p2) { //直线交圆
	double a=l.a, b=l.b, c=l.c; double aa=a*a, bb=b*b, s=aa+bb;
	double d=r*r*s-sqr(a*p.x+b*p.y+l.c);
	if(sgn(d)<0) return 0; if(sgn(d)==0) d=0; else d=sqrt(d);
	double ab=a*b, double bd=b*d, ad=a*d;
	double xx=bb*p.x-ab*p.y-a*c;
	double yy=aa*p.y-ab*p.x-b*c;
	p2=Point((xx+bd)/s, (yy-ad)/s);
	p1=Point((xx-bd)/s, (yy+ad)/s);
	if(sgn(d)>0) return 2; else return 1;
}
Line crossline_cc(Point p1, double r1, Point p2, double r2) { //两圆交线
	Point s=p2+p1, m=p2-p1;
	return Line(2.*m.x, 2.*m.y, -dot(s, m)-(r1+r2)*(r1-r2));
}
int cross_cc(p1, r1, p2, r2, Point &p1, Point &p2) { //两圆交点 不可共圆心
	double mx=p2.x-p1.x, sx=p2.x+p1.x, mx2=mx*mx;
	double my=p2.y-p1.y, sy=p2.y+p1.y, my2=my*my;
	double sq=mx2+my2, d=-(sq-sqr(r1-r2))*(sq-sqr(r1+r2));
	if(sgn(d)<0) return 0; if(sgn(d)==0) d=0; else d=sqrt(d);
	double x=mx*((r1+r2)*(r1-r2) + mx*sx) + sx*my2;
	double y=my*((r1+r2)*(r1-r2) + my*sy) + sy*mx2;
	double dx=mx*d, dy=my*d; sq*=2.;
	p1=Point((x-dy)/sq, (y+dx)/sq);
	p2=Point((x+dy)/sq, (y-dx)/sq);
	if(sgn(d)>0) return 2; else return 1;
}
bool cross_cl(Line l, Point p, double r, Point &p1, Point &p2) { //线交圆
	Point t=p-Point(l.a, l.b)*(l.a*p.x+l.b*p.y+l.c)/sqrt(l.a*l.a+l.b*l.b);
	Point dir=Point(-l.b, l.a); dir=dir/dir.len();
	double x=(r*r-(t-p).sq_len()); if(sgn(x)<0) return false;
	if(sgn(x)==0) x=0; else x=sqrt(x);
	p1=t+dir*x; p2=t-dir*x; return true;
}
void tang_point(Point p1, double r1, Point p, Point &t1, Point &t2) {
	double x=(p1-p).sq_len()-r1*r1;          //点切圆，返回切点
	if(sgn(x)<0) printf("ERROR!\n");
	if(sgn(x)==0) { t1=t2=p; return; }
	x=sqrt(x); cross_cc(p1, r1, p, x, t1, t2);
}
void in_tang_line(P p1, double r1, P p2, double r2, Line &l1, Line &l2) {
	Point p=(p1*r2+p2*r1)/(r1+r2);           //两圆内切线
	double x=(p1-p).sq_len()-r1*r1;
	if(sgn(x)<0) printf("ERROR\n");
	if(sgn(x)==0) { //两圆相切
		Point dir(p2.y-p1.y, p1.x-p2.x); l1=l2=Line(p, p+dir); return;
	}
	x=sqrt(x);
	Point t1, t2; cross_cc(p1, r1, p, x, t1, t2);
	l1=Line(p, t1);	l2=Line(p, t2);
}
double area_union(Point p1, double r1, Point p2, double r2) { //两圆面积交
	double sq_len=sq_dist(p1,p2), len=dist(p1,p2);
	if(r1+r2<=len) return 0.;
	if(r1+len<=r2) return PI*r1*r1;
	if(r2+len<=r1) return PI*r2*r2;
	double c1=(r1*r1-r2*r2+sq_len)/len/r1/2.;
	double c2=(r2*r2-r1*r1+sq_len)/len/r2/2.;
	double s1=acos(c1), s2=acos(c2), ans=0.;
	ans+=r1*r1*(s1-sin(s1)*cos(s1));
	ans+=r2*r2*(s2-sin(s2)*cos(s2));
	return ans;
}
double area2(Point pa, Point pb, double r) {
	if(pa.len()<pb.len()) swap(pa, pb); if(sgn(pb.len())==0) return 0.;
	double a=pb.len(), b=pa.len(), c=(pa-pb).len();
	double cosB=dot(pb,pb-pa)/a/c, sinB=fabs(mult(pb,pb-pa)/a/c);
	double cosC=dot(pa,pb)/a/b, sinC=fabs(mult(pa,pb)/a/b);
	double B=atan2(sinB, cosB), C=atan2(sinC, cosC);
	double S, h, theta;
	if(a>r) { S=C/2.*r*r; h=a*b*sinC/c;
		if(h<r && B<PI/2.) S-=acos(h/r)*r*r-h*sqrt(r*r-h*h);
	} else if(b>r) { theta=PI-B-asin(sinB/r*a);
		S=.5*a*r*sin(theta)+(C-theta)/2.*r*r;
	} else S=.5*sinC*a*b;
	return S;
}
double area(Point o, double r, Point a, b, c) { //圆与三角形交的面积
	double S=0.; a=a-o, b=b-o, c=c-o;
	S+=area2(a, b) * sgn(mult(a, b));
	S+=area2(b, c) * sgn(mult(b, c));
	S+=area2(c, a) * sgn(mult(c, a));
	return abs(S);
}
