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

struct Record {
    int h, m, s;
    int Y, M, D;
    void clear() {
        h = m = s = 0;
        Y = -1, M = D = 1;
    }
    bool read() {
        return scanf("%d%d%d%d%d%d", &h, &m, &s, &Y, &M, &D) != EOF;
    }
    bool same_day(const Record &rec) {
        return Y == rec.Y && M == rec.M && D == rec.D;
    }
    bool in_morning() {
        if (h == 7) return true;
        if (h != 8) return false;
        if (m < 30) return true;
        return m == 30 && s == 0;
    }
    bool in_halfhour() {
        if (h >= 16 && h <= 20) return true;
        if (h != 21) return false;
        if (m < 30) return true;
        return m == 30 && s == 0;
    }
    bool delta_more_than_half_hour(const Record &rec) {
        int dh = rec.h - h;
        int dm = rec.m - m;
        int ds = rec.s - s;
        dm += dh * 60;
        ds += dm * 60;
        return ds >= 30 * 60;
    }
};

int main() {
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    
    int count_morning = 0, count_halfhour = 0;
    Record last, cur;
    last.clear();
    
    while (cur.read()) {
        if (!cur.in_morning() && !cur.in_halfhour())
            continue;
        if (!last.same_day(cur)) {
            if (cur.in_morning())
                count_morning ++;
            last = cur;
            continue;
        }
        if (cur.in_halfhour())
            if (last.in_morning())
                last = cur;
            else
                if (last.delta_more_than_half_hour(cur)) {
                    count_halfhour ++;
                    last.clear();
                }
    }
    count_morning = max(0, 10 - count_morning);
    count_halfhour = max(0, 20 - count_halfhour);
    printf("%d %d\n", count_morning, count_halfhour);
    /*
    int last_h = 0, last_m = 0, last_s = 0, last_Y = -1, last_M = 1, last_D = 1;
    int cur_h, cur_m, cur_s, cur_Y, cur_M, cur_D;
    while (scanf("%d%d%d%d%d%d", &cur_h, &cur_m, &cur_s, &cur_Y, &cur_M, &cur_D) != EOF)
        if (cur_Y == last_Y && cur_M == last_M && cur_D == last_M) {
        } else {
            
        }
    */
    return 0;
}
