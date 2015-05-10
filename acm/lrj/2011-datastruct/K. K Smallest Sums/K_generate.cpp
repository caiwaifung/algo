#include<iostream>
using namespace std;
int main() {
    srand(time(NULL));
    freopen("k.in","w",stdout);
    printf("750\n");for(int i=0;i<750;i++){for(int j=0;j<750;j++)printf("%d ",rand()%100000+1);printf("\n");}
    return 0;
}
