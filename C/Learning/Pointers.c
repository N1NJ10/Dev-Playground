#include <stdio.h>
#include <string.h> // Needed for strcmp

int main() {
    // 1. The target memory (Stack String)
    char password[] = "open";

    // 2. The Tool (Pointer)
    // 'ptr' now holds the address of the first letter 'o'
    char *ptr = password;

    printf("Current Password: %s\n", password);


    // Answer

    *ptr = 's';
    ptr[1] = 'a';
    ptr[2] = 'f';
    ptr[3] = 'e';

    // ---------------------------------------------------------
    // MISSION: Change "open" to "safe" using ONLY the pointer!
    // ---------------------------------------------------------
    
    // Step 1: Change 'o' to 's'
    // Hint: *ptr refers to the first character
    // WRITE CODE HERE:
    
    
    // Step 2: Change 'p' to 'a'
    // Hint: *(ptr + 1) OR ptr[1] refers to the second character
    // WRITE CODE HERE:
    
    
    // Step 3: Change 'e' to 'f'
    // WRITE CODE HERE:
    
    
    // Step 4: Change 'n' to 'e'
    // WRITE CODE HERE:
    

    // ---------------------------------------------------------
    // Verification System
    // ---------------------------------------------------------
    if (strcmp(password, "safe") == 0) {
        printf("\n[+] ACCESS GRANTED! Password is now: %s\n", password);
    } else {
        printf("\n[-] ACCESS DENIED. Password is still: %s\n", password);
    }

    return 0;
}