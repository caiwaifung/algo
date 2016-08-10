class Dinic {
public:
    typedef LL T;
    explicit Dinic(int n) : n_(n), es_(n) {}
    void add_edge(int x, int y, T w) { add_edge_(x, y, w); }
    T compute_max(int s, int t) { return compute_max_(s, t); }

private: // {{{
    struct Edge { int y;  T w; Edge* oppo; };

    void add_edge_(int x, int y, T w) {
        Edge *e1, *e2;
        es_[x].emplace_back(e1=new Edge{y, w, nullptr});
        es_[y].emplace_back(e2=new Edge{x, 0, nullptr});
        e1->oppo=e2, e2->oppo=e1;
    }

    T compute_max_(int s, int t) {
        T ans=0;
        while(1) {
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
            if(dis[t]==0) return ans;

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
            ans+=dfs(s, numeric_limits<T>::max());
        }
    }

    const int n_;
    vector<vector<unique_ptr<Edge>>> es_;
// }}}
};
