VI es[N];
int n;

void solve() {
    VI belong(n), dfn(n, -1), low(n), color(n);
    VI stack;
    int num=0, counter=0;
    const function<void(int)> dfs=[&](int x) {
        dfn[x]=low[x]=counter++;
        color[x]=-1;
        stack.pb(x);
        for(int y: es[x]) {
            if(color[y]==0) {
                dfs(y);
                setmin(low[x], low[y]);
            } else if(color[y]<0) {
                setmin(low[x], dfn[y]);
            }
        }
        color[x]=1;
        if(low[x]==dfn[x]) {
            while(1) {
                const int y=stack.back(); stack.pop_back();
                belong[y]=num;
                if(y==x) break;
            }
            ++num;
        }
    };
    repn(i, n) if(color[i]==0) dfs(i);

    // ...
}
