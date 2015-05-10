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

int commandType[1010], commandValue[1010];
int commandCount;

bool init() {
    if (scanf("%d", &commandCount) == EOF)
        return false;
    for (int i = 1; i <= commandCount; i ++)
        scanf("%d%d", &commandType[i], &commandValue[i]);
    return true;
}

int array[1010];

bool checkStack() {
    int top = 0;
    for (int i = 1; i <= commandCount; i ++)
        if (commandType[i] == 1)
            array[++top] = commandValue[i];
        else
            if (top == 0 || array[top--] != commandValue[i])
                return false;
    return true;
}

bool checkQueue() {
    int st = 1, en = 0;
    for (int i = 1; i <= commandCount; i ++)
        if (commandType[i] == 1)
            array[++en] = commandValue[i];
        else
            if (st > en || array[st++] != commandValue[i])
                return false;
    return true;
}

bool checkPriorityQueue() {
    int len = 0;
    for (int i = 1; i <= commandCount; i ++)
        if (commandType[i] == 1)
            array[++len] = commandValue[i];
        else {
            if (len == 0)
                return false;
            int ind = 1;
            for (int k = 2; k <= len; k ++)
                if (array[k] > array[ind])
                    ind = k;
            if (array[ind] != commandValue[i])
                return false;
            array[ind] = array[len--];
        }
    return true;
}

void solve() {
    bool isStack = checkStack();
    bool isQueue = checkQueue();
    bool isPriorityQueue = checkPriorityQueue();
    int cnt = 0;
    if (isStack) cnt ++;
    if (isQueue) cnt ++;
    if (isPriorityQueue) cnt ++;
    if (cnt == 0)
        printf("impossible\n");
    else if (cnt > 1)
        printf("not sure\n");
    else if (isStack)
        printf("stack\n");
    else if (isQueue)
        printf("queue\n");
    else if (isPriorityQueue)
        printf("priority queue\n");
}

int main() {
  //  freopen("ismall.in", "r", stdin);
   // freopen("ismall.out", "w", stdout);
    while (init())
        solve();
    return 0;
}
