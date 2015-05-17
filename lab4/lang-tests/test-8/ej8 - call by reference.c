#include <stdio.h>

void interchange(int x1, int y1);

int main(void){
    int x = 50, y = 70;
    interchange(x,y);
    printf("x = %d, y = %d\n",x,y);
    return 0;
}

void interchange(int x1,int y1){
    int z1;
    z1 = x1;
    x1 = y1;
    y1 = z1;
}
