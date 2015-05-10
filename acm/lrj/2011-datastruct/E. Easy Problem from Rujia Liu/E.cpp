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

const int MAX_LENGTH = 100010;

int sequence[MAX_LENGTH];
int sequenceLength;
int queryCount;

bool init() {
    if (scanf("%d%d", &sequenceLength, &queryCount) == EOF)
        return false;
    for (int i = 1; i <= sequenceLength; i ++)
        scanf("%d", &sequence[i]);
    return true;
}

pair<int, int> list[MAX_LENGTH];
int firstOccurrence[1000010];
int countOccurrence[1000010];

void solve() {
    for (int i = 1; i <= sequenceLength; i ++)
        list[i] = make_pair(sequence[i], i);
    sort(list+1, list+sequenceLength+1);
    memset(countOccurrence, 0, sizeof(countOccurrence));
    for (int i = 1; i <= sequenceLength; i ++)
        if ((++ countOccurrence[list[i].first]) == 1)
            firstOccurrence[list[i].first] = i;
    while (queryCount --) {
        int k, v;
        scanf("%d%d", &k, &v);
        if (countOccurrence[v] < k)
            printf("0\n");
        else
            printf("%d\n", list[firstOccurrence[v]+k-1].second);
    }
}

int main() {
    //freopen("esmall.in", "r", stdin);
    //freopen("esmall.out", "w", stdout);
    while (init())
        solve();
    return 0;
}
