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

map<string, int> word_index;
string start_word, end_word;
string word[6010];
int word_count;

bool get_word(string &word) {
    char s[20];
    if (scanf("%s", s) == EOF)
        return false;
    word = string(s);
    return true;
}

void init() {
    get_word(start_word);
    get_word(end_word);
    word_count = 0;
    while (get_word(word[word_count + 1]))
        ++ word_count, word_index[word[word_count]] = word_count;
}

int queue[6010];
int dist[6010];

void solve() {
    int queue_head = 0, queue_tail = 0;
    memset(dist, 0xff, sizeof(dist));
    queue[++ queue_tail] = word_index[start_word];
    dist[word_index[start_word]] = 1;
    while (queue_head < queue_tail) {
        int cur = queue[++ queue_head];
        string w = word[cur];
        for (int i = 0; i < w.size(); i ++) {
            char i_char = w[i];
            for (char c = 'a'; c <= 'z'; c ++) {
                w[i] = c;
                map<string, int>::iterator it = word_index.find(w);
                if (it != word_index.end() && dist[it->second] < 0) {
                    dist[it->second] = dist[cur] + 1;
                    queue[++ queue_tail] = it->second;
                }
            }
            w[i] = i_char;
        }
    }
    printf("%d\n", dist[word_index[end_word]]);
}

int main() {
    freopen("c.in", "r", stdin);
    freopen("c.out", "w", stdout);
    init();
    solve();
    
    return 0;
}
