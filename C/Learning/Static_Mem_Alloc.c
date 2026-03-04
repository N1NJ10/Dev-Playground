#include <stdio.h>

// 1. THE GLOBAL VARIABLE (The Public Billboard)
// Declared outside of all functions. Anyone can see it and change it.
// It lives in the Data Section for the entire life of the program.
int global_count = 0; 

void test_variables() {
    // 2. THE NORMAL VARIABLE (The Whiteboard)
    // Declared inside the function. Lives on the Stack.
    // It is created fresh and set to 0 every single time this function runs.
    int normal_count = 0;

    // 3. THE STATIC VARIABLE (The Locked Notebook)
    // Declared inside the function, but marked 'static'. Lives in the Data Section.
    // The "= 0" part only happens ONCE. It remembers its value between calls.
    static int static_count = 0;

    // Add 1 to all of them
    global_count++;
    normal_count++;
    static_count++;

    // Print the results
    printf("Normal: %d  |  Static: %d  |  Global: %d\n", normal_count, static_count, global_count);
}

int main() {
    printf("--- First Call ---\n");
    test_variables();

    printf("\n--- Second Call ---\n");
    test_variables();

    printf("\n--- Third Call ---\n");
    test_variables();

    // PROOF OF SCOPE:
    // The main function can easily change the global variable...
    global_count = 100; 
    
    // ...but if we try to type 'normal_count = 100;' or 'static_count = 100;' here, 
    // the compiler will throw an error because those variables are hidden inside test_variables()!

    printf("\n--- After Main changes Global ---\n");
    test_variables();

    return 0;
}