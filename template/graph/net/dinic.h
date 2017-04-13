template <class T> class Net {
public:
    Net(int n0, int s, int t)
        : n(n0 + 2),
          original_s(s),
          original_t(t),
          super_s(n),
          super_t(n + 1),
          es(n),
          dis(n) {}

    void* add(int x, int y, T w) {
        assert(x >= 0 && x < n && y >= 0 && y < n);
        Edge *e1, *e2;
        es[x].emplace_back(e1 = new Edge{y, w, nullptr});
        es[y].emplace_back(e2 = new Edge{x, 0, nullptr});
        e1->oppo = e2, e2->oppo = e1;
        return e1;
    }
    void* add(int x, int y, pair<T, T> w) {
        assert(w.fi <= w.se);
        if(w.fi > 0) {
            add(super_s, y, w.fi);
            add(x, super_t, w.fi);
            super_total += w.fi;
        }
        return add(x, y, w.se - w.fi);
    }

    // returns -1 if no solution.
    T compute() {
        if(super_total > 0) {
            add(original_t, original_s, numeric_limits<T>::max());
            LL r = 0, tmp;
            while((tmp = augment(super_s, super_t)) > 0) {
                r += tmp;
            }
            if(r != super_total) return -1;
        }
        T ans = 0, tmp;
        while((tmp = augment(original_s, original_t)) > 0) {
            ans += tmp;
        }
        return ans;
    }

    T flow(void* e) const { return static_cast<Edge*>(e)->oppo->w; }
    bool on_cut(void* e) const {
        return dis[static_cast<Edge*>(e)->oppo->y] > 0 &&
               dis[static_cast<Edge*>(e)->y] == 0;
    }
    VI left() const {
        VI r;
        repn(i, n) if(dis[i] > 0) r.pb(i);
        return r;
    }

private:
    struct Edge {
        int y;
        T w;
        Edge* oppo;
    };

    T augment(int s, int t) {
        dis.resize(n);
        fill(all(dis), 0);
        dis[s] = 1;
        queue<int> que;
        que.push(s);
        while(!que.empty()) {
            int x = que.front();
            que.pop();
            for(const auto& e : es[x]) {
                if(e->w > 0 && dis[e->y] == 0) {
                    dis[e->y] = dis[x] + 1;
                    que.push(e->y);
                }
            }
        }
        if(dis[t] == 0) return 0;

        vector<size_t> ce(n);
        const function<T(int, T)> dfs = [&](int x, T rest) {
            if(x == t) return rest;
            T r = 0;
            for(size_t& i = ce[x]; i < es[x].size(); ++i) {
                const auto& e = es[x][i];
                if(e->w > 0 && dis[e->y] > dis[x]) {
                    T cur = dfs(e->y, min(e->w, rest));
                    e->w -= cur, e->oppo->w += cur;
                    r += cur, rest -= cur;
                    if(rest == 0) break;
                }
            }
            return r;
        };
        return dfs(s, numeric_limits<T>::max());
    }

    const int n, original_s, original_t, super_s, super_t;
    T super_total = 0;
    vector<vector<unique_ptr<Edge>>> es;
    VI dis;
};
