// Finds x and y: a x + b y = gcd(a, b).  Returns gcd(a, b).
// 
// Must: |a| + |b| > 0.
// Guarantee: ???
LL ext_gcd(LL a, LL b, LL* x, LL* y) {
    if(b==0) { *x=1, *y=0; return a; }
    LL nx, ny; LL d=ext_gcd(b, a%b, &nx, &ny);
    *x=ny, *y=nx-(a/b)*ny;
    return d;
}

// Returns x: (a * x) % m = 1.
//
// Must: gcd(a, m) = 1.
// Guarantee: 0 <= x < m.
LL inv(LL a, LL m) {
    LL x, y;
    assert(ext_gcd(a, m, &x, &y)==1);
    if(x<0) x+=m;
    return x;
}
