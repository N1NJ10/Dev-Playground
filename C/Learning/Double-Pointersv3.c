#include <stdio.h>

int main () {

    int var = 10; // var address = 0x1 with value 10
    int *x = &var; // This x address = 0x2 with with value 0x1
    int y = *x; // the y has and address 0x3 with value 10

    int k = 7;
    int *var = &k;

    printf("%d",var);

    return 0;
}
