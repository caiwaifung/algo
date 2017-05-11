int min_representation(const string& a) {
    const int n = sz(a);
    int i = 0, j = 1, k = 0;
    while(i < n && j < n && k < n) {
        const auto& ai = a[(i + k) % n];
        const auto& aj = a[(j + k) % n];
        if(ai == aj) {
            ++k;
        } else {
            (ai > aj ? i : j) += k + 1;
            if(i == j) ++j;
            k = 0;
        }
    }
    return min(i, j);
}
