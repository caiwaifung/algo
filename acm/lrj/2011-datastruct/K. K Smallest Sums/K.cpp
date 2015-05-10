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

int number[755][755];
int size;

bool init() {
    if (scanf("%d", &size) == EOF)
        return false;
    for (int row = 1; row <= size; row ++) {
        for (int col = 1; col <= size; col ++)
            scanf("%d", &number[row][col]);
        sort(number[row] + 1, number[row] + size + 1);
    }
    return true;
}

class Heap {
    pair<int, int> h[755];
    int size;
public:
    void initalize() {
        size = 0;
    }
    void push(pair<int, int> key) {
        h[++ size] = key;
        int j = size, i = size/2;
        while (i >= 1 && h[i] > h[j]) {
            swap(h[i], h[j]);
            j = i, i = i/2;
        }
    }
    pair<int, int> pop() {
        pair<int, int> result = h[1];
        h[1] = h[size --];
        int i = 1, j = 2;
        while (j <= size) {
            if (j < size && h[j+1] < h[j])
                j ++;
            if (h[i] < h[j])
                break;
            swap(h[i], h[j]);
            i = j, j = j*2;
        }
        return result;
    }
} heap;

int ind[755];

void merge(int a[], int b[], int c[]) {
    heap.initalize();
    for (int col = 1; col <= size; col ++)
        heap.push(make_pair(a[col] + b[ind[col]=1], col));
    for (int cur = 1; cur <= size; cur ++) {
        pair<int, int> key = heap.pop();
        c[cur] = key.first;
        int col = key.second;
        if (++ind[col] <= size)
            heap.push(make_pair(a[col] + b[ind[col]], col));
    }
}

void solve() {
    for (int row = 2; row <= size; row ++) {
        merge(number[row-1], number[row], number[0]);
        memmove(number[row], number[0], sizeof(number[0]));
    }
    for (int i = 1; i <= size; i ++)
        printf("%d%c", number[size][i], i<size ? ' ' : '\n');
}

int main() {
    //freopen("k.in", "r", stdin); freopen("k.out", "w", stdout);
    //freopen("ksmall.in", "r", stdin); freopen("ksmall.out", "w", stdout);
    while (init())
        solve();
    return 0;
}
