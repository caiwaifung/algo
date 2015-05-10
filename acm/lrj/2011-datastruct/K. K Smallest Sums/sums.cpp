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

const int MAX_N = 1010;

typedef long long int64;

int number[MAX_N][MAX_N];
int delta[MAX_N][MAX_N];
int64 min_sum;
int n;

bool init() {
    if (scanf("%d", &n) == EOF)
        return false;
    min_sum = 0;
    for (int row = 1; row <= n; row ++) {
        for (int col = 1; col <= n; col ++)
            scanf("%d", &number[row][col]);
        sort(number[row] + 1, number[row] + n + 1);
        min_sum += number[row][1];
        for (int col = 1; col < n; col ++)
            delta[row][col] = number[row][col+1] - number[row][col];
    }
    return true;
}

class Heap {
    pair<int64, int> h[MAX_N];
    int size;
public:
    void initalize() {
        size = 0;
    }
    void push(pair<int64, int> key) {
        h[++ size] = key;
        int j = size, i = size/2;
        while (i >= 1 && h[i] > h[j]) {
            swap(h[i], h[j]);
            j = i, i = i/2;
        }
    }
    pair<int64, int> pop() {
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

class Plan {
    int index[MAX_N];
    pair<int, int> it[MAX_N];
    int it_size;
    void sort_it() {
        for (int i = 2; i <= it_size; i ++)
            if (it[i].first < it[1].first)
                swap(it[i], it[1]);
    }
public:
    int64 sum;
    void initalize(const int index_arr[], const int64 s) {
        sum = s;
        memmove(&index[1], &index_arr[1], sizeof(index[1]) * n);
        it_size = 0;
        for (int i = 1; i <= n; i ++) {
            if (index[i] < n)
                it[++ it_size] = make_pair(delta[i][index[i]], i);
            if (index[i] > 1)
                break;
        }
        sort_it();
    }
    int64 get_min_cost() {
        return it_size == 0 ? -1 : (sum + it[1].first);
    }
    void set_min_to(Plan &plan) {
        index[it[1].second] ++;
        plan.initalize(index, sum + it[1].first);
        index[it[1].second] --;
        it[1] = it[it_size --];
        sort_it();
    }
} plans[MAX_N];
int tmp[MAX_N];

void add(int index) {
    int64 cost = plans[index].get_min_cost();
    if (cost >= 0)
        heap.push(make_pair(cost, index));
}

void solve() {
    heap.initalize();
    for (int i = 1; i <= n; i ++)
        tmp[i] = 1;
    plans[1].initalize(tmp, min_sum);
    add(1);
    for (int cur_index = 2; cur_index <= n; cur_index ++) {
        pair<int64, int> cur = heap.pop();
        plans[cur.second].set_min_to(plans[cur_index]);
        add(cur.second);
        add(cur_index);
    }
    for (int i = 1; i <= n; i ++)
        cout << plans[i].sum << (i < n ? ' ' : '\n');
}

int main() {
    //freopen("sums.in", "r", stdin);
    //freopen("sums.out", "w", stdout);
    
    while (init())
        solve();
    
    return 0;
}
