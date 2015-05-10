#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
using namespace std;

bool connected[1000][1000];
int degree[1000];
vector<int> list;
bool visited[1000];
int nCities, nRoads;

void dfs(int x) {
    //printf("dfs %d\n", x);
    visited[x] = true;
    list.push_back(x);
    for (int y = 0; y < nCities; y ++)
        if (!visited[y] && connected[x][y])
            dfs(y);
}

void solve(int case_id) {
    scanf("%d%d", &nCities, &nRoads);
    memset(degree, 0, sizeof(degree));
    memset(connected, false, sizeof(connected));
    for (int i = 0; i < nRoads; i ++) {
        int x, y;
        scanf("%d%d", &x, &y);
        connected[x][y] = connected[y][x] = true;
        degree[x] ++;
        degree[y] ++;
    }
    
    vector<int> odds;
    memset(visited, false, sizeof(visited));
    for (int i = 0; i < nCities; i ++)
        if (!visited[i]) {
            list.clear();
            dfs(i);
            if (list.size() == 1 && degree[list[0]] == 0)
                continue;
            int tot = 0;
            for (int k = 0; k < list.size(); k ++)
                if (degree[list[k]] & 1)
                    tot ++;
            odds.push_back(tot);
        }
        
    int ans;
    if (odds.size() == 1)
        ans = odds[0] / 2;
    else {
        ans = odds.size();
        for (int i = 0; i < odds.size(); i ++)
            if (odds[i] > 2)
                ans += (odds[i] - 2) / 2;
    }
    printf("Case #%d: %d\n", case_id, ans);
}

int main() {
    freopen("B-small-practice.in", "r", stdin);
    freopen("B-small-practice.out", "w", stdout);
    int cs;
    scanf("%d", &cs);
    for (int i = 1; i <= cs; i ++)
        solve(i);
    return 0;
}
