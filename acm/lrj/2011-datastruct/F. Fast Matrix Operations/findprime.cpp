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

bool prime(long long x) {
    for (long long i = 2; i*i <= x; i ++)
        if (x%i==0)
            return false;
    return true;
}

int main() {
    
for(;;){
    long long n;
    cin >> n;
    while (!prime(n)) n ++;
    cout << n << endl;
}
    return 0;
}
