template<size_t N, size_t M> class BipartiteGraph {
    bool g[N][M], vis[M]; int n, m;
    bool find(int x) {
        for(int y=1; y<=m; ++y)
            if(g[x][y] && !vis[y]) {
                vis[y]=true;
                if(ly[y]==0 || find(ly[y])) {
                    ly[y]=x; lx[x]=y;
                    return true;
                }
            }
        return false;
    }
    void dfs(int x) {
        for(int y=1; y<=m; ++y)
            if(g[x][y] && !vcy[y]) {
                int x0=ly[y]; assert(x0>0 && vcx[x0]);
                vcx[x0]=false; vcy[y]=true;
                dfs(x0);
            }
    }
public:
    int lx[N], ly[M];
    bool vcx[N], vcy[M];
    BipartiteGraph(int n, int m) : n(n), m(m) {
        assert(n<(int)N && m<(int)M);
        memset(g, false, sizeof(g));
    }
    void addEdge(int i, int j) { g[i][j]=true; }
    void delEdge(int i, int j) { g[i][j]=false; }
    int match() {
        memset(lx, 0, sizeof(lx));
        memset(ly, 0, sizeof(ly));
        int ans=0;
        for(int i=1; i<=n; ++i) {
            memset(vis, false, sizeof(vis));
            if(find(i)) ans++;
        }
        return ans;
    }
    void vc() { // compute vertex cover
        memset(vcx, false, sizeof(vcx));
        memset(vcy, false, sizeof(vcy));
        for(int i=1; i<=n; ++i) if(lx[i]) vcx[i]=true;
        for(int i=1; i<=n; ++i) if(lx[i]==0) dfs(i);
    }
};
