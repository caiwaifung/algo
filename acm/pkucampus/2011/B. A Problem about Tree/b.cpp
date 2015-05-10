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

const int MAX_NODES = 10010;
const int MAX_EDGES = MAX_NODES * 2;
const int MAX_LOG_NODES = 15;

struct Graph {
    int link[MAX_EDGES], next[MAX_EDGES];
    int first[MAX_NODES];
    int edge_count;
    void initalize() {
        memset(first, 0, sizeof(first));
        edge_count = 0;
    }
    void insert_edge(int a, int b) {
        link[++ edge_count] = b;
        next[edge_count] = first[a];
        first[a] = edge_count;
    }
} graph;

int up_node[MAX_NODES][MAX_LOG_NODES];
int index_start[MAX_NODES], index_end[MAX_NODES], index_count;
int depth[MAX_NODES];
int node_count;
int query_count;

void dfs(int node, int father, int cur_depth) {
    depth[node] = cur_depth;
    index_start[node] = ++ index_count;
    up_node[node][0] = father;
    for (int i = 0; up_node[node][i] > 0; i ++)
        up_node[node][i+1] = up_node[up_node[node][i]][i];
    for (int edge = graph.first[node]; edge > 0; edge = graph.next[edge])
        if (graph.link[edge] != father)
            dfs(graph.link[edge], node, cur_depth+1);
    index_end[node] = index_count;
}

void init() {
    graph.initalize();
    scanf("%d%d", &node_count, &query_count);
    for (int i = 1; i <= node_count-1; i ++) {
        int x, y;
        scanf("%d%d", &x, &y);
        graph.insert_edge(x, y);
        graph.insert_edge(y, x);
    }
    index_count = 0;
    memset(up_node, 0, sizeof(up_node));
    depth[0] = 0;
    dfs(1, 0, 1);
}

bool is_ancester(int node, int ancester) {
    return index_start[ancester] <=  index_start[node] && index_end[node] <= index_end[ancester];
}

void solve(int case_id) {
    while (query_count --) {
        int root, node;
        scanf("%d%d", &root, &node);
        if (is_ancester(root, node)) {
            for (int i = MAX_LOG_NODES-1; i >= 0; i --)
                if (depth[up_node[root][i]] > depth[node])
                    root = up_node[root][i];
            printf("%d\n", root);
        } else
            printf("%d\n", up_node[node][0]);
    }
}

int main() {
    //freopen("b.in", "r", stdin);
    //freopen("b.out", "w", stdout);
    int cs;
    scanf("%d", &cs);
    for (int case_id = 1; case_id <= cs; case_id ++) {
        init();
        solve(case_id);
    }
    return 0;
}
