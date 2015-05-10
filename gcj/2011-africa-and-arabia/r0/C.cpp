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

vector<string> grid;
int tot[55][55];
int height, width;

void init() {
    cin >> width >> height;
    grid.resize(height);
    for (int i = 0; i < height; i ++)
        cin >> grid[i];
}

void solve(int case_id) {
    memset(tot, 0, sizeof(tot));
    for (int x= height-1; x >= 0; x --)
        for (int y = width-1; y >= 0; y --)
            tot[x][y] = tot[x+1][y] + tot[x][y+1] - tot[x+1][y+1] + ((grid[x][y] == 'G' || grid[x][y] == 'S') ? 0 : 1);
    int maxArea = 0;
    for (int x1 = 0; x1 < height; x1 ++)
        for (int y1 = 0; y1 < width; y1 ++)
            for (int x2 = 0; x2 < height; x2 ++)
                for (int y2 = 0; y2 < width; y2 ++)
                    if (tot[x1][y1] - tot[x1][y2+1] - tot[x2+1][y1] + tot[x2+1][y2+1] == 0)
                        maxArea = max(maxArea, (y2-y1+1) * (x2-x1+1));
    printf("Case #%d: %d\n", case_id, maxArea);                        
}

int main() {
    freopen("C-large-practice.in", "r", stdin);
    freopen("C-large-practice.out", "w", stdout);
    int cs;
    cin >> cs;
    for (int case_id = 1; case_id <= cs; case_id ++) {
        init();
        solve(case_id);
    }
    return 0;
}
