#include <stdio.h>

int main () { 
    int var = 10;  // var address = 0x1 with value 10 
    int *x = &var; // x address = 0x2 with value 0x1 
    int y = *x;    // y address = 0x3 with value 10 

    printf("Before hacking: var = %d\n", var); 
    
    int k = 7;     // k address = 0x4 with value 7 
    int **dp = &x; // dp has address = 0x5 and has value 10 
    **dp = k; // what inside dp = 0x2 , First * what inside 0x2 = 0x1 , 2nd * what inside 0x2 = 10 so make it = k which is 7  

    printf("After hacking:  var = %d\n", var); 

    return 0;
}