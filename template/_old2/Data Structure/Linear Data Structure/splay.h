template<size_t MAXN> class Splay {
	struct Node {
		// values
		bool brev;
		// buffers
		int size;
		Node *c[2];
		void clear() {
			//init values
			brev=false; //init buffers
			size=0, c[0]=c[1]=NULL;
		}
		void update() {
			size=1; //init values
			for(int i=0; i<2; ++i) if(c[i]) {
				//update values
				size+=c[i]->size;
			}
		}
		void push(bool crev, /*...*/) {
			brev^=crev;
			if(crev) swap(c[0], c[1]);
			// ...
		}
		void release() {
			if(c[0]) c[0]->push(brev, /*...*/);
			if(c[1]) c[1]->push(brev, /*...*/);
			brev=false; //clear buffers
		}
	};
	Node nodes[MAXN], *curnode;
	void rotate(Node *&x, int i) {
		Node *y=x->c[i];
		x->c[i]=y->c[1-i];
		y->c[1-i]=x;
		x->update();
		y->update();
		x=y;
	}
	Node *splay(Node *root, int ind) {
		static Node *st[MAXN];
		static int sc[MAXN];
		int t=1;
		for(st[t]=root; ; ) {
			int tmp=ind-1; if(st[t]->c[0]) tmp-=st[t]->c[0]->size;
			st[t]->release();
			if(tmp==0) break;
			if(sc[t]=(tmp>0)) ind=tmp;
			st[t+1]=st[t]->c[sc[t]], ++t;
		}
		while(t>=3) {
			t-=2;
			if(sc[t]==sc[t+1])
				rotate(st[t], sc[t]);
			else
				rotate(st[t]->c[sc[t]], sc[t+1]);
			rotate(st[t], sc[t]);
			if(t>=2)
				st[t-1]->c[sc[t-1]]=st[t];
		}
		if(t==2)
			rotate(st[1], sc[1]);
		return st[1];
	}

public:
	Node *root;
	Splay() {
		curnode=nodes;
		(root=curnode++)->clear();
		(root->c[0]=curnode++)->clear();
		root->c[0]->update();
		root->update();
	}
	void insert(int ind, const int val) {
		root=splay(root, ind+2);
		Node *x=curnode++; x->clear(); x->v=val; x->update();
		x->c[0]=root->c[0]; root->c[0]=x;
		x->update();
		root->update();
	}
	void remove(int index) {
		root=splay(root, index);
		root->c[1]=splay(root->c[1], 2);
		root->c[1]->c[0]=NULL;
		root->c[1]->update();
		root->update();
	}
	void push_buffer(int le, int ri, bool brev, /*...*/) {
		root=splay(root, le);
		root->c[1]=splay(root->c[1], ri-le+2);
		root->c[1]->c[0]->push(brev, /*...*/);
		root->c[1]->update();
		root->update();
	}
	Node get_value(int le, int ri) {
		root=splay(root, le);
		root->c[1]=splay(root->c[1], ri-le+2);
		root->update();
		return *(root->c[1]->c[0]);
	}
	void revolve(int le, int ri, int times) {
		if(0==(times%=(ri-le+1))) return;
		int mi=ri-times;
		root=splay(root, mi+1);
		root->c[0]=splay(root->c[0], le);
		root->c[1]=splay(root->c[1], ri-mi+1);
		Node *tmp=root->c[0]; root->c[0]=tmp->c[1];
		tmp->c[1]=root->c[1]->c[0]; root->c[1]->c[0]=NULL;
		root->c[1]->update();
		root->update();
		tmp->update();
		root=splay(root, 1);
		root->c[0]=tmp;
		root->update();
	}
};
