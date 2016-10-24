VI es[N];
int n;

void solve() {
    VI belong(n, -1), dfn(n), low(n);
    VI stack;
    int num=0, counter=0;
    const function<void(int)> dfs=[&](int x) {
        dfn[x]=low[x]=counter++;
        belong[i]=-2;
        stack.pb(x);
        for(int y: es[x]) {
            if(belong[y]==-1) {
                dfs(y);
                setmin(low[x], low[y]);
            } else if(belong[y]==-2) {
                setmin(low[x], dfn[y]);
            }
        }
        if(low[x]==dfn[x]) {
            while(1) {
                const int y=stack.back(); stack.pop_back();
                belong[y]=num;
                if(y==x) break;
            }
            ++num;
        }
    };
    repn(i, n) if(belong[i]==0) dfs(i);

    // ...
}
