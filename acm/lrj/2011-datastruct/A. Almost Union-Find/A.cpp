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

const int MAX_NODES = 100010;
const int MAX_QUERYS = 100010;

int64 unionSum[MAX_NODES+MAX_QUERYS];
int unionCount[MAX_NODES+MAX_QUERYS];
int father[MAX_NODES+MAX_QUERYS];
int nodeIndex[MAX_NODES];
int nodeCount;
int queryCount;

bool init() {
    if (scanf("%d%d", &nodeCount, &queryCount) == EOF)
        return false;
    return true;
}

int getFather(int x) {
    int node = x;
    while (father[node] != node)
        node = father[node];
    while (x != node) {
        int tmp = father[x];
        father[x] = node;
        x = tmp;
    }
    return node;
}

void solve() {
    for (int i = 1; i <= nodeCount; i ++) {
        nodeIndex[i] = i;
        unionSum[i] = (int64)i;
        unionCount[i] = 1;
        father[i] = i;
    }
    while (queryCount --) {
        int op, nodeA, nodeB, fatherA, fatherB;
        scanf("%d", &op);
        switch (op) {
            case 1:
                scanf("%d%d", &nodeA, &nodeB);
                fatherA = getFather(nodeIndex[nodeA]);
                fatherB = getFather(nodeIndex[nodeB]);
                if (fatherA != fatherB) {
                    unionSum[fatherA] += unionSum[fatherB];
                    unionCount[fatherA] += unionCount[fatherB];
                    father[fatherB] = fatherA;
                }
                break;
            case 2:
                scanf("%d%d", &nodeA, &nodeB);
                fatherA = getFather(nodeIndex[nodeA]);
                fatherB = getFather(nodeIndex[nodeB]);
                unionSum[fatherA] -= nodeA;
                unionCount[fatherA] --;
                unionSum[fatherB] += nodeA;
                unionCount[fatherB] ++;
                father[nodeIndex[nodeA] = ++ nodeCount] = fatherB;
                break;
            case 3:
                scanf("%d", &nodeA);
                fatherA = getFather(nodeIndex[nodeA]);
                cout << unionCount[fatherA] << " " << unionSum[fatherA] << endl;
                break;
        }
    }
}

int main() {
    //freopen("a.in", "r", stdin);
    //freopen("a.out", "w", stdout);
    while (init())
        solve();
    return 0;
}
