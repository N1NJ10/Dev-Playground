int main() {
    int number = 50;

    // --- MODE 1: DECLARATION (The Badge) ---
    // "I am creating a pointer named ptr."
    int *ptr = &number; 

    // --- MODE 2: DEREFERENCE (The Action) ---
    // "Go to the address in ptr and change the value to 100."
    *ptr = 100; 

    // --- MODE 2: DEREFERENCE (The Action) ---
    // "Go to the address in ptr and read the value."
    printf("%d", *ptr); 

    return 0;
}