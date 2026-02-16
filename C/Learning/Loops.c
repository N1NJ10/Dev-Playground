#include <stdio.h>

int main() {

    // ==========================================
    // 1. THE WHILE LOOP (Entry Control)
    // Use when: You don't know how many times it will run.
    // Logic: "Check the fuel gauge. If empty, don't even start."
    // ==========================================
    printf("\n--- Mission 1: The Countdown (While Loop) ---\n");

    int fuel = 3;

    while (fuel > 0) {
        printf("Fuel is at %d%%\n", fuel);
        fuel--; // Decrease fuel
    }
    printf("Blast off!\n");


    // ==========================================
    // 2. THE DO-WHILE LOOP (Exit Control)
    // Use when: The code MUST run at least once (like a menu or input check).
    // Logic: "Eat the pizza first, THEN check if you are full."
    // ==========================================
    printf("\n--- Mission 2: Security Check (Do-While Loop) ---\n");

    int pin = 0;

    do {
        // This runs BEFORE checking the condition!
        printf("Enter the PIN (Hint: 1234): ");
        scanf("%d", &pin);

    } while (pin != 1234); // Keep looping if PIN is wrong

    printf("Access Granted!\n");


    // ==========================================
    // 3. THE FOR LOOP (Counter Control)
    // Use when: You know EXACTLY how many times to run (Arrays).
    // Logic: "Do this exactly 5 times."
    // ==========================================
    printf("\n--- Mission 3: Scan Sector (For Loop) ---\n");

    // Syntax: ( Start ; Stop Condition ; Step )
    for (int i = 0; i <= 5; i++) {
        printf("Scanning Sector #%d...\n", i);
    }

    return 0;
}