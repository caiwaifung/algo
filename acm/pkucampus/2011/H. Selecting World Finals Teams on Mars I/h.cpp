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

const int MAX_CONTESTS = 10010;
const int MAX_TEAMS = 5010;
const int MAX_NODES = MAX_CONTESTS + MAX_TEAMS;

int edge_link[MAX_NODES*2], edge_next[MAX_NODES*2];
int first_edge[MAX_NODES];

char team_name[MAX_TEAMS][110];
int team_strength[MAX_TEAMS];
int contest_count, team_count;

void init() {
    memset(first_edge, 0, sizeof(first_edge));
    scanf("%d%d", &contest_count, &team_count);
    for (int i = 1, e = 0; i <= contest_count + team_count - 1; i ++) {
        int x, y;
        scanf("%d%d", &x, &y);
        edge_link[++ e] = y; edge_next[e] = first_edge[x]; first_edge[x] = e;
        edge_link[++ e] = x; edge_next[e] = first_edge[y]; first_edge[y] = e;
    }
    for (int i = 1; i <= team_count; i ++)
        scanf("%s%d", team_name[i], &team_strength[i]);
    team_strength[0] = 0;
}

bool cmp_as_strength(int x, int y) {
    return team_strength[x] < team_strength[y];
}

void update(pair<int, int> &a, int p) {
    if (cmp_as_strength(a.second, p))
        a.second = p;
    if (cmp_as_strength(a.first, a.second))
        swap(a.first, a.second);
}

pair<int, int> calculate(int node, int father) {
    if (node > contest_count)
        return make_pair(node - contest_count, 0);
    pair<int, int> result = make_pair(0, 0);
    for (int e = first_edge[node]; e > 0; e = edge_next[e]) {
        if (edge_link[e] == father) continue;
        pair<int, int> tmp = calculate(edge_link[e], node);
        update(result, tmp.first);
        update(result, tmp.second);
    }
    return result;
}

void solve() {
    vector<int> list;
    for (int e = first_edge[1]; e > 0; e = edge_next[e]) {
        pair<int, int> tmp = calculate(edge_link[e], 1);
        if (tmp.first > 0) list.push_back(tmp.first);
        if (tmp.second > 0) list.push_back(tmp.second);
    }
    sort(list.begin(), list.end(), cmp_as_strength);
    for (int i = list.size()-1; i >= 0; i --)
        printf("%s\n", team_name[list[i]]);
}

int main() {
    //freopen("h.in", "r", stdin);
    //freopen("h.out", "w", stdout);
    init();
    solve();
    return 0;
}
