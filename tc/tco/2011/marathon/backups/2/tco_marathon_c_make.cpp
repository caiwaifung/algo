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
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

int cntBlack[64], cntWhite[64];

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
        int val = 0;
        
       // printf("restore count_val (%d,%d)\n",x,y); fflush(stdout);
        
        bool a1 = (x > 0) && (y > 0) && (board[x-1][y-1] == '1');
        bool a2 = (x > 0) && (board[x-1][y] == '1');
        bool a3 = (x > 0) && (y < width-1) && (board[x-1][y+1] == '1');
        bool b1 = (x < height-1) && (y > 0) && (board[x+1][y-1] == '1');
        bool b2 = (x < height-1) && (board[x+1][y] == '1');
        bool b3 = (x < height-1) && (y < width-1) && (board[x+1][y+1] == '1');
        
        val = val * 2 + (a1 ? 1 : 0);
        val = val * 2 + (a2 ? 1 : 0);
        val = val * 2 + (a3 ? 1 : 0);
        val = val * 2 + (b1 ? 1 : 0);
        val = val * 2 + (b2 ? 1 : 0);
        val = val * 2 + (b3 ? 1 : 0);
        
        if (board[x][y] == '1')
            cntBlack[val] ++;
        else
            cntWhite[val] ++;
        
        return val;        
    }
	
	vector<string> restore(int _h, int _w, int _nb, int _nl) {
		height = _h;
		width = _w;
		nBlack = _nb;
		nLetter = _nl;
        
       // printf("restore stage I\n"); fflush(stdout);
		
		board.resize(height, string(width, '?'));
		scanned.resize(height, false);
		for (int i = 0; i < height; i ++)
            board[i] = ImageToScan::scan(i);
            
       // printf("restore stage II\n"); fflush(stdout);
		        
        list.clear();
        for (int i = 0; i < height; i ++)
            for (int j = 0; j < width; j ++)
                count_value(i, j);
		
		return board;
	}
};



////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

void test(char *s) {
    freopen(s, "r", stdin);
    int h, w, nb = 0;
    scanf("%d%d", &h, &w);
    __board.resize(h);
    for (int i = 0; i < h; i ++) {
        cin >> __board[i];
        for (int j = 0; j < w; j ++)
            if (__board[i][j] == '1')
                nb ++;
    }
    __scanned.resize(h, false);
    ImageScanner ct;
    vector<string> result = ct.restore(h, w, nb, 0);
}

int main() {
    //    cout << result[i] << endl;
    
    for (char c = '1'; c <= '9'; c ++) {
        char s[100];
        sprintf(s, "inputs/input%c.txt", c);
        test(s);
    }
    
    
    freopen("c_data.txt", "w", stdout);
    printf("const int cntBlack[64] = {\n    ");
    for (int i = 0; i < 64; i ++) printf("%d%s", cntBlack[i], i < 63 ? ", " : "\n};\n");
    printf("const int cntWhite[64] = {\n    ");
    for (int i = 0; i < 64; i ++) printf("%d%s", cntWhite[i], i < 63 ? ", " : "\n};\n");
    
    //printf("total score = %.7lf\n", score);

    return 0;
}
