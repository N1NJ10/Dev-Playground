#include <stdio.h>
#include <stdlib.h>

// Our trusty double-pointer function
void grow_array(int **arr, int new_size) {
    int *temp = realloc(*arr, new_size * sizeof(int));

    if (temp == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    // Overwrite main's piece of paper with the new address
    *arr = temp;
}

int main() {
    // 1. Allocate our initial small array (Space for 2 numbers)
    int *my_list = malloc(2 * sizeof(int));
    my_list[0] = 10;
    my_list[1] = 20;

    // 2. THE BLOCKER!
    // This forces realloc to pack up and move our array later.
    int *blocker = malloc(100 * sizeof(int));

    printf("--- BEFORE REALLOC ---\n");
    printf("Where does my_list point? %p\n", (void*)my_list);
    printf("Where is the blocker?     %p\n", (void*)blocker);
    printf("Data: %d, %d\n\n", my_list[0], my_list[1]);

    // 3. Try to grow my_list.
    // realloc hits the blocker, copies the 10 and 20 to a new location,
    // and our double pointer updates my_list with the new address.

    grow_array(&my_list, 5000);

    // 4. ADD MORE DATA!
    // Because my_list now holds the NEW address, this data goes exactly
    // where it belongs in the freshly allocated space.
    my_list[2] = 30;
    my_list[3] = 40;
    my_list[4] = 50;

    printf("--- AFTER REALLOC ---\n");
    printf("Where does my_list point? %p  <-- THIS IS THE NEW ADDRESS!\n", (void*)my_list);

    // Proving the old data survived the move
    printf("Old Data that survived: %d, %d\n", my_list[0], my_list[1]);

    // Proving the new data was saved successfully
    printf("New Data we just added: %d, %d, %d\n", my_list[2], my_list[3], my_list[4]);

    // 5. Clean up both
    free(my_list);
    free(blocker);

    return 0;
}