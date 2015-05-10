struct Circle {
    Point p; double r;
    Circle() { }
    Circle(Point p, double r) : p(p), r(r) { }
    int crossLine(Line l, Point &p1, Point &p2) {
        double a=l.a, b=l.b, c=l.c; double aa=a*a, bb=b*b, s=aa+bb;
        double d=r*r*s-sqr(a*p.x+b*p.y+l.c);
        if(sgn(d)<0) return 0; if(sgn(d)==0) d=0; else d=sqrt(d);
        double ab=a*b, bd=b*d, ad=a*d;
        double xx=bb*p.x-ab*p.y-a*c;
        double yy=aa*p.y-ab*p.x-b*c;
        p2=Point((xx+bd)/s, (yy-ad)/s);
        p1=Point((xx-bd)/s, (yy+ad)/s);
        if(sgn(d)>0) return 2; else return 1;
    }
};
