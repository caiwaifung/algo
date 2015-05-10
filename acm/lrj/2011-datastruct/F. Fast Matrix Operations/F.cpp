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

const int MAX_ROWS = 22;

int rowCount, colCount;
int queryCount;

bool init() {
    if (scanf("%d%d%d", &rowCount, &colCount, &queryCount) == EOF)
        return false;    
    return true;
}

const int STREE_BUF_NONE = 0;
const int STREE_BUF_SET = 1;
const int STREE_BUF_ADD = 2;

struct SegmentTreeNode {
    int sumV, minV, maxV;
    int bufType, bufValue;
    int st, en;
    SegmentTreeNode *lChild, *rChild;
    
    SegmentTreeNode(int _st, int _en) {
        st = _st, en = _en;
        sumV = minV = maxV = 0;
        bufType = STREE_BUF_NONE;
        if (st == en)
            lChild = rChild = NULL;
        else {
            lChild = new SegmentTreeNode(st, (st+en)/2);
            rChild = new SegmentTreeNode((st+en)/2+1, en);
        }
    }
    
    void deleteChilds() {
        if (st == en)
            return;
        lChild -> deleteChilds();
        rChild -> deleteChilds();
        delete lChild;
        delete rChild;
    }
    
    bool fullyOutside(int le, int ri) {
        return (ri < st || en < le);
    }
    
    bool fullyInside(int le, int ri) {
        return (le <= st && en <= ri);
    }
    
    void setBuf(int type, int val) {
        if (type == STREE_BUF_SET) {
            sumV = val*(en-st+1);
            minV = maxV = val;
            bufType = STREE_BUF_SET;
            bufValue = val;
        }
        if (type == STREE_BUF_ADD) {
            sumV += val*(en-st+1);
            minV += val;
            maxV += val;
            if (bufType == STREE_BUF_NONE) {
                bufType = STREE_BUF_ADD;
                bufValue = val;
            } else
                bufValue += val;
        }
    }
    
    void clearBuf() {
        if (bufType == STREE_BUF_NONE)
            return;
        lChild -> setBuf(bufType, bufValue);
        rChild -> setBuf(bufType, bufValue);
        bufType = STREE_BUF_NONE;
    }
    
    void update() {
        sumV = lChild->sumV + rChild->sumV;
        minV = min(lChild->minV, rChild->minV);
        maxV = max(lChild->maxV, rChild->maxV);
    }
    
    void increase(int le, int ri, int val) {
        if (fullyOutside(le, ri))
            return;
        if (fullyInside(le, ri)) {
            setBuf(STREE_BUF_ADD, val);
            return;
        }
        clearBuf();
        lChild -> increase(le, ri, val);
        rChild -> increase(le, ri, val);
        update();
    }
    
    void setValue(int le, int ri, int val) {
        if (fullyOutside(le, ri))
            return;
        if (fullyInside(le, ri)) {
            setBuf(STREE_BUF_SET, val);
            return;
        }
        clearBuf();
        lChild -> setValue(le, ri, val);
        rChild -> setValue(le, ri, val);
        update();        
    }
    
    void query(int le, int ri, int &sumVal, int &minVal, int &maxVal) {
        //printf("[%d,%d] query (%d,%d)\n", st, en, le, ri);
        if (fullyOutside(le, ri))
            return;
        if (fullyInside(le, ri)) {
            sumVal += sumV;
            minVal = min(minVal, minV);
            maxVal = max(maxVal, maxV);
            return;
        }
        clearBuf();
        lChild -> query(le, ri, sumVal, minVal, maxVal);
        rChild -> query(le, ri, sumVal, minVal, maxVal);
    }
};

SegmentTreeNode *segmentTrees[MAX_ROWS];

void solve() {
    for (int row = 1; row <= rowCount; row ++)
        segmentTrees[row] = new SegmentTreeNode(1, colCount);
    while (queryCount --) {
        int operation, x1, y1, x2, y2, v;
        scanf("%d", &operation);
        switch (operation) {
            case 1:
                scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &v);
                for (int row = x1; row <= x2; row ++)
                    segmentTrees[row] -> increase(y1, y2, v);
                break;
            case 2:
                scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &v);
                for (int row = x1; row <= x2; row ++)
                    segmentTrees[row] -> setValue(y1, y2, v);
                break;
            case 3:
                scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
                int sumV = 0, minV = +1<<30, maxV = -1<<30;
                for (int row = x1; row <= x2; row ++)
                    segmentTrees[row] -> query(y1, y2, sumV, minV, maxV);
                printf("%d %d %d\n", sumV, minV, maxV);
                break;
        }
    }
    for (int row = 1; row <= rowCount; row ++) {
        segmentTrees[row] -> deleteChilds();
        delete segmentTrees[row];
    }
}

int main() {
    //freopen("fsmall.in", "r", stdin);
    //freopen("fsmall.out", "w", stdout);
    while (init())
        solve();
    return 0;
}
