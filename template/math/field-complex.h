struct ComplexField {
    typedef complex<double> value_t;
    static value_t root_of_unity(int n, bool is_inv = false) {
        static constexpr double PI = 3.14159265358979323846264;
        const double ang = PI * 2.0 / n;
        return value_t(cos(ang), is_inv ? sin(ang) : -sin(ang));
    }
    static value_t add(const value_t& a, const value_t& b) { return a + b; }
    static value_t sub(const value_t& a, const value_t& b) { return a - b; }
    static value_t mul(const value_t& a, const value_t& b) { return a * b; }
    static value_t div(const value_t& a, const value_t& b) { return a / b; }
};
