#include <iostream>
#include <algorithm>
using namespace std;

const int s[]={
    75, 60, 50, 45,
    40, 36, 32, 29, 26,
    24, 22, 20, 18, 16,
    15, 14, 13, 12, 11,
    10, 9, 8, 7, 6,
    5, 4, 3, 2, 1,0};

int main() {
    int a[30]={0};
    for(int i=0; i<3; ++i) {
        for(int j=0; j<30; ++j) a[j]+=s[j];
        sort(a, a+30);
    }
    cout<<a[0]<<endl;
    return 0;
}


