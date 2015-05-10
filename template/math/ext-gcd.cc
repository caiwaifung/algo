template<class T> T ext_gcd(T a, T b, T &x, T &y) {
    if(b==0) { x=1, y=0; return a; }
    LL nx, ny, d; d=ext_gcd(b, a%b, nx, ny);
    x=ny, y=nx-(a/b)*ny;
    return d;
}
