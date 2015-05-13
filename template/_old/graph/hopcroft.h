int Maxmatch(){
	memset(mk,-1,sizeof(mk));memset(cx,-1,sizeof(cx));
	memset(cy,-1,sizeof(cy));
	for(int p=1, fl=1, h, tail; fl; ++p) {
		fl=0;
		h=tail=0;
		for(int i=0; i<n; ++i) if(cx[i]==-1)
			q[++tail]=i, pre[i]=-1, src[i]=i;
		for(h=1; h<=tail; ++h){
			int u=q[h];
			if(cx[src[u]]!=-1) continue;
			for(int pp=head[u], v=vtx[pp]; pp; pp=next[pp], v=vtx[pp])
				if(mk[v]!=p) {
					mk[v]=p; q[++tail]=cy[v];
					if(cy[v]>=0) {
						pre[cy[v]]=u; src[cy[v]]=src[u];continue;
					}
					int d,e,t;
					for(--tail,fl=1,d=u,e=v; d!=-1;
						t=cx[d],cx[d]=e,cy[e]=d,e=t,d=pre[d]);
					break;
				}
		}
	}
	int res=0; for (int i=0;i<n;++i) res+=(cx[i]!=-1); return res;
}
