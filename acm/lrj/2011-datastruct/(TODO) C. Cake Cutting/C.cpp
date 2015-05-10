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

const int MAX_NODES = 200100;

struct HalfPlane {
    double x1, y1, x2, y2;
    double arcTan;
};

struct Treap {
    struct TreapNode {
        HalfPlane halfplane;
        int left, right;
        int lc, rc, randomKey;
    } nodes[MAX_NODES];
    int root;
    int _insert(int x, HalfPlane halfplane)
} treap;

bool init() {
}

void solve() {
}

int main() {
    freopen("c.in", "r", stdin);
    freopen("c.out", "w", stdout);
    srand(123456798);
    while (init())
        solve();
    return 0;
}
