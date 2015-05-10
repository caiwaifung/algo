#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;

int combine[26][26];
bool opposed[26][26];
char sequence[110];
int lenSequence;

void init() {
    memset(combine, 0xff, sizeof(combine));
    memset(opposed, false, sizeof(opposed));
    int cnt;
    char str[10];
    scanf("%d", &cnt);
    while (cnt --) {
        scanf("%s", str);
        combine[str[0]-'A'][str[1]-'A'] = combine[str[1]-'A'][str[0]-'A'] = str[2]-'A';
    }
    scanf("%d", &cnt);
    while (cnt --) {
        scanf("%s", str);
        opposed[str[0]-'A'][str[1]-'A'] = opposed[str[1]-'A'][str[0]-'A'] = true;
    }
    scanf("%d%s", &lenSequence, sequence);
}

void solve(int case_id) {
    vector<char> list;
    for (int i = 0; i < lenSequence; i ++) {
        int cur = sequence[i]-'A';
        while (list.size() > 0 && combine[list.back()][cur] >= 0) {
            cur = combine[list.back()][cur];
            list.pop_back();
        }
        bool flag = true;
        for (vector<char>::iterator it = list.begin(); it != list.end(); ++ it)
            if (opposed[*it][cur])
                flag = false;
        if (flag)
            list.push_back(cur);
        else
            list.clear();
    }
    printf("Case #%d: [", case_id);
    
    for (int i = 0; i+1 < list.size(); i ++)
        printf("%c, ", 'A'+list[i]);        
    if (list.size() > 0)
        printf("%c", 'A'+list[list.size()-1]);
    printf("]\n");
}

int main() {
    freopen("B-large.in", "r", stdin);
    freopen("B-large.out", "w", stdout);
    int cs;
    scanf("%d", &cs);
    for (int case_id = 1; case_id <= cs; case_id ++) {
        init();
        solve(case_id);
    }
    return 0;
}
