struct DisjointSetNode {
    DisjointSetNode *f;
    Node() : f(NULL) { }
    Node *find() { return f==NULL ? this : f=f->find(); }
};
typedef DisjointSetNode Node;
