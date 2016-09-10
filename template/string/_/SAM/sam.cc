struct State {
    State* succ[26];
    State* f;
    int l;
    State(int _l, State* copy=nullptr) {
        if(copy!=nullptr) *this=*copy;
        l=_l;
    }
} *last, *root;

void extend(int ch) {
    State* p=last;
    State* np=new State(p->l+1);
    for(; p && p->succ[ch]==nullptr; p=p->f)
        p->succ[ch]=np;
    if(p==nullptr) {
        np->f=root;
    } else {
        State* q=p->succ[ch];
        if(q->l==p->l+1) {
            np->f=q;
        } else {
            State* nq=new State(p->l+1, q);
            np->f=q->f=nq;
            for(; p && p->succ[ch]==q; p=p->f)
                p->succ[ch]=nq;
        }
    }
    last=np;
}
