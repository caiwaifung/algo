namespace SA {
int sa[MAXLEN], rank[MAXLEN], height[MAXLEN], limit[MAXLEN];
int wxa[MAXLEN], wxb[MAXLEN], wxc[MAXLEN];
char str[MAXLEN];
int len;
void cal_sa() {
    int *x=wxa, *y=wxb, *c=wxc, size=256;
    for(int i=0; i<=size; ++i) c[i]=0; //memset
    for(int i=1; i<=len; ++i) ++c[x[i]=(int)str[i]];
    for(int i=1; i<=size; ++i) c[i]+=c[i-1];
    for(int i=len; i>=1; --i) sa[c[x[i]]--]=i;

    for(int w=1; w<len; w*=2, size=len) {
        int p=0;
        for(int i=len-w+1; i<=len; ++i) y[++p]=i;
        for(int i=1; i<=len; ++i) if(sa[i]>w) y[++p]=sa[i]-w;

        for(int i=0; i<=size; ++i) c[i]=0; //memset
        for(int i=1; i<=len; ++i) ++c[x[i]];
        for(int i=1; i<=size; ++i) c[i]+=c[i-1];
        for(int i=len; i>=1; --i) sa[c[x[y[i]]]--]=y[i];
        std::swap(x, y); x[sa[1]]=1;
        for(int i=2; i<=len; ++i) {
            int j1=sa[i-1], j2=sa[i];
            int c1=y[j1], c2=y[j2];
            if(c1==c2) {
                c1=(j1+w<=len?y[j1+w]:0);
                c2=(j2+w<=len?y[j2+w]:0);
            }
            x[j2]=x[j1]+(c1<c2);
        }
    }
    for(int i=1; i<=len; ++i) rank[sa[i]]=i;
}
void cal_height() {
    for(int i=1, h=0; i<=len; ++i) {
        if(h>0) --h;
        int j=sa[rank[i]-1];
        while(i+h<=len && j+h<=len && str[i+h]==str[j+h])
            ++h;
        height[rank[i]]=h;
    }
}

int lcp_st[MAXLogN][MAXLEN];
int lcp_k[MAXLEN], lcp_w[MAXLEN];
void cal_lcp() {
    for(int i=2; i<=len; ++i) lcp_st[0][i]=height[i];
    for(int k=1, w=1; 2+w<=len; ++k, w*=2)
        for(int i=2; i+w<=len; ++i)
            lcp_st[k][i]=min(lcp_st[k-1][i], lcp_st[k-1][i+w]);
    for(int i=1, k=0, w=1; i<=len; ++i) {
        while(w*2<=i) w*=2, ++k;
        lcp_k[i]=k, lcp_w[i]=w;
    }
}
int lcp(int i, int j) {
    if(i==j) return limit[i];
    i=rank[i], j=rank[j]; if(i>j) swap(i, j);
    ++i;
    int k=lcp_k[j-i+1], w=lcp_w[j-i+1];
    return min(lcp_st[k][i], lcp_st[k][j-w+1]);
}

};
