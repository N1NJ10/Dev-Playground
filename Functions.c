#include <stdio.h>


void add_two_numbers(int num1 , int num2 ) {
    int xyz = num1 + num2;
    printf("%d",xyz);

}


int main () {

    int num1;
    int num2;

    scanf("%d %d",&num1,&num2);
    add_two_numbers(num1,num2);

}