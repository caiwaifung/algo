#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;

typedef long long int64;

const int MAX_LENGTH = 3010;
const int MAX_NODES = MAX_LENGTH;
const int MAX_EDGES = MAX_NODES * 4;
const int64 MAX_VALUE = (int64)(1<<30) * (int64)(1<<30);

class Network {
    int edge_link[MAX_EDGES*2];
    int edge_oppo[MAX_EDGES*2];
    int64 edge_flow[MAX_EDGES*2];
    int edge_next[MAX_EDGES*2];
    int first_edge[MAX_NODES];
    int edge_count, node_count;
    int start_node, end_node;
    
    void insert_edge(int e, int e_op, int x, int y, int64 flow) {
        edge_link[e] = y;
        edge_oppo[e] = e_op;
        edge_flow[e] = flow;
        edge_next[e] = first_edge[x];
        first_edge[x] = e;
    }
    
    int queue[MAX_NODES];
    int64 flow[MAX_NODES];
    int pre_node[MAX_NODES];
    int pre_edge[MAX_NODES];
    
    int64 ford_fulkerson() {
        int64 answer = 0;
        while (true) {
            memset(flow, 0, sizeof(flow));
            int head = 0, tail = 1;
            flow[queue[tail]=start_node] = MAX_VALUE;
            while (head < tail)
                for (int cur = queue[++head], edge = first_edge[cur]; edge > 0; edge = edge_next[edge]) {
                    int tmp = edge_link[edge];
                    if (edge_flow[edge] > 0 && flow[tmp] == 0) {
                        queue[++ tail] = tmp;
                        flow[tmp] = min(flow[cur], edge_flow[edge]);
                        pre_node[tmp] = cur;
                        pre_edge[tmp] = edge;
                    }
                }
            if (flow[end_node] == 0)
                break;
            //printf("flow: %I64d\n", flow[end_node]);
            answer += flow[end_node];
            for (int node = end_node; node != start_node; node = pre_node[node]) {
                int edge = pre_edge[node];
                //printf("%d (%I64d)", node,edge_flow[edge]);
                edge_flow[edge] -= flow[end_node];
                edge_flow[edge_oppo[edge]] += flow[end_node];
            }
            //printf("\n");
        }
        return answer;
    }
    
public:
    
    void initalize(int nodes, int start, int end) {
        node_count = nodes;
        start_node = start;
        end_node = end;
        edge_count = 0;
        memset(first_edge, 0, sizeof(first_edge));
    }
    
    void add_edge(int x, int y, int64 flow) {
        //printf("add_edge %d -> %d flow=%I64d\n", x, y, flow);
        int e1 = ++ edge_count;
        int e2 = ++ edge_count;
        insert_edge(e1, e2, x, y, flow);
        insert_edge(e2, e1, y, x, 0);
    }
    
    int64 calculate_max_flow() {
        return ford_fulkerson();
    }
} network;

int number[MAX_LENGTH], value[MAX_LENGTH];
int length;

void init() {
    scanf("%d", &length);
    for (int i = 1; i <= length; i ++)
        scanf("%d", &number[i]);
    for (int i = 1; i <= length; i ++)
        scanf("%d", &value[i]);
}

bool check(int a, int b) {
    if (a % 2 == b % 2)
        return false;
    int c = (int)(sqrt((double)a*(double)a + (double)b*(double)b) + 0.2);
    if ((int64)a*(int64)a + (int64)b*(int64)b != (int64)c*(int64)c)
        return false;
    while (b != 0) {
        int tmp = a % b;
        a = b, b = tmp;
    }
    return a == 1;
}

void solve() {
    int start_node = length + 1;
    int end_node = length + 2;
    network.initalize(length + 2, start_node, end_node);
    int64 answer = 0;
    for (int i = 1; i <= length; i ++) {
        answer += value[i];
        if (number[i] % 2 == 0) {
            network.add_edge(start_node, i, (int64)value[i]);
            for (int j = 1; j <= length; j ++)
                if (check(number[i], number[j]))
                    network.add_edge(i, j, MAX_VALUE);
        } else
            network.add_edge(i, end_node, (int64)value[i]);
    }
    answer -= network.calculate_max_flow();
    cout << answer << endl;
}

int main() {
    freopen("g.in", "r", stdin);
    freopen("g.out", "w", stdout);
    int case_count;
    scanf("%d", &case_count);
    for (int case_id = 1; case_id <= case_count; case_id ++) {
        init();
        solve();
    }
    return 0;
}
