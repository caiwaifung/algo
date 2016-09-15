struct Hopcroft {
    VI es[N];
    int n, m;
    int maxmatch() {
        VI mx(n, -1), my(m, -1);
        while(1) {
            vector<bool> vis(m, false);
            VI src(n, -1), pre(n, -1);
            queue<int> que;
            repn(i, n) if(mx[i]<0) {
                src[i]=i;
                que.push(i);
            }
            bool found=false;
            while(!que.empty()) {
                const int x=que.front(); que.pop();
                if(mx[src[x]]>=0) continue;
                for(int y: es[x]) if(!vis[y]) {
                    vis[y]=true;
                    if(my[y]<0) {
                        for(int i=x, j=y; i>=0; ) {
                            const int j0=mx[i];
                            mx[i]=j, my[j]=i; i=pre[i], j=j0;
                        }
                        found=true;
                        break;
                    }
                    src[my[y]]=src[x];
                    pre[my[y]]=x;
                    que.push(my[y]);
                }
            }
            if(!found) break;
        }
        int ans=0;
        repn(i, n) if(mx[i]>=0) ++ans;
        return ans;
    }
};
