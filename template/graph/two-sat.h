class TwoSat {
public:
    TwoSat(int n) : n(n), es(n * 2) {}

    void add_conflict(PII a, PII b) {
        assert(a.fi >= 0 && a.fi < n && a.se >= 0 && a.se <= 1);
        assert(b.fi >= 0 && b.fi < n && b.se >= 0 && b.se <= 1);
        es[a.fi + a.se * n].pb(b.fi + (1 - b.se) * n);
        es[b.fi + b.se * n].pb(a.fi + (1 - a.se) * n);
    }

    // If no solution, returns {}; otherwise returns
    // r: r[i] = value of variable i (0/1).
    VI solve() {
        VI belong(n * 2, -1), dfn(n * 2), low(n * 2), stack;
        int cur = 0, num = 0;
        const function<void(int)> dfs = [&](int x) {
            dfn[x] = low[x] = cur++;
            stack.pb(x);
            belong[x] = -2;
            for(int y : es[x]) {
                if(belong[y] == -1) {
                    dfs(y);
                    setmin(low[x], low[y]);
                } else if(belong[y] == -2) {
                    setmin(low[x], dfn[y]);
                }
            }
            if(low[x] == dfn[x]) {
                while(1) {
                    int y = stack.back();
                    stack.pop_back();
                    belong[y] = num;
                    if(y == x) break;
                }
                ++num;
            }
        };
        repn(i, n * 2) if(belong[i] == -1) dfs(i);

        VI r(n);
        repn(i, n) {
            if(belong[i] == belong[i + n]) {
                return VI();
            }
            r[i] = (belong[i] > belong[i + n]);
        }
        return r;
    }

private:
    const int n;
    vector<VI> es;
};
