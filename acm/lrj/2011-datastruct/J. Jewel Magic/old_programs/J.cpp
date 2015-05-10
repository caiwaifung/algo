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

class HashManager {
    vector<int64> powerMod;
    int64 modNumber;
public:
    void init(int maxLen) {
        modNumber = 1346985251LL;
        powerMod.resize(maxLen + 1);
        powerMod[0] = 1LL;
        for (int i = 1; i <= maxLen; i ++)
            powerMod[i] = powerMod[i-1]*2LL % modNumber;
    }
    int64 merge(int64 lKey, int64 midKey, int64 rKey, int rSize) {
      //  printf("begin merge rSize=%d\n",rSize); fflush(stdout);
        int64 result = (lKey * powerMod[rSize+1] + midKey * powerMod[rSize] + rKey) % modNumber;
      //  printf("end merge\n"); fflush(stdout);
        return result;
    }
} hashManager;

class Splay {
    struct SplayNode {
        int64 hashKey[2];
        int reversed;
        int key;
        int size;
        SplayNode *lChild, *rChild;
        
        void reverse() {
            reversed = !reversed;
            swap(hashKey[0], hashKey[1]);
            swap(lChild, rChild);
        }
        
        void clearReversion() {
            if (reversed) {
                lChild -> reverse();
                rChild -> reverse();
                reversed = false;
            }
        }
        
        void update() {
      //  printf("begin update\n"); fflush(stdout);
            hashKey[0] = hashManager.merge(lChild->hashKey[0], (int64)key, rChild->hashKey[0], rChild->size);
            hashKey[1] = hashManager.merge(rChild->hashKey[1], (int64)key, lChild->hashKey[1], lChild->size);
            size = lChild->size + rChild->size + 1;
       // printf("end update\n"); fflush(stdout);
        }
    } *root, *nullNode;
    
    SplayNode *lRotate(SplayNode *node) {
        SplayNode *son = node->lChild;
        son->clearReversion();
        node->lChild = son->rChild;
        son->rChild = node;
        node->update();
        son->update();
        return son;
    }
    
    SplayNode *rRotate(SplayNode *node) {
        SplayNode *son = node->rChild;
        son->clearReversion();
        node->rChild = son->lChild;
        son->lChild = node;
        node->update();
        son->update();
        //printf("after rRotate son=%d son.l=%d son.r=%d\n", son, son->lChild, son->rChild),fflush(stdout);
        return son;
    }
    
    SplayNode *splay(SplayNode *node, int index, bool isRoot) {
      //  printf("splay node=%d index=%d isRoot=%d\n", node,index,isRoot),fflush(stdout);
        if (index == node->lChild->size + 1)
            return node;
        node -> clearReversion();
        
        if (index <= node->lChild->size) {
            node->lChild = splay(node->lChild, index, false);
            node -> update();
            if (index == node->lChild->lChild->size + 1)
                if (isRoot) node = lRotate(node)/*, printf("splay: l\n"),fflush(stdout)*/; else;
            else
                if (index <= node->lChild->lChild->size)
                    node->lChild = lRotate(node->lChild), node = lRotate(node);//, printf("splay: l l\n"),fflush(stdout);
                else
                    node->lChild = rRotate(node->lChild), node = lRotate(node);//, printf("splay: l r\n"),fflush(stdout);
        } else {
            index -= node->lChild->size + 1;
            node->rChild = splay(node->rChild, index, false);
            node -> update();
          //  printf("index=%d  node.r.l.size=%d\n", index,node->rChild->lChild->size); fflush(stdout);
            if (index == node->rChild->lChild->size + 1)
                if (isRoot) node = rRotate(node)/*, printf("splay: r\n"),fflush(stdout)*/; else;
            else
                if (index <= node->rChild->lChild->size)
                    node->rChild = lRotate(node->rChild), node = rRotate(node);//, printf("splay: r l\n"),fflush(stdout);
                else
                    node->rChild = rRotate(node->rChild), node = rRotate(node);//, printf("splay: r r\n"),fflush(stdout);
        }
        return node;
    }
    
    SplayNode *splay(SplayNode *root, int index) {
        return splay(root, index, true);
    }
    
    SplayNode *insertNode(SplayNode *curNode, SplayNode *node, int index) {
       // printf("insert node index=%d  curNode=%d nullNode=%d\n", index,curNode,nullNode); fflush(stdout);
        if (curNode == nullNode) //{
           // printf("successd insert node=%d node.l=%d node.r=%d\n", node, node->lChild, node->rChild),fflush(stdout);
            return node;//}
        curNode -> clearReversion();
        if (index <= curNode->lChild->size)
            curNode->lChild = insertNode(curNode->lChild, node, index);
        else
            curNode->rChild = insertNode(curNode->rChild, node, index - curNode->lChild->size - 1);
        curNode -> update();
        return curNode;
    }
    
    SplayNode *mergeTrees(SplayNode *treeA, SplayNode *treeB) {
        if (treeA == nullNode) return treeB;
        if (treeB == nullNode) return treeA;
        treeB = splay(treeB, 1);
        treeB->lChild = treeA;
        return treeB;
    }
    
    void splitTree(SplayNode *node, int index, SplayNode *&treeA, SplayNode *&treeB) {
        if (index == 0) {
            treeA = nullNode;
            treeB = node;
            return;
        }
        node = splay(node, index);
        treeB = node->rChild;
        node->rChild = nullNode;
        treeA = node;
    }
    /*
    void reverseTree(SplayNode *node, int st, int en) {
        if (en < 1 || st > node->size)
            return;
        if (st <= 1 && node->size <= en) {
            node -> reverse();
            return;
        }
        int sz = node->lChild->size + 1;
        reverseTree(node->lChild, st, en);
        reverseTree(node->rChild, st-sz, en-sz);
    }*/
    
    int64 getHashKey(SplayNode *node, int ind) {
       // printf("begin getHashKey2 node=%d ind=%d\n",node,ind); fflush(stdout);
        if (ind == 0)
            return 0;
        if (ind <= node->lChild->size)
            return getHashKey(node->lChild, ind);
        else {
            ind -= node->lChild->size + 1;
            return hashManager.merge(node->lChild->hashKey[0], (int64)node->key, getHashKey(node->rChild, ind), ind);
        }
    }
    
    int64 getHashKey(SplayNode *root, int st, int en) {
        //printf("begin getHashKey\n"); fflush(stdout);
        if (st > 1)
            root = splay(root, st - 1);
        //printf("begin getHashKey2\n"); fflush(stdout);
        int64 result = getHashKey(root, en - st + 1);
       // printf("end getHashKey\n"); fflush(stdout);
        return result;
    }
    
    void clearChilds(SplayNode *node) {
        if (node->lChild != nullNode) {
            clearChilds(node->lChild);
            delete node->lChild;
        }
        if (node->rChild != nullNode) {
            clearChilds(node->rChild);
            delete node->rChild;
        }
    }
    
public:
    void init() {
        nullNode = new SplayNode;
        nullNode->lChild = nullNode->rChild = nullNode;
        nullNode->key = 0;
        nullNode->size = 0;
        nullNode->hashKey[0] = nullNode->hashKey[1] = 0LL;
        root = nullNode;
    }
    
    void clear() {
        if (root != nullNode) {
            clearChilds(root);
            delete root;
        }
        delete nullNode;
    }
    
    void insert(int index, int k) {
      //  printf("begin insert index=%d k=%d\n",index,k); fflush(stdout);
        
        SplayNode *node = new SplayNode;
        node->lChild = node->rChild = nullNode;
        node->key = k;
        node->size = 1;
        node->hashKey[0] = node->hashKey[1] = (int64)k;
        node->reversed = false;
        
      //  printf("inserting..\n"); fflush(stdout);
        root = insertNode(root, node, index);
      //  printf("splay..\n"); fflush(stdout);
        root = splay(root, index + 1);
       // printf("root.l=%d root.r=%d nullNode=%d splay\n",root->lChild,root->rChild,nullNode); fflush(stdout);
      //  printf("end insert index=%d k=%d\n\n\n",index,k); fflush(stdout);
    }
    
    void remove(int index) {
        root = splay(root, index);
        SplayNode *node = root;
        root = mergeTrees(root->lChild, root->rChild);
        delete node;
    }
    
    void reverse(int st, int en) {
        SplayNode *treeA, *treeB;
        splitTree(root, en, root, treeB);
        splitTree(root, st-1, treeA, root);
        root -> reverse();
        root = mergeTrees(treeA, root);
        root = mergeTrees(root, treeB);
    }
    
    int queryLCP(int indexA, int indexB) {
        int le = 0, ri = root->size - max(indexA, indexB) + 1;
        while (le < ri) {
            int mid = (le + ri + 1) / 2;
            int64 keyA = getHashKey(root, indexA, indexA + mid - 1);
            int64 keyB = getHashKey(root, indexB, indexB + mid - 1);
            if (keyA == keyB)
                le = mid;
            else
                ri = mid - 1;
        }
        return le;
    }
} splay;

bool mainProcedure() {
    int jewelsLength;
    int operationCount;
    
    if (scanf("%d%d", &jewelsLength, &operationCount) == EOF)
        return false;
        
    hashManager.init(jewelsLength + operationCount);
    splay.init();
    for (int i = 0; i < jewelsLength; i ++) {
        char c = getchar();
        while (c!='0' && c!='1') c = getchar();
       // printf("going to insert index=%d\n", i); fflush(stdout);
        splay.insert(i, c=='0'?0:1);
    }
    while (operationCount --) {
        int operation, p1, p2, c;
        scanf("%d", &operation);
        printf("opCount = %d\n", operationCount+1); fflush(stdout);
        switch (operation) {
            case 1:
                scanf("%d%d", &p1, &c);
                splay.insert(p1, c);
                break;
            case 2:
                scanf("%d", &p1);
                splay.remove(p1);
                break;
            case 3:
                scanf("%d%d", &p1, &p2);
                splay.reverse(p1, p2);
                break;
            case 4:
                scanf("%d%d", &p1, &p2);
                printf("%d\n", splay.queryLCP(p1, p2));
                break;             
        }
    }
    splay.clear();
    return true;
}

int main() {
    freopen("j.in", "r", stdin);
    freopen("j.out", "w", stdout);
    while (mainProcedure());
    return 0;
}
