#include <stdio.h>
#include <stdlib.h>

int main() {
    int *arr;
    int n, i;

    // Get size from user
    printf("Enter number of elements: ");
    scanf("%d", &n);

    // Dynamically allocate memory for n integers
    arr = (int*) malloc(n * sizeof(int));

    // Check if memory allocation was successful
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return -1;
    }

    // Initialize the array
    printf("Enter %d numbers:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Display the array
    printf("You entered: ");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Free the allocated memory
    free(arr);
    arr = NULL; // Good practice to avoid dangling pointers

    printf("Memory freed successfully.\n");
    return 0;
}
