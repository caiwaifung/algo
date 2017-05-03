VI manacher(const string& s) {
    VI ans(sz(s));
    int p = -1, r = -1;
    repn(i, sz(s)) {
        int cur = 1;
        if(r > i) {
            cur = min(ans[p * 2 - i], r - i);
        }
        while(i - cur >= 0 && i + cur < sz(s) && s[i - cur] == s[i + cur]) {
            ++cur;
        }
        ans[i] = cur;
        if(setmax(r, i + cur)) {
            p = i;
        }
    }
    return ans;
}
