bool sameline(P3 p1, P3 p2, P3 p3) { //判断共线
	return sgn(det(p1, p2, p3).len())==0;
}
bool sameplane(P3 p1, P3, p2, P3 p3, P3 p4) { //判断共面
	return sgn(dot(det(p1, p2, p3), p4-p3))==0;
}
bool on_segment(P3 p, P3 a1, P3 a2) { //判断是否在线段上；包含端点
	if(!sameline(p, a1, a2)) return false;
	a1=a1-p, a2=a2-p;    //若想不包含端点，需特判 p!=a1 && p!=a2
	return sgn(a1.x*a2.x)<=0 && sgn(a1.y*a2.y)<=0 && sgn(a1.z*a2.z)<=0;
}
bool in_tri(P3 p, P3 s1, P3 s2, P3 s3) { //判断是否在三角形内；包含边界
	double a=det(p,s1,s2).len() + det(p,s2,s3).len() + det(p,s3,s1).len();
	double b=det(s1, s2, s3).len();
	return sgn(a-b)==0; //若想不包含边界，需特判!sameline(p,s[i],s[i+1])
}
bool sameside(P3 p1, P3 p2, P3 l1, P3 l2) { //平面两点是否在直线的同一侧
	return sgn(dot(det(l1, l2, p1), det(l1, l2, p2)))>0;
}
bool sameside(P3 p1, P3 p2, P3 s1, P3 s2, P3 s3) { //两点是否在平面同一侧
	P3 n=det(s1,s2,s3); return sgn(dot(n, p1-s1)*dot(n, p2-s1))>0;
}
bool parallel(P3 a1, P3 a2, P3 b1, P3 b2) { //直线是否平行
	return sgn(det(a1-a2, b1-b2).len())==0;
}
bool parallel(P3 a1, P3 a2, P3 a3, P3 b1, P3 b2, P3 b3) { //平面是否平行
	return sgn(det(det(a1,a2,a3), det(b1,b2,b3)).len())==0;
}
bool parallel(P3 p1, P3 p2, P3 a1, P3 a2, P3 a3) { //平面与直线是否平行
	return sgn(dot(p1-p2, det(a1,a2,a3)))==0;
}
bool perp(P3 a1, P3 a2, P3 b1, P3 b2) { //直线是否垂直
	return sgn(dot(a1-a2, b1-b2))==0;
}
bool perp(P3 a1, P3 a2, P3 a3, P3 b1, P3 b2, P3 b3) { //平面是否垂直
	return sgn(dot(det(a1,a2,a3), det(b1,b2,b3)))==0;
}
bool perp(P3 p1, P3 p2, P3 a1, P3 a2, P3 a3) { //平面与直线是否垂直
	return sgn(det(p1-p2, det(a1,a2,a3)).len())==0;
}
bool intersect(P3 a1, P3 a2, P3 b1, P3 b2) { //线段是否相交；不包括端点
	return sameplane(a1,a2,b1,b2) &&
		opposide(a1,a2,b1,b2) && opposide(b1,b2,a1,a2);
}
bool intersect(P3 l1, P3 l2, P3 s1, P3 s2, P3 s3) { //线段是否与三角形交
	return !sameside(l1,l2,s1,s2,s3) && !sameside(s1,s2,l1,l2,s3)
		 && !sameside(s2,s3,l1,l2,s1) && !sameside(s3,s1,l1,l2,s2);
	//包含边界；若想不包含边界，请用"opposide"代替"!sameside"
}
P3 intersect(P3 a1, P3 a2, P3 b1, P3 b2) { //直线交；需保证共面且不平行
	double t=(a1.x-b1.x)*(b1.y-b2.y) - (a1.y-b1.y)*(b1.x-b2.x);
	t/=(a1.x-a2.x)*(b1.y-b2.y) - (a1.y-a2.y)*(b1.x-b2.x);
	return a1+(u2-u1)*t;
}
P3 proj(P3 p, P3 dir, P3 normal, P3 p0) { //p沿dir方向投影到平面
	double a=dot(dir, normal);
	double b=dot(p-p0, normal);
	return p+dir*(-b/a);
}
bool intersect_line(P3 a1,a2,a3, P3 b1,b2,b3, P3 &l1,&l2) { //平面交
	if(parallel(a1,a2,a3, b1,b2,b3)) return false;
	l1=parallel(b1,b2, a1,a2,a3)
		? intersect(b2,b3, a1,a2,a3) : intersect(b1,b2, a1,a2,a3);
	l2=l1+det(det(a), det(b));  return true;
}
double dist_l(P3 p, P3 a1, P3 a2) {
	return det(p, a1, a2).len() / dist(a1, a2);
}
double dist_p(P3 p, P3 s1, P3 s2, P3 s3) {
	return fabs(dot(det(s), p-s1)) / det(s).len();
}
double dist_lines(P3 a1, P3 a2, P3 b1, P3 b2） { //平行时有问题！！！！
	P3 n=det(a1-a2, b1-b2);  return fabs(dot(u1-v1, n)) / n.len();
}
double angle_cos(P3 ua,ub, P3 va,vb) { // 两直线形成的角的cos值
	return dot(ua-ub, va-vb) / (ua-ub).len() / (va-vb).len();
}
double angle_cos(P3 ua,ub,uc, P3 va,vb,vc) { // 两平面形成的角的cos值
	return dot(det(u), det(v)) / det(u).len() / det(v).len();
}

