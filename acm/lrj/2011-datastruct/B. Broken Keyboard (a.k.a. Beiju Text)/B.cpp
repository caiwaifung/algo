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

const int MAX_LEN = 100010;

char rawText[MAX_LEN];
int textLen;

bool init() {
    if (scanf("%s", rawText) == EOF)
        return false;
    textLen = strlen(rawText);
    return true;
}

char nodeChar[MAX_LEN];
int nodeLeft[MAX_LEN];
int nodeRight[MAX_LEN];
int nodeCount;
int nodeHead, nodeTail;

void solve() {
    nodeCount = 2;
    nodeHead = 1, nodeTail = 2;
    nodeRight[nodeHead] = nodeTail;
    nodeLeft[nodeTail] = nodeHead;
    int currentPosition = nodeHead;
    for (int i = 0; i < textLen; i ++) {
        if (rawText[i] == '[') {
            currentPosition = nodeHead;
            continue;
        }
        if (rawText[i] == ']') {
            currentPosition = nodeLeft[nodeTail];
            continue;
        }
        int node = ++ nodeCount;
        nodeChar[node] = rawText[i];
        nodeLeft[node] = currentPosition;
        nodeRight[node] = nodeRight[currentPosition];
        nodeRight[nodeLeft[node]] = node;
        nodeLeft[nodeRight[node]] = node;
        currentPosition = node;
    }
    for (int node = nodeRight[nodeHead]; node != nodeTail; node = nodeRight[node])
        printf("%c", nodeChar[node]);
    printf("\n");
}

int main() {
    //freopen("b.in", "r", stdin);
    //freopen("b.out", "w", stdout);
    while (init())
        solve();
    return 0;
}
