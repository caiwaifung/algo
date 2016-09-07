class Network {
    typedef int T;
    struct Edge { int y; T w; Edge* oppo; };
    const int n_, super_s_, super_t_;
    T super_total_=0;
    vector<vector<unique_ptr<Edge>>> es_;

public:
    explicit Network(int n) : n_(n+2), super_s_(n), super_t_(n+1), es_(n_) {}

    void* add_edge(int x, int y, T w) {
        Edge *e1, *e2;
        es_[x].emplace_back(e1=new Edge{y, w, nullptr});
        es_[y].emplace_back(e2=new Edge{x, 0, nullptr});
        e1->oppo=e2, e2->oppo=e1;
        return e1;
    }

    void* add_edge_with_lower_limit(int x, int y, T w, T lb) {
        if(lb>0) {
            add_edge(super_s_, y, lb);
            add_edge(x, super_t_, lb);
            super_total_+=lb;
        }
        return add_edge(x, y, w-lb);
    }

    // Returns -1 if no solution.
    T compute_maxflow(int s, int t) {
        if(super_total_>0) {
            add_edge(t, s, numeric_limits<T>::max());
            LL r=0, tmp;
            while((tmp=augment(super_s_, super_t_))>0) r+=tmp;
            if(r!=super_total_) return -1;
        }
        T ans=0, tmp;
        while((tmp=augment(s, t))>0) ans+=tmp;
        return ans;
    }

    T flow(void* e) const { return static_cast<Edge*>(e)->oppo->w; }

private:
    T augment(int s, int t) {
        VI dis(n_); dis[s]=1; 
        queue<int> que; que.push(s);
        while(!que.empty()) {
            int x=que.front(); que.pop();
            for(const auto& e: es_[x]) {
                if(e->w>0 && dis[e->y]==0) {
                    dis[e->y]=dis[x]+1;
                    que.push(e->y);
                }
            }
        }
        if(dis[t]==0) return 0;

        vector<size_t> ce(n_);
        const function<T(int,T)> dfs=[&](int x, T rest) {
            if(x==t) return rest;
            T r=0;
            for(size_t& i=ce[x]; i<es_[x].size(); ++i) {
                const auto& e=es_[x][i];
                if(e->w>0 && dis[e->y]>dis[x]) {
                    T cur=dfs(e->y, min(e->w, rest));
                    e->w-=cur, e->oppo->w+=cur;
                    r+=cur, rest-=cur;
                    if(rest==0) break;
                }
            }
            return r;
        };
        return dfs(s, numeric_limits<T>::max());
    }
};
