#include <stdio.h>

// --- PART 1: THE TOOLS (The Recipe) ---

// 1. The Box (Struct)
// A custom container to hold two integers.
typedef struct {
    int first;
    int second;
} SwappedValues;

// 2. The Tool (Function)
// Takes two addresses, swaps the values there, and returns a box with the results.
SwappedValues swap(int *a, int *b) {
    // A. The Swap Logic (Changing the real variables)
    int temp = *a;
    *a = *b; 
    *b = temp;

    // B. The Receipt (Packing the result)
    // Create a box named 'result' and put the new values inside.
    SwappedValues result = {*a, *b}; 
    
    // C. Hand the box back
    return result;
}

// --- PART 2: THE CHEF (The Main Function) ---

int main() {
    // 1. Create two variables (The Ingredients)
    int x = 10;
    int y = 20;

    printf("Before Swap: x = %d, y = %d\n", x, y);

    // 2. Call the Tool
    // We send the ADDRESSES (&x, &y) because the function asks for pointers (*a, *b).
    // We catch the returned box in a variable named 'outcome'.
    SwappedValues outcome = swap(&x, &y);

    // 3. Look at the results
    // The original variables 'x' and 'y' are changed!
    printf("After Swap (Originals): x = %d, y = %d\n", x, y);
    
    // The returned box 'outcome' also holds the new values!
    printf("From the Box: First = %d, Second = %d\n", outcome.first, outcome.second);

    return 0;
}