#include <stdio.h>
#include <string.h>

# define ARRAY 5

int main () {

    int numbers[ARRAY];

    memset(&numbers, '\0', sizeof(numbers));

    printf("Enter 5 numbers :\n");

    for (int i =0 ; i < 5 ; i++) {
        scanf("%d",&numbers[i]); // need the memory address not index only '&'

    }

    printf("Displaying numbesr\n");

    for (int i =0 ; i < 5 ; i++) {
        printf("%d\n", numbers[i]);

    }
    return 0;

}