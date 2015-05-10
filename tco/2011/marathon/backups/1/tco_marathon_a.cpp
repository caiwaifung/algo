#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<string> __board;
vector<bool> __scanned;
class ImageToScan {
public:
    static string scan(int i) {
        __scanned[i] = true;
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
    
    int count_value(int x, int y) {
        /*
        int val = 0;
        
        bool a1 = (x > 0) && (y > 0) && (board[x-1][y-1] == '1');
        bool a2 = (x > 0) && (board[x-1][y] == '1');
        bool a3 = (x > 0) && (y < width-1) && (board[x-1][y+1] == '1');
        bool b1 = (x < height-1) && (y > 0) && (board[x+1][y-1] == '1');
        bool b2 = (x < height-1) && (board[x+1][y] == '1');
        bool b3 = (x < height-1) && (y < width-1) && (board[x+1][y+1] == '1');
        
        int val1 = 0;
        if (a1 && b3) val1 += 10;
        if (a2 && b2) val1 += 10;
        if (a3 && b1) val1 += 10;
        
        int val2 = 0;
        if (a1 && b2) val2 += 7;
        if (a2 && b1) val2 += 7;
        if (a2 && b3) val2 += 7;
        if (a3 && b2) val2 += 7;
        
        val = min(15, (min(val1, 12) + min(val2, 10))) * 10;
        //val = min(val, 40);
        //val += min(10, val3 * 5);
        
        int val4 = 0;
        for (int dx = -2; dx <= 2; dx ++)
            for (int dy = -2; dy <= 2; dy ++) {
                int x0 = x + dx;
                int y0 = y + dy;
                if (x0 < 0 || x0 >= height || y0 < 0 || y0 >= width)
                    continue;
                if (scanned[x0] && board[x0][y0] == '1') {
                    int dist = abs(dx) + abs(dy);
                    val4 += sqr(5-dist);
                }
            }
        
        //val += min(val4, 45);
        
        return val;
        */
        //*
        
        int val = 0;
        
        bool a1 = (x > 0) && (y > 0) && (board[x-1][y-1] == '1');
        bool a2 = (x > 0) && (board[x-1][y] == '1');
        bool a3 = (x > 0) && (y < width-1) && (board[x-1][y+1] == '1');
        bool b1 = (x < height-1) && (y > 0) && (board[x+1][y-1] == '1');
        bool b2 = (x < height-1) && (board[x+1][y] == '1');
        bool b3 = (x < height-1) && (y < width-1) && (board[x+1][y+1] == '1');
        
        
        if (a1 && b2) val = 7;
        if (a2 && b1) val = 7;
        if (a2 && b3) val = 7;
        if (a3 && b2) val = 7;
        
        if (a1 && b3) val = 10;
        if (a2 && b2) val = 10;
        if (a3 && b1) val = 10;
        
        return val;
        //*/
    }
	
	vector<string> restore(int _h, int _w, int _nb, int _nl) {
		height = _h;
		width = _w;
		nBlack = _nb;
		nLetter = _nl;
    
        //printf("restore stage I\n"); fflush(stdout);
    
		
		board.resize(height, string(width, '?'));
		scanned.resize(height, false);
		for (int i = 0; i < height; i ++)
            if (i % 2 < 1) {
                scanned[i] = true;
                board[i] = ImageToScan::scan(i);
                for (int j = 0; j < width; j ++)
                    if (board[i][j] == '1')
                        nBlack --;
            }
        
       // printf("restore stage II\n"); fflush(stdout);
    
		
        
        list.clear();
        for (int i = 0; i < height; i ++) {
            if (scanned[i]) continue;
            for (int j = 0; j < width; j ++)
                list.push_back(Item(i, j, count_value(i, j)));
        }
        sort(list.begin(), list.end());
        
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

double test(char *s) {
    freopen(s, "r", stdin);
    int h, w, nb = 0;
    scanf("%d%d", &h, &w);
    
    //printf("stage I h=%d w=%d\n",h,w); fflush(stdout);
    
    __board.resize(h);
    for (int i = 0; i < h; i ++) {
        cin >> __board[i];
        for (int j = 0; j < w; j ++)
            if (__board[i][j] == '1')
                nb ++;
    }
    __scanned.resize(h, false);
    
    //printf("stage II\n"); fflush(stdout);
    
    ImageScanner ct;
    vector<string> result = ct.restore(h, w, nb, 0);
    
    int cp = 0, wp = 0;
    for (int i = 0; i < h; i ++) if (!__scanned[i])
        for (int j = 0; j < w; j ++) {
            if (result[i][j] == __board[i][j]) cp ++;
            if ('0' == __board[i][j]) wp ++;
        }
    double score = max(0.0, (double)(cp-wp) / (double)nb);
    
    printf("executed %s - score=%.7lf\n", s, score);
    return score;            
    
    //printf("stage III\n"); fflush(stdout);
    /*
    freopen("result_a.txt", "w", stdout);
    for (int i = 0; i < h; i ++) {
        for (int j = 0; j < w; j ++)
            if (result[i][j] == '1')
                printf("#");
            else
                printf(" ");
        printf("\n");
    }
    */
}

int main() {
    freopen("log.txt", "w", stdout);
    //    cout << result[i] << endl;
    
    double score = 0;
    for (char c = '1'; c <= '9'; c ++) {
        char s[100];
        sprintf(s, "inputs/input%c.txt", c);
        score += test(s);
    }
    
    printf("total score = %.7lf\n", score);

    return 0;
}
