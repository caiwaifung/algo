int a[N][N], n;

int match() {
    VI lnk(n, -1), cx(n, 0), cy(n, 0);
    repn(cur, n) {
        VI slack(n, 1<<30), pre(n, -1);
        vector<bool> vis(n, false);
        int j0=-1;
        while(1) {
            if(j0>=0) vis[j0]=true;
            int i0=(j0<0?cur:lnk[j0]); if(i0<0) break;
            int minv=1<<30, minj=-1;
            repn(j, n) if(!vis[j]) {
                if(setmin(slack[j], a[i0][j]-cx[i0]-cy[j]))
                    pre[j]=j0;
                if(setmin(minv, slack[j]))
                    minj=j;
            }
            cx[cur]+=minv;
            repn(j, n) if(vis[j]) {
                cx[lnk[j]]+=minv;
                cy[j]-=minv;
            } else {
                slack[j]-=minv;
            }
            j0=minj;
        }
        while(j0>=0) {
            int j=pre[j0];
            lnk[j0]=(j<0?cur:lnk[j]), j0=j;
        }
    }
    int ans=0; repn(j, n) ans+=a[lnk[j]][j];
    return ans;
}
