#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>
using namespace std;

typedef long long int64;

const int MAX_N = 80010;
const int MODULE = 1000000000+7;

int sequence[MAX_N];
int seq_len, query_count;

struct Value {
    int v[5];
    Value() {
        v[0] = v[1] = v[2] = v[3] = v[4] = 0;
    }
    Value(int val) {
        v[0] = 1;
        v[1] = (val%MODULE + MODULE) % MODULE;
        v[2] = v[3] = v[4] = 0;
    }
    friend Value operator +(const Value &a, const Value &b) {
        Value c;
        for (int i = 0; i <= 4; i ++)
            for (int j = 0; j <= 4-i; j ++)
                c.v[i+j] = (int)(((int64)c.v[i+j] + (int64)a.v[i]*(int64)b.v[j]) % MODULE);
        return c;
    }
};

Value tree[MAX_N * 4];

void modify(int x, int s, int t, int index, int val) {
    if (s == t) {
        tree[x] = Value(val);
        return;
    }
    int m = (s+t) >> 1;
    if (index <= m)
        modify(x*2, s, m, index, val);
    else
        modify(x*2+1, m+1, t, index, val);
    tree[x] = tree[x*2] + tree[x*2+1];
}

Value query(int x, int s, int t, int st, int en) {
    if (st <= s && t <= en)
        return tree[x];
    int m = (s+t) >> 1;
    if (en <= m) return query(x*2, s, m, st, en);
    if (m+1 <= st) return query(x*2+1, m+1, t, st, en);
    return query(x*2, s, m, st, en) + query(x*2+1, m+1, t, st, en);
}

int main() { 
	int T; scanf("%d", &T);
	while (T--) {   
		scanf("%d%d", &seq_len, &query_count);
		for (int i = 1; i <= seq_len; i ++) {
		    scanf("%d", &sequence[i]);
		    modify(1, 1, seq_len, i, sequence[i]);
		}    
		while (query_count --) {
		    char operation[10];
		    int x, y, z;
		    scanf("%s%d%d", operation, &x, &y);
		    if (operation[0] == 'I') {
		        sequence[x] += y;
		        modify(1, 1, seq_len, x, sequence[x]);
		    } else {
		        scanf("%d", &z);
		        Value ans = query(1, 1, seq_len, x, y);
		        for (int i = 1; i <= z; i ++)
		            printf("%d%c", ans.v[i], i<z ? ' ' : '\n');
		    }
		}
	}
    return 0;
}

