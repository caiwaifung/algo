#include <iostream>
#include <cmath>
using namespace std;

typedef long long int64;

int64 gcd(int64 a, int64 b) {
    return b == 0 ? a : gcd(b, a%b);
}

bool check(int64 a, int64 b) {
    if (gcd(a, b) != 1) return false;
    int64 c = (int64)(sqrt(a*a+b*b) + 0.1);
    return (a*a + b*b == c*c);
}

int main() {
    //freopen("exp.txt", "w", stdout);
    //FILE *f = fopen("exp.txt", "w");
    int cnt = 0;
    for (int64 i = 1; i <= 100000; i ++) {
        int c = 0;
        for (int64 j = i; j <= 100000; j ++)
            if (check(i, j))
                c ++;
        if (c > cnt) {
            cnt = c;
            printf("max_cnt = %d\n", cnt);
        }
        if (i % 1000 == 0) printf("i=%d cnt=%d\n", i, cnt);
        /*
                //printf("%d %d\n", i, j),
                if (++ cnt % 10 == 0) 
                    printf("cnt = %d (i=%d j=%d)\n", cnt,i,j),
                    fprintf(f,"cnt = %d (i=%d j=%d)\n", cnt,i,j);*/
    }
   // printf("cnt=%d\n", cnt);
    return 0;
}
