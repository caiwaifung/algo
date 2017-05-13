class DancingLinks {
public:
    DancingLinks(int n, int m)
        : n(n), m(m), chosen(n, false), ignored(m, false) {}

    void add(int x, int y) {
        assert(x >= 0 && x < n && y >= 0 && y < m);
        ps.pb(mp(x,y));
    }

    void choose(int x) { chosen[x] = true; }
    void ignore(int y) { ignored[y] = true; }

    // on_found: input is bool[n] for rows selection
    //           output is whether to continue
    void solve(function<bool(const vector<bool>&)> on_found) {
        build();
        search(on_found);
    }

private:
    struct Node {
        int x, y, l, r, u, d;
        Node(int x, int y) : x(x), y(y), l(-1), r(-1), u(-1), d(-1) {}
    };

    void build() {
        s = VI(m);
        a.clear();
        repn(y, m) a.pb(Node(-1, y));
        for(const auto& p: ps) a.pb(Node(p.fi, p.se));
        sort(all(a), [](const Node& u, const Node& v) {
            return u.x < v.x || (u.x == v.x && u.y < v.y);
        });
        VI c(m, -1);
        int last = -1, last_x = -1;
        vector<bool> to_cover(m, false);
        repn(i, sz(a)) {
            const int x = a[i].x, y = a[i].y;
            if(setmax(last_x, x)) last = -1;
            a[i].u = a[i].d = a[i].l = a[i].r = i;
            if(c[y] >= 0) a[i].u = c[y], a[i].d = a[c[y]].d;
            if(last >= 0) a[i].l = last, a[i].r = a[last].r;
            a[a[i].u].d = a[a[i].d].u = i;
            a[a[i].l].r = a[a[i].r].l = i;
            last = c[y] = i, ++s[y];
            if(x >= 0 && chosen[x]) {
                assert(!to_cover[y]);
                to_cover[y] = true;
            }
        }
        h = sz(a), a.pb(Node(-1, -1));
        a[h].r = 0, a[h].l = a[0].l, a[a[h].l].r = a[a[h].r].l = h;
        repn(y, m) if(to_cover[y]) cover(y);
    }

    void cover(int y) {
        a[a[y].l].r = a[y].r, a[a[y].r].l = a[y].l;
        for(int i = a[y].d; i != y; i = a[i].d) {
            for(int j = a[i].r; j != i; j = a[j].r) {
                a[a[j].u].d = a[j].d, a[a[j].d].u = a[j].u;
                --s[a[j].y];
            }
        }
    }

    void uncover(int y) {
        for(int i = a[y].u; i != y; i = a[i].u) {
            for(int j = a[i].l; j != i; j = a[j].l) {
                a[a[j].u].d = a[a[j].d].u = j;
                ++s[a[j].y];
            }
        }
        a[a[y].l].r = a[a[y].r].l = y;
    }

    bool search(function<bool(const vector<bool>&)> on_found) {
        int y = -1;
        for(int i = a[h].r; i != h; i = a[i].r) {
            if(!ignored[a[i].y]) {
                if(y < 0 || s[a[i].y] < s[a[y].y]) y = i;
            }
        }
        if(y < 0) return on_found(chosen);
        bool cont = true;
        cover(y);
        for(int i = a[y].d; cont && i != y; i = a[i].d) {
            chosen[a[i].x] = true;
            for(int j = a[i].r; j != i; j = a[j].r) cover(a[j].y);
            cont &= search(on_found);
            for(int j = a[i].l; j != i; j = a[j].l) uncover(a[j].y);
            chosen[a[i].x] = false;
        }
        uncover(y);
        return cont;
    }

    const int n, m;
    vector<bool> chosen, ignored;
    VPI ps;

    vector<Node> a;
    int h;
    VI s;
};
