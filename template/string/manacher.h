#include "../base/header.h"

VI manacher(const string& s) {
    VI ans(len(s));
    int p = -1, r = -1;
    repn(i, len(s)) {
        int cur = 1;
        if (r > i) {
            cur = min(ans[p * 2 - i], r - i);
        }
        while (i - cur >= 0 && i + cur < len(s) && s[i - cur] == s[i + cur]) {
            ++cur;
        }
        ans[i] = cur;
        if (setmax(r, i + cur)) {
            p = i;
        }
    }
    return ans;
}
