#include <stdio.h>

void count_evens_to_100(){

    for (int i = 0 ; i<=100 ; i+=2){
        printf("%d\n",i);
    }
    int x = 0;
    while (x%2==0 && x <= 100) {
        printf("%d\n",x);
        x+=2;

    }
    int y = 0;
    do {
        printf("%d\n",y);
        y+=2;
    } while (y <= 100 && y%2==0);
}

int main () {

    count_evens_to_100();

    return 0;

}