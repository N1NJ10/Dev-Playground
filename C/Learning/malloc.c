#include <stdio.h>
#include <stdlib.h> // Required to use malloc() and free()
#include <string.h> // Required to use strcpy()

// 1. Define the structure
struct employee_t {
    int id;
    char name[50];
};

int main() {
    // 2. Ask the Heap for memory to hold one employee
    struct employee_t *my_employee = malloc(sizeof(struct employee_t));

    // 3. Always check if the hotel (Heap) was full!
    if (my_employee == NULL) {
        printf("Error: Could not allocate memory!\n");
        return 1; // Exit the program with an errorbut
    }

    // 4. Use the memory (Note the -> arrow instead of a dot)
    my_employee->id = 101;
    strcpy(my_employee->name, "Alice"); // We use strcpy to copy text in C

    printf("Employee created!\n");
    printf("ID: %d\n", my_employee->id);
    printf("Name: %s\n\n", my_employee->name);

    // 5. Give the memory back to the system
    free(my_employee);

    // 6. Throw away the key so we don't have a dangling pointer
    my_employee = NULL;

    return 0; // Exit successfully
}