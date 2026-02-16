#include <stdio.h>


int add_two_numbers(int num1, int num2){
    int results = num1 + num2;
    return results;
}

int main (){
    int num1,num2;
    scanf("%d %d",&num1,&num2);
    printf("%d",add_two_numbers(num1,num2));
    
}