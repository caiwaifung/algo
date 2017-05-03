// ans[i] = max prefix of t matches suffix of s[:i]
VI kmp(const string& s, const string& t) {
    VI fail(sz(t) + 1);
    int j = fail[0] = -1;
    repn(i, sz(t)) {
        while(j >= 0 && t[j] != t[i]) j = fail[j];
        fail[i + 1] = ++j;
    }

    VI ans(sz(s));
    j = 0;
    repn(i, sz(s)) {
        while(j >= 0 && t[j] != s[i]) j = fail[j];
        ans[i] = ++j;
    }
    return ans;
}
