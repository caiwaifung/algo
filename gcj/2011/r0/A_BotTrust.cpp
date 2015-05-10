#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

int commandAim[110];
int commandType[110];
int nextAim[110][2];
int commandCount;

void init() {
    scanf("%d", &commandCount);
    for (int i = 1; i <= commandCount; i ++) {
        char buf[10];
        scanf("%s%d", buf, &commandAim[i]);
        commandType[i] = (buf[0]=='O' ? 0 : 1);
    }
    nextAim[commandCount+1][0] = nextAim[commandCount+1][1] = -1;
    for (int i = commandCount; i >= 1; i --) {
        nextAim[i][0] = nextAim[i+1][0];
        nextAim[i][1] = nextAim[i+1][1];
        nextAim[i][commandType[i]] = commandAim[i];
    }
}

void solve(int case_id) {
    int ans = 0;
    int position[2] = {1, 1};
    for (int i = 1; i <= commandCount; i ++) {
        int curPeople = commandType[i];
        int anotherPeople = 1-curPeople;
        int period = abs(commandAim[i] - position[curPeople]) + 1;
        ans += period;
        position[curPeople] = commandAim[i];
        int nextP = nextAim[i][anotherPeople];
        //printf("nextP=%d
        if (nextP >= 0)
            if (abs(nextP - position[anotherPeople]) <= period)
                position[anotherPeople] = nextP;
            else
                position[anotherPeople] += period * (position[anotherPeople] < nextP ? 1 : -1);
        //printf("period=%d p0=%d p1=%d\n", period,position[0],position[1]);
    }
    printf("Case #%d: %d\n", case_id, ans);
}

int main() {
    freopen("A-large.in", "r", stdin);
    freopen("A-large.out", "w", stdout);
    int cs;
    scanf("%d", &cs);
    for (int case_id = 1; case_id <= cs; case_id ++) {
        init();
        solve(case_id);
    }
    return 0;
}
