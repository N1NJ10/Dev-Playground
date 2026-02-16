#include <stdio.h>

// 1. THE BLUEPRINT (Design the Car)
// This goes at the top, outside main
struct Car {
    int year;      // Whole number
    float speed;   // Decimal number
    char gear;     // Letter
};

int main() {
    // 2. BUILD THE CAR (Create the variable)
    // We make a variable named 'myFerrari' using the blueprint
    struct Car myFerrari;

    // 3. FILL IT UP (The Dot Operator)
    // Use the dot (.) to open specific pockets
    myFerrari.year = 2024;
    myFerrari.speed = 220.5;
    myFerrari.gear = 'D';

    // 4. USE IT
    printf("--- Car Status ---\n");
    printf("Year:  %d\n", myFerrari.year);
    printf("Speed: %.1f km/h\n", myFerrari.speed);
    printf("Gear:  %c\n", myFerrari.gear);

    return 0;
}