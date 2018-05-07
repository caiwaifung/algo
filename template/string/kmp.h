#include "../base/header.h"

// ans[i] = max prefix of t matches suffix of s[0..i]
VI kmp(const string& s, const string& t) {
    VI fail(len(t) + 1);
    int j = fail[0] = -1;
    repn(i, len(t)) {
        while (j >= 0 && t[j] != t[i]) j = fail[j];
        fail[i + 1] = ++j;
    }

    VI ans(len(s));
    j = 0;
    repn(i, len(s)) {
        while (j >= 0 && t[j] != s[i]) j = fail[j];
        ans[i] = ++j;
    }
    return ans;
}
