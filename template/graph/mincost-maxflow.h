template<class T> class MincostMaxflow {
    struct Edge { int y; T w, c; Edge* oppo; };
    const int n_;
    vector<vector<unique_ptr<Edge>>> es_;
public:
    explicit MincostMaxflow(int n) : n_(n), es_(n) {}

    void add_edge(int x, int y, T w, T c) {
        Edge *e1, *e2;
        es_[x].emplace_back(e1=new Edge{y, w, c, nullptr});
        es_[y].emplace_back(e2=new Edge{x, 0, -c, nullptr});
        e1->oppo=e2, e2->oppo=e1;
    }

    // Returns (flow, cost).
    pair<T, T> compute(int s, int t) {
        pair<T, T> ans;
        while(1) {
            vector<T> dis(n_, numeric_limits<T>::max());
            vector<T> flow(n_);
            vector<Edge*> pre(n_);
            dis[s]=0;
            flow[s]=numeric_limits<T>::max();

            vector<bool> inside(n_, false);
            queue<int> que;
            inside[s]=true;
            que.push(s);
            while(!que.empty()) {
                const int x=que.front(); que.pop();
                for(const auto& e: es_[x]) {
                    if(e->w>0 && setmin(dis[e->y], dis[x]+e->c)) {
                        pre[e->y]=e.get();
                        flow[e->y]=min(flow[x], e->w);
                        if(!inside[e->y]) {
                            inside[e->y]=true;
                            que.push(e->y);
                        }
                    }
                }
                inside[x]=false;
            }
            if(dis[t]==numeric_limits<T>::max()) {
                return ans;
            }

            ans.fi+=flow[t], ans.se+=flow[t]*dis[t];
            for(int x=t; x!=s; x=pre[x]->oppo->y) {
                pre[x]->w-=flow[t];
                pre[x]->oppo->w+=flow[t];
            }
        }
        return ans;
    }
};