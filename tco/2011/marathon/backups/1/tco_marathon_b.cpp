#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<string> __board;
class ImageToScan {
public:
    static string scan(int i) {
        return __board[i];
    }
};

class ImageScanner {
private:
    int sqr(int x) {
        return x * x;
    }
public:
	vector<string> board;
	vector<bool> scanned;
	int height, width, nBlack, nLetter;
	
    struct Item {
        int x, y, val;
        Item(int _x, int _y, int _v) {
            x = _x, y = _y, val = _v;
        }
        friend bool operator <(const Item &a, const Item &b) {
            return a.val > b.val;
        }
    };
    vector<Item> list;
    
    void scan_five(int x, int y, bool a[]) {
        for (int j = 0; j < 5; j ++) {
            int y0 = y + j - 2;
            if (y0 >= 0 && y0 < width && board[x][y0] == '1')
                a[j] = true;
        }
    }
    
    int count_value(int x, int y) {
        int val = 0;
        
       // printf("restore count_val (%d,%d)\n",x,y); fflush(stdout);
        
        bool tony[5], jack[5];
        memset(tony, false, sizeof(tony));
        memset(jack, false, sizeof(jack));
        
        int i;
        for (i = x-1; i >= 0 && !scanned[i]; i --);
        if (i >= 0) scan_five(i, y, tony);
        for (i = x+1; i < height && !scanned[i]; i ++);
        if (i < height) scan_five(i, y, jack);
        
        if (x % 3 == 2)
            for (int i = 0; i < 5; i ++)
                swap(tony[i], jack[i]);
        
        if (tony[2] && jack[2]) val += 100;
        
        if (tony[1] && jack[3]) val += 10;
        if (tony[1] && jack[4]) val += 8;
        if (tony[3] && jack[1]) val += 10;
        if (tony[3] && jack[0]) val += 8;
        
        if (tony[0] && jack[3]) val += 5;
        if (tony[0] && jack[4]) val += 5;
        if (tony[4] && jack[1]) val += 5;
        if (tony[4] && jack[0]) val += 5;
        
        return val;        
    }
	
	vector<string> restore(int _h, int _w, int _nb, int _nl) {
		height = _h;
		width = _w;
		nBlack = _nb;
		nLetter = _nl;
        
        printf("restore stage I\n"); fflush(stdout);
		
		board.resize(height, string(width, '?'));
		scanned.resize(height, false);
		for (int i = 0; i < height; i ++)
            if (i % 3 == 0) {
                scanned[i] = true;
                board[i] = ImageToScan::scan(i);
                for (int j = 0; j < width; j ++)
                    if (board[i][j] == '1')
                        nBlack --;
            }
            
        printf("restore stage II\n"); fflush(stdout);
		        
        list.clear();
        for (int i = 0; i < height; i ++) {
            //printf("i = %d\n", i);
            if (scanned[i]) continue;
            for (int j = 0; j < width; j ++)
                list.push_back(Item(i, j, count_value(i, j)));
        }
        sort(list.begin(), list.end());
        
        
        printf("restore stage III\n"); fflush(stdout);
        
        for (int i = 0; i < nBlack; i ++)
            if (list[i].val > 0)
                board[list[i].x][list[i].y] = '1';
        
        for (int i = 0; i < height; i ++)
            for (int j = 0; j < width; j ++)
                if (board[i][j] == '?')
                    board[i][j] = '0';
		
		return board;
	}
};

int main() {
    freopen("inputs/input.txt", "r", stdin);
    freopen("log.txt", "w", stdout);
    int h, w, nb = 0;
    scanf("%d%d", &h, &w);
    
    printf("stage I h=%d w=%d\n",h,w); fflush(stdout);
    
    __board.resize(h);
    for (int i = 0; i < h; i ++) {
        cin >> __board[i];
        for (int j = 0; j < w; j ++)
            if (__board[i][j] == '1')
                nb ++;
    }
    
    printf("stage II\n"); fflush(stdout);
    
    ImageScanner ct;
    vector<string> result = ct.restore(h, w, nb, 0);
    
    printf("stage III\n"); fflush(stdout);
    
    freopen("result.txt", "w", stdout);
    for (int i = 0; i < h; i ++) {
        for (int j = 0; j < w; j ++)
            if (result[i][j] == '1')
                printf("#");
            else
                printf(" ");
        printf("\n");
    }
    //    cout << result[i] << endl;

    return 0;
}
