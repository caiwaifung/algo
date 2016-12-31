template <class T> struct Net {
    Net(int n, int s, int t)
        : n_(n + 2), s_(s), t_(t), super_s_(n), super_t_(n + 1), es_(n_) {}

    void* add(int x, int y, T w) { return add_(x, y, w); }
    void* add(int x, int y, pair<T, T> w) { return add_(x, y, w); }

    // returns -1 if no solution.
    T compute() { return compute_(); }
    T flow(void* e) { return flow_(e); }

private:  // {{{
    struct Edge {
        int y;
        T w;
        Edge* oppo;
    };
    const int n_, s_, t_, super_s_, super_t_;
    T super_total_ = 0;
    vector<vector<unique_ptr<Edge>>> es_;

    void* add_(int x, int y, T w) {
        Edge *e1, *e2;
        es_[x].emplace_back(e1 = new Edge{y, w, nullptr});
        es_[y].emplace_back(e2 = new Edge{x, 0, nullptr});
        e1->oppo = e2, e2->oppo = e1;
        return e1;
    }

    void* add_(int x, int y, pair<T, T> w) {
        assert(w.fi <= w.se);
        if(w.fi > 0) {
            add(super_s_, y, w.fi);
            add(x, super_t_, w.fi);
            super_total_ += w.fi;
        }
        return add_(x, y, w.se - w.fi);
    }

    T compute_() {
        if(super_total_ > 0) {
            add_(t_, s_, numeric_limits<T>::max());
            LL r = 0, tmp;
            while((tmp = augment_(super_s_, super_t_)) > 0) r += tmp;
            if(r != super_total_) return -1;
        }
        T ans = 0, tmp;
        while((tmp = augment_(s_, t_)) > 0) ans += tmp;
        return ans;
    }

    T flow_(void* e) const { return static_cast<Edge*>(e)->oppo->w; }

    T augment_(int s, int t) {
        VI dis(n_);
        dis[s] = 1;
        queue<int> que;
        que.push(s);
        while(!que.empty()) {
            int x = que.front();
            que.pop();
            for(const auto& e : es_[x]) {
                if(e->w > 0 && dis[e->y] == 0) {
                    dis[e->y] = dis[x] + 1;
                    que.push(e->y);
                }
            }
        }
        if(dis[t] == 0) return 0;

        vector<size_t> ce(n_);
        const function<T(int, T)> dfs = [&](int x, T rest) {
            if(x == t) return rest;
            T r = 0;
            for(size_t& i = ce[x]; i < es_[x].size(); ++i) {
                const auto& e = es_[x][i];
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
    // }}}
};
