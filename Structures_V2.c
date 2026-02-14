#include <stdio.h>
#include <string.h>

struct Students {
    int age;
    char grade;
    char notes[100];
    char name[50];
};

int main() {
    struct Students fady;

    fady.age = 22;
    fady.grade = 'A';
    strcpy(fady.notes, "What this used for!");
    strcpy(fady.name, "fady");

    // FIX IS HERE: Changed %c to %s for name and notes
    printf("Student data:\n");
    printf("Name:  %s\n", fady.name);   // %s for String
    printf("Age:   %d\n", fady.age);    // %d for Integer
    printf("Grade: %c\n", fady.grade);  // %c for Character
    printf("Notes: %s\n", fady.notes);  // %s for String

    return 0;
}