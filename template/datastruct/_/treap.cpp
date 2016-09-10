class Treap { //{{{
    struct Node {
        int val, rkey;
        int l, r, size;
    } tr[10010];
    int num, root;

    void update(int x) {
        tr[x].size=tr[tr[x].l].size+tr[tr[x].r].size+1;
    }
    int lrotate(int x) {
        int y=tr[x].l; tr[x].l=tr[y].r; tr[y].r=x;
        update(x); update(y);
        return y;
    }
    int rrotate(int x) {
        int y=tr[x].r; tr[x].r=tr[y].l; tr[y].l=x;
        update(x); update(y);
        return y;
    }
    int insert(int x, int y) {
        if(x==0) return y;
        if(tr[y].val<tr[x].val) {
            tr[x].l=insert(tr[x].l, y);
            if(tr[tr[x].l].rkey>tr[x].rkey)
                x=lrotate(x);
        }
        else {
            tr[x].r=insert(tr[x].r, y);
            if(tr[tr[x].r].rkey>tr[x].rkey)
                x=rrotate(x);
        }
        update(x);
        return x;
    }
    int remove(int x, int val) {
        if(tr[x].val==val) {
            if(tr[x].l==0 && tr[x].r==0)
                return 0;
            if(tr[tr[x].l].rkey>tr[tr[x].r].rkey) {
                x=lrotate(x);
                tr[x].r=remove(tr[x].r, val);
            }
            else {
                x=rrotate(x);
                tr[x].l=remove(tr[x].l, val);
            }
        }
        else {
            if(val<tr[x].val)
                tr[x].l=remove(tr[x].l, val);
            else
                tr[x].r=remove(tr[x].r, val);
        }
        update(x);
        return x;
    }
    int ask(int x, int ind) {
        assert(ind<=tr[x].size);
        int ls=tr[tr[x].l].size;
        if(ind<=ls)
            return ask(tr[x].l, ind);
        if(ind==ls+1)
            return tr[x].val;
        return ask(tr[x].r, ind-ls-1);
    }

public:
    void init() {
        num=root=0;
        tr[0].rkey=-1;
        tr[0].size=0;
    }
    void add(int val) {
        int x=++num;
        tr[x].val=val, tr[x].rkey=rand();
        tr[x].l=tr[x].r=0, tr[x].size=1;
        root=insert(root, x);
    }
    void del(int val) {
        root=remove(root, val);
    }
    int query(int ind) {
        return ask(root, ind);
    }
}; //}}}
