#include <stdio.h>

void classify_number(int num) {
    if (num < 0) {
        printf("NEGATIVE\n");
    } else if (num == 0) {
        printf("ZERO\n");
    } else {
        printf("POSITIVE\n");
    }
}


int main (){

    int x ;
    printf("What is the temp Degree : "); 
    scanf("%d",&x);
    classify_number(x);


    return 0 ;

}

