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

const int cntBlack[64] = {
    816, 249, 279, 780, 262, 36, 755, 5074, 172, 65, 223, 824, 172, 22, 293, 1316, 256, 302, 1567, 190, 304, 21, 132, 67, 632, 1050, 216, 7362, 274, 57, 1435, 2173, 316, 167, 292, 260, 163, 27, 1096, 1561, 23, 24, 56, 47, 20, 13, 47, 249, 785, 287, 158, 1712, 966, 47, 6331, 2847, 4972, 1472, 79, 2472, 1468, 259, 2816, 10896
};
const int cntWhite[64] = {
    160821, 4686, 749, 1836, 5526, 352, 2323, 5785, 5274, 8262, 216, 888, 121, 281, 136, 482, 755, 240, 29, 10, 220, 38, 13, 69, 2091, 1047, 4, 53, 99, 38, 26, 86, 5264, 98, 240, 83, 7183, 159, 1069, 785, 337, 217, 59, 36, 233, 474, 21, 159, 2227, 90, 16, 10, 964, 48, 73, 82, 5643, 482, 27, 74, 779, 143, 71, 105
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
        int x, y; double val;
        Item(int _x, int _y, double _v) {
            x = _x, y = _y, val = _v;
        }
        friend bool operator <(const Item &a, const Item &b) {
            return a.val > b.val;
        }
    };
    vector<Item> list;
    
    double count_value(int x, int y) {                
        bool a1 = (x > 0) && (y > 0) && (board[x-1][y-1] == '1');
        bool a2 = (x > 0) && (board[x-1][y] == '1');
        bool a3 = (x > 0) && (y < width-1) && (board[x-1][y+1] == '1');
        bool b1 = (x < height-1) && (y > 0) && (board[x+1][y-1] == '1');
        bool b2 = (x < height-1) && (board[x+1][y] == '1');
        bool b3 = (x < height-1) && (y < width-1) && (board[x+1][y+1] == '1');
        
        int p = 0;
        p = p * 2 + (a1 ? 1 : 0);
        p = p * 2 + (a2 ? 1 : 0);
        p = p * 2 + (a3 ? 1 : 0);
        p = p * 2 + (b1 ? 1 : 0);
        p = p * 2 + (b2 ? 1 : 0);
        p = p * 2 + (b3 ? 1 : 0);
        
        int pb1 = 1, pb2 = 1;
        int pw1 = 1, pw2 = 1;
        
        double vb = pb2, vw = pw2;
        while (pb1 --) vb *= (double) cntBlack[p];
        while (pw1 --) vw *= (double) cntWhite[p];
        
        return vb - vw;        
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
            if (i % 2 == 0) {
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
        
       // printf("restore stage III\n"); fflush(stdout);
        
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


int main() {
    freopen("inputs/input.txt", "r", stdin);
    //freopen("log.txt", "w", stdout);
    int h, w, nb = 0;
    scanf("%d%d", &h, &w);
    
    //printf("stage I h=%d w=%d\n",h,w); fflush(stdout);
    
    __board.resize(h);
    __scanned.resize(h);
    for (int i = 0; i < h; i ++) {
        cin >> __board[i];
        for (int j = 0; j < w; j ++)
            if (__board[i][j] == '1')
                nb ++;
    }
    
    //printf("stage II h=%d w=%d\n",h,w); fflush(stdout);
    
    ImageScanner ct;
    vector<string> result = ct.restore(h, w, nb, 0);
    
    //printf("stage III h=%d w=%d\n",h,w); fflush(stdout);
    
    freopen("result.txt", "w", stdout);
    for (int i = 0; i < h; i ++) {
        for (int j = 0; j < w; j ++)
            if (result[i][j] == '1')
                printf("#");
            else
                printf(" ");
        printf("\n");
    }
    return 0;
}

/*
double test(char *s) {
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
    
    int cp = 0, wp = 0;
    for (int i = 0; i < h; i ++) if (!__scanned[i])
        for (int j = 0; j < w; j ++) {
            if (result[i][j] == __board[i][j]) cp ++;
            if ('0' == __board[i][j]) wp ++;
        }
    double score = max(0.0, (double)(cp-wp) / (double)nb);
    
    printf("executed %s - score=%.7lf\n", s, score);
    return score;            
}

int main() {
    //freopen("log.txt", "w", stdout);
    
    double score = 0;
    for (char c = '1'; c <= '9'; c ++) {
        char s[100];
        sprintf(s, "inputs/input%c.txt", c);
        score += test(s);
    }
    
    printf("total score = %.7lf\n", score);
    
    for (;;);

    return 0;
}
*/
