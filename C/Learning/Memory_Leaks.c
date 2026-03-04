#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("--- Welcome to the Memory Leak Test ---\n");

    // 1. We rent 100 bytes of memory (Room A)
    char *my_memory = malloc(100);
    printf("Allocated 100 bytes (Room A) at: %p\n", (void*)my_memory);

    // 2. THE LEAK: We overwrite our map!
    // We rent 50 NEW bytes (Room B) and save it in the SAME variable.
    // We just permanently lost the address for Room A!
    my_memory = malloc(50);
    printf("Overwrote pointer! Now holding (Room B) at: %p\n", (void*)my_memory);

    // 3. We clean up Room B... but Room A is lost forever.
    free(my_memory);
    printf("Freed Room B. Exiting program...\n");

    return 0;
}