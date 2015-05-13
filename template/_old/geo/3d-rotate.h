double[3][3] rotate_matrix(Point p, double ang) { //绕Op逆时针转ang角度
	// xx+c(1-xx)    xy(1-c)-zs    zx(1-c)+ys
	// xy(1-c)+zs    yy+c(1-yy)    yz(1-c)-xs
	// zx(1-c)-ys    yz(1-c)+xs    zz+c(1-zz)
}
P3 rotate(Point a, Point b, double ang) { //a绕Ob转ang
	b.normalize();
	P3 e3=b;  double lens=dot(a, e3);
	P3 e1=a-e3*lens;  if(sgn(e1.len())>0) e1.normalize(); else return a;
	P3 e2=det(e1, e3);
	double y1=dot(a, e1), x1=dot(a, e2);
	double x=x1*cos(ang)-y1*sin(ang), y=x1*sin(ang)+y1*cos(ang);
	return e3*lens + e1*y + e2*x;
}
