#include <stdio.h>
/*
Add `int max_of_four(int a, int b, int c, int d)` here.
*/

int max_of_four(int a , int b , int c , int d){
    
    signed Max_number;
    int arr[] = {a,b,c,d};
    for (int x = 0; x < 4; x++) {
        if (arr[x]> Max_number) {
            Max_number = arr[x];
        }
    }
    return Max_number;
}

int main() {
    int a, b, c, d;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    int ans = max_of_four(a, b, c, d);
    printf("%d", ans);
    
    return 0;
}