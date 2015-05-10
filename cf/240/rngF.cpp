#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <functional>
#include <utility>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdio>

using namespace std;

#define REP(i,n) for((i)=0;(i)<(int)(n);(i)++)
#define foreach(c,itr) for(__typeof((c).begin()) itr=(c).begin();itr!=(c).end();itr++)

#define T (1<<17)
int tree[30][2*T];

void update(int ch, int L, int R, int x, int id = 1, int low = 0, int high = T){ // tree[ch][L..R] = x
    if(low >= R || high <= L) return;
    
    int d = high - low;
    if(low >= L && high <= R){
        tree[ch][id] = d * x;
        return;
    }
    
    if(tree[ch][id] == 0) tree[ch][2*id] = tree[ch][2*id+1] = 0;
    if(tree[ch][id] == d) tree[ch][2*id] = tree[ch][2*id+1] = d/2;
    
    int mid = (low + high) / 2;
    update(ch, L, R, x, 2*id, low, mid);
    update(ch, L, R, x, 2*id+1, mid, high);
    
    tree[ch][id] = tree[ch][2*id] + tree[ch][2*id+1];
}

int sum(int ch, int L, int R, int id = 1, int low = 0, int high = T){ // sum tree[ch][L..R]
    if(low >= R || high <= L) return 0;
    
    int d = high - low;
    if(low >= L && high <= R) return tree[ch][id];
    
    if(tree[ch][id] == 0) return 0;
    if(tree[ch][id] == d) return min(high,R) - max(low,L);
    
    int mid = (low + high) / 2;
    int ans = 0;
    ans += sum(ch, L, R, 2*id, low, mid);
    ans += sum(ch, L, R, 2*id+1, mid, high);
    return ans;
}

string s,ans;
int a[30];

int main(void){
    int N,Q,L,R,i,j;
    
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    cin >> N >> Q >> s;
    REP(i,N) update(s[i]-'a', i, i+1, 1);
    
    REP(i,Q){
        cin >> L >> R; L--;
        int d = (R - L) / 2;
        
        REP(j,26) a[j] = sum(j, L, R);
        int odd = -1, cnt = 0;
        REP(j,26) if(a[j] % 2 == 1) {odd = j; cnt++;}
        if(cnt >= 2) continue;
        
        REP(j,26) update(j, L, R, 0);
        
        if(odd != -1){
            update(odd, L+d, L+d+1, 1);
            a[odd]--;
        }
        
        int tmp = 0;
        REP(j,26) if(a[j] > 0){
            update(j, L+tmp, L+tmp+a[j]/2, 1);
            update(j, R-tmp-a[j]/2, R-tmp, 1);
            tmp += a[j]/2;
        }
    }
    
    REP(i,N) REP(j,26) if(sum(j, i, i+1) == 1) ans += (char)('a' + j);
    cout << ans << endl;
    
    return 0;
}
