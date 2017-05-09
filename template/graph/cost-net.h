template <class T> class CostNet {
public:
    explicit CostNet(int n0) : n(n0 + 2), src(n0), dst(n0 + 1), es(n) {}

    int s() const { return src; }
    int t() const { return dst; }

    void* add(int x, int y, T w, T c) {
        assert(c >= 0);
        Edge *e1, *e2;
        es[x].emplace_back(e1 = new Edge{y, w, c, nullptr});
        es[y].emplace_back(e2 = new Edge{x, 0, -c, nullptr});
        e1->oppo = e2, e2->oppo = e1;
        return static_cast<void*>(e1);
    }

    // Returns (flow, cost).
    pair<T, T> compute() {
        pair<T, T> ans = {0, 0};
        while(1) {
            vector<T> dis(n, numeric_limits<T>::max());
            vector<T> flow(n);
            vector<Edge*> pre(n);
            dis[src] = 0;
            flow[src] = numeric_limits<T>::max();

            vector<bool> inside(n, false);
            queue<int> que;
            inside[src] = true;
            que.push(src);
            while(!que.empty()) {
                const int x = que.front();
                que.pop();
                for(const auto& e : es[x]) {
                    if(e->w > 0 && setmin(dis[e->y], dis[x] + e->c)) {
                        pre[e->y] = e.get();
                        flow[e->y] = min(flow[x], e->w);
                        if(!inside[e->y]) {
                            inside[e->y] = true;
                            que.push(e->y);
                        }
                    }
                }
                inside[x] = false;
            }
            if(dis[dst] == numeric_limits<T>::max()) {
                return ans;
            }

            ans.fi += flow[dst], ans.se += flow[dst] * dis[dst];
            for(int x = dst; x != src; x = pre[x]->oppo->y) {
                pre[x]->w -= flow[dst];
                pre[x]->oppo->w += flow[dst];
            }
        }
        return ans;
    }

    T flow(void* e) { return static_cast<Edge*>(e)->oppo->w; }

private:
    struct Edge {
        int y;
        T w, c;
        Edge* oppo;
    };

    const int n, src, dst;
    vector<vector<unique_ptr<Edge>>> es;
};
