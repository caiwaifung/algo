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

const int MAX_LENGTH = 200010;
const int MAX_OPERATION = 100010;
const int MAX_NODES = MAX_LENGTH * 20;

int sequence[MAX_LENGTH];
int position[MAX_LENGTH];
bool inOperation[MAX_LENGTH];
int sequenceLength;
int operation[MAX_OPERATION];
int64 answer[MAX_OPERATION];
int operationCount;

bool init() {
    if (scanf("%d%d", &sequenceLength, &operationCount) == EOF)
        return false;
    for (int i = 1; i <= sequenceLength; i ++) {
        scanf("%d", &sequence[i]);
        position[sequence[i]] = i;
    }
    memset(inOperation, false, sizeof(inOperation));
    for (int i = 1; i <= operationCount; i ++) {
        scanf("%d", &operation[i]);
        inOperation[operation[i]] = true;
    }
    return true;
}

class Lists {
private:
    int firstNode[MAX_LENGTH];
    int nodeKey[MAX_NODES];
    int nodeNext[MAX_NODES];
    int nodeCount;
public:
    void clear() {
        memset(firstNode, 0xff, sizeof(firstNode));
        nodeCount = 0;
    }
    void add(int pos, int key) {
        nodeCount ++;
        nodeKey[nodeCount] = key;
        nodeNext[nodeCount] = firstNode[pos];
        firstNode[pos] = nodeCount;
    }
    void getArray(int pos, int array[], int &len) {
        len = 0;
        for (int node = firstNode[pos]; node > 0; node = nodeNext[node])
            array[++len] = nodeKey[node];
    }
} lists;
int tmpArray[MAX_LENGTH];

class Trees {
private:
    int key[MAX_NODES];
    int value[MAX_NODES];
    int lc[MAX_NODES];
    int rc[MAX_NODES];
    int nodeCount;
public:
    void clear() {
        value[0] = 0;
        nodeCount = 0;
    }
    int buildTree(int array[], int st, int en) {
        if (st > en)
            return 0;
        int mid = (st + en) / 2;
        int node = ++ nodeCount;
        key[node] = array[mid];
        value[node] = 0;
        lc[node] = buildTree(array, st, mid-1);
        rc[node] = buildTree(array, mid+1, en);
        return node;
    }
    void addValue(int node, int aimKey) {
        while (1) {
            value[node] ++;
            if (key[node] == aimKey)
                return;
            node = (aimKey < key[node] ? lc[node] : rc[node]);
        }
    }
    int countWithHigh(int node, int limit) {
        int ans = 0;
        while (node > 0)
            if (key[node] <= limit)
                ans += value[node] - value[rc[node]], node = rc[node];
            else
                node = lc[node];
        return ans;
    }
    int countWithLow(int node, int limit) {
        int ans = 0;
        while (node > 0)
            if (limit <= key[node])
                ans += value[node] - value[lc[node]], node = lc[node];
            else
                node = rc[node];
        return ans;
    }
} trees;
int roots[MAX_LENGTH];

void preCompute() {
    lists.clear();
    for (int i = 1; i <= sequenceLength; i ++)
        for (int x = i; x <= sequenceLength; x += (x&-x))
            lists.add(x, sequence[i]);
    trees.clear();
    for (int x = 1; x <= sequenceLength; x ++) {
        int len;
        lists.getArray(x, tmpArray, len);
        sort(tmpArray+1, tmpArray+len+1);
        roots[x] = trees.buildTree(tmpArray, 1, len);
    }
}

int countWithRightHigh(int x, int limit) {
    int ans = 0;
    for (; x > 0; x -= (x&-x))
        ans += trees.countWithHigh(roots[x], limit);
    return ans;
}

int countWithRightLow(int x, int limit) {
    int ans = 0;
    for (; x > 0; x -= (x&-x))
        ans += trees.countWithLow(roots[x], limit);
    return ans;
}

void addValue(int x, int key) {
    for (; x <= sequenceLength; x += (x&-x))
        trees.addValue(roots[x], key);
}

void solve() {
    preCompute();
    int64 countReverse = 0;
    for (int i = 1; i <= sequenceLength; i ++)
        if (!inOperation[sequence[i]]) {
            countReverse += countWithRightLow(i-1, sequence[i]+1);
            //cout << "reverse=" << countReverse << endl;
            addValue(i, sequence[i]);
        }
    for (int i = operationCount; i >= 1; i --) {
        int key = operation[i];
        int pos = position[key];
        countReverse += countWithRightLow(pos-1, key+1);
          //  cout << "xreverse=" << countReverse << endl;
        countReverse += countWithRightHigh(sequenceLength, key-1) - countWithRightHigh(pos, key-1);
          //  cout << "yreverse=" << countReverse << endl;
        answer[i] = countReverse;
        addValue(pos, key);
    }
    for (int i = 1; i <= operationCount; i ++)
        cout << answer[i] << endl;
}

int main() {
    //freopen("dsmall.in", "r", stdin);
    //freopen("dsmall.out", "w", stdout);
    //freopen("d.in", "r", stdin);
    //freopen("d.out", "w", stdout);
    while (init())
        solve();
    return 0;
}
