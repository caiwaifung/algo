#include <iostream>
#include <algorithm>
using namespace std;

int msgTime[1000], msgPosi[1000];
int nMsg;

int main() {
    freopen("C-large-practice.in", "r", stdin);
    freopen("C-large-practice.out", "w", stdout);
    int cs;
    scanf("%d", &cs);
    for (int case_id = 1; case_id <= cs; case_id ++) {
        scanf("%d", &nMsg);
        for (int i = 0; i < nMsg; i ++)
            scanf("%d%d", &msgPosi[i], &msgTime[i]);
        
        int ans = 0;
        for (int i = 0; i < nMsg; i ++)
            for (int j = 0; j < nMsg; j ++) {
                int dist = abs(msgPosi[i] - msgPosi[j]);
                int t = abs(msgTime[i] - msgTime[j]);
                ans = max(ans, dist - t);
            }
        printf("Case #%d: %.2lf\n", case_id, (double)ans * 0.5);
    }
    return 0;
}
