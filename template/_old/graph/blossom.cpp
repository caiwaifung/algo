const int maxn=210;
vector<int> link[maxn];
int n; int match[maxn]; int Queue[maxn], head, tail;
int pred[maxn], base[maxn];
bool InQueue[maxn], InBlossom[maxn]; bool use[maxn];
int start, finish; int newbase;
void push(int u) {  Queue[tail++]=u; InQueue[u]=true; }
int pop() { return Queue[head++];}
int FindCommonAncestor(int u, int v) {
	bool InPath[maxn];  for(int i=0; i<n; i++) InPath[i]=0;
	while(true) {
		u=base[u];  InPath[u]=true;
		if(u==start) break; u=pred[match[u]];
	}
	while(true) { v=base[v]; if(InPath[v]) break; v=pred[match[v]]; }
	return v;
}
void ResetTrace(int u) {
	int v;
	while(base[u]!=newbase) {
		v=match[u]; InBlossom[base[u]]=InBlossom[base[v]]=true;
		u=pred[v]; if(base[u]!=newbase) pred[u]=v;
	}
}
void BlossomContract(int u, int v) {
	newbase=FindCommonAncestor(u, v);
	for(int i=0; i<n; ++i) InBlossom[i]=0;
	ResetTrace(u); ResetTrace(v);
	if(base[u]!=newbase) pred[u]=v;  if(base[v]!=newbase) pred[v]=u;
	for(int i=0; i<n; ++i) 
		if(InBlossom[base[i]]) {
			base[i]=newbase; if(!InQueue[i]) push(i);
		}
}
bool FindAugmentingPath(int u) {
	bool found=false;
	for(int i=0; i<n; ++i) pred[i]=-1, base[i]=i;
	for(int i=0; i<n; ++i) InQueue[i]=0;
	start=u; finish=-1; head=tail=0; push(start);
	while(head<tail) {
		int u=pop();
		for(int i=link[u].size()-1; i>=0; --i) {
			int v=link[u][i];
			if(use[u] && use[v] && base[u]!=base[v] && match[u]!=v) {
				if(v==start || (match[v]>=0 && pred[match[v]]>=0))
					BlossomContract(u, v);
				else if(pred[v]==-1) {pred[v]=u;
					if(match[v]>=0) push(match[v]);
					else {finish=v; return true;}
				}
			}
		}
	}
	return found;
}
void AugmentPath() {
	int u, v, w; u=finish;
	while(u>=0) { v=pred[u]; w=match[v]; match[v]=u; match[u]=v; u=w; }
}
void FindMaxMatching() {
	for(int i=0; i<n; ++i) match[i]=-1;
	for(int i=0; i<n; ++i)
		if(match[i]==-1 && use[i])
			if(FindAugmentingPath(i)) AugmentPath();
}
int main() {
	//编号0..n-1； link[i]为与i相连的点，双向边
	FindMaxMatching();
	int k=0; for(int i=0; i<n; ++i) if(match[i]>=0) ++k; // 已匹配k/2对
}
