template <class T> class SAM {
public:
    static constexpr int MAX_C = 26;
    struct State {
        const int len;
        const bool is_end;
        State *succ[MAX_C] = {nullptr}, *f = nullptr;
        T info;

        State(int len, bool is_end, State* copy = nullptr)
            : len(len), is_end(is_end) {
            if(copy) {
                memcpy(succ, copy->succ, sizeof(succ));
                f = copy->f;
            } else {
                assert(succ[20] == nullptr);
            }
        }
    };

    SAM() {
        last_ = root_ = new State(0, false);
        states_.pb(root_);
    }

    State* extend(int ch) {
        assert(ch >= 0 && ch < MAX_C);
        State *p = last_, *np = new State(p->len + 1, true);
        states_.pb(np);
        for(; p && !p->succ[ch]; p = p->f) {
            p->succ[ch] = np;
        }
        if(!p) {
            np->f = root_;
        } else {
            State* q = p->succ[ch];
            if(q->len == p->len + 1) {
                np->f = q;
            } else {
                State* nq = new State(p->len + 1, false, q);
                states_.pb(nq);
                np->f = q->f = nq;
                for(; p && p->succ[ch] == q; p = p->f) {
                    p->succ[ch] = nq;
                }
            }
        }
        return last_ = np;
    }

    void finish() {
        sort(all(states_),
             [](const State* p, const State* q) { return p->len < q->len; });
        states_rev_ = states_;
        reverse(all(states_rev_));
    }

    State* root() const { return root_; }
    const vector<State*> states_top_down() const { return states_; }
    const vector<State*> states_bottom_up() const { return states_rev_; }

private:
    State *last_, *root_;
    vector<State *> states_, states_rev_;
};
