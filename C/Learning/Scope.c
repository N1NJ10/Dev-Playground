#include <stdio.h>

// [1] GLOBAL SCOPE
// Visible to ALL functions. Lives in .data section.
int g_Config = 100; 

void helper() {
    // This function can see the Global variable
    printf("\n[HELPER] accessing Global g_Config: %d (Addr: %p)\n", g_Config, &g_Config);
}

int main() {
    // [2] LOCAL SCOPE (Outer)
    // Visible only inside main(). Lives on the Stack.
    int personID = 5; 

    printf("[MAIN] Start. Outer personID = %d (Addr: %p)\n", personID, &personID);
    printf("[MAIN] Global g_Config is: %d\n", g_Config);

    // [3] NESTED BLOCK SCOPE
    // Starts a new temporary stack frame section.
    {
        // [4] SHADOWING
        // This is a BRAND NEW variable. It hides the outer 'personID'.
        // Notice the address will be different!
        int personID = 999; 
        
        // We modify the INNER variable
        personID += 1; 

        // We modify the GLOBAL variable
        g_Config = 500;

        printf("\n    [BLOCK] Inside block!\n");
        printf("    [BLOCK] Inner personID = %d (Addr: %p) <--- DIFFERENT!\n", personID, &personID);
        printf("    [BLOCK] Global g_Config changed to: %d\n", g_Config);
    } 
    // [5] END OF BLOCK
    // The inner 'personID' (1000) is destroyed here. 
    // The name 'personID' now refers back to the Outer variable.

    printf("\n[MAIN] Back to main. Outer personID is still: %d (Addr: %p)\n", personID, &personID);
    printf("[MAIN] But Global g_Config stayed changed: %d\n", g_Config);

    helper();

    return 0;
}
