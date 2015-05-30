Point c[8010]; int m;
void go_convex() {
    m=0;
    sort(a+1, a+n+1);
    forint(i, 1, n) {
        while(m>1 && mult(c[m-1], c[m], a[i])<=0) --m;
        c[++m]=a[i];
    }
    int t=m;
    forintdown(i, n, 1) {
        while(m>t && mult(c[m-1], c[m], a[i])<=0) --m;
        c[++m]=a[i];
    }
    --m;
}