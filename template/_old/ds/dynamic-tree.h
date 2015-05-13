class DynamicTree {
	struct Node {
		/*信息 e.g. v, vmax*/
		bool brev; /*其他可传递信息 e.g. bsum*/
		Node *c[2], *p;
		bool isroot() { return !p || (p->c[0]!=this && p->c[1]!=this); }
		void clear() {
			/*清空信息 e.g. v=vmax=0*/
			brev=false; /*清空可传递信息 e.g. bsum=0*/
			c[0]=c[1]=p=NULL;
		}
		void push(bool crev, /*其他可传递信息 e.g. csum*/) {
			brev^=crev; if(crev) swap(c[0], c[1]);
			/*push e.g. bsum+=csum, v+=csum, vmax+=csum*/
		}
		void update() { /*e.g. vmax=max(v, max(c[0]->vmax,c[1]->vmax))*/ }
		void release() {                 //!!!!^^^^ 注意要判断c[0/1]!=NULL
			for(int i=0; i<2; ++i)
				if(c[i]) c[i]->push(brev, /*...*/);
			brev=false; /*清空可传递信息 e.g. bsum=0*/
		}
	} *nodes, **stack;
	void rotate(Node *x, int i) {
		Node *y=x->c[i];
		y->p=x->p; x->p=y;
		if(y->p) {
			if(y->p->c[0]==x) y->p->c[0]=y;
			if(y->p->c[1]==x) y->p->c[1]=y;
		}
		x->c[i]=y->c[1-i]; if(x->c[i]) x->c[i]->p=x;
		y->c[1-i]=x;
		x->update(); y->update();
	}
	void splay(Node *x) {
		Node *y, *z;
		int cy, cz, top;
		stack[top=1]=x;
		for(y=x; !y->isroot(); ) stack[++top]=(y=y->p);
		while(top>=1) stack[top--]->release();
		while(!x->isroot()) {
			cy=((y=x->p)->c[1]==x);
			if(y->isroot()) rotate(y, cy);
			else {
				cz=((z=y->p)->c[1]==y);
				if(cy==cz) rotate(z, cz), rotate(y, cy);
					else rotate(y, cy), rotate(z, cz);
			}
		}
	}
	Node *head(Node *x) {
		for(x->release(); x->c[0]; x=x->c[0])
			x->release();
		splay(x); return x;
	}
	Node *expose(Node *x) {
		Node *y;
		for(y=NULL; x; y=x, x=x->p) {
			splay(x);  x->c[1]=y;  x->update();
		}
		return y;
	}
public:
	void initialize(int n) {
		nodes=new Node[n+1];
		stack=new Node*[n+1];
		for(int i=1; i<=n; ++i) (nodes+i)->clear();
	}
	void change_root(int x) { expose(nodes+x)->push(true, /*e.g. 0*/); }
	int get_root(int x) { return head(expose(nodes+x))-nodes; }
	void connect(int x, int y) {
		change_root(x); splay(nodes+x);
		(nodes+x)->p=(nodes+y);
	}
	void cut(int x) {
		Node *p=nodes+x;
		splay(p);
		if(p->c[0]) {
			p->c[0]->p=p->p;
			p->c[0]=p->p=NULL;
		} else p->p=NULL;
	}
	void modify(int x, /*e.g. w*/) {
		expose(nodes+x)->push(false, /*e.g. w*/);
	}
	Node query(int x) {
		return *expose(nodes+x);
	}
};
