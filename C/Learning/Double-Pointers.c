#include <stdio.h>

int main() {
    // 1. The Treasure (Normal Variable)
    int val = 42;

    // 2. The First Map (Single Pointer)
    int *ptr = &val;

    // 3. The Map to the Map (Double Pointer)
    int **dptr = &ptr;

    printf("=== THE ACTUAL VALUES ===\n");
    printf("Value of val      : %d\n", val);
    printf("Value via *ptr    : %d  (Follows ptr once)\n", *ptr);
    printf("Value via **dptr  : %d  (Follows dptr twice)\n\n", **dptr);

    printf("=== THE SECRET CHAIN OF ADDRESSES ===\n");

    // Let's look at where the treasure actually lives
    printf("1. Address of 'val' (&val) : %p\n", (void*)&val);

    // Let's look at what the first pointer holds, and where it lives
    printf("2. What 'ptr' holds        : %p  <-- Matches address of val!\n", (void*)ptr);
    printf("3. Address of 'ptr' (&ptr) : %p\n", (void*)&ptr);

    // Let's look at what the double pointer holds
    printf("4. What 'dptr' holds       : %p  <-- Matches address of ptr!\n", (void*)dptr);

    return 0;
}