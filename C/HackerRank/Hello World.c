#include <stdio.h>

int main()
{
    char x[100];
    scanf("%[^\n]", x);
    printf("Hello, World!\n");
    printf("%s", x);

    return 0;
}